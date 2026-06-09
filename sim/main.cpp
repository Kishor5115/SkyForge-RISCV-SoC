/*
 * Verilator Testbench for PicoRV32 SoC
 * - Clock generation, reset sequencing
 * - Remote Bitbang TCP server on port 9824 for JTAG via OpenOCD
 * - Firmware execution monitoring (trap, GPIO, timer)
 */

#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vsoc_top.h"
#include "Vsoc_top___024root.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <csignal>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <termios.h>
#include <deque>

/* ── Configuration ───────────────────────────────────────────────── */
#define RBB_PORT        9824
#define RESET_CYCLES    10
#define MAX_SIM_TIME    0ULL            /* 0 = no limit (debug-friendly) */
#define TRACE_ENABLE    0              /* Disable VCD for speed */

/* ── Remote Bitbang Server ───────────────────────────────────────── */
class RemoteBitbang {
public:
    RemoteBitbang(int port) : listen_fd(-1), client_fd(-1), tck(1), tms(1), tdi(1), tdo(0), trst(1), srst(1) {
        listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (listen_fd < 0) { perror("socket"); exit(1); }

        int opt = 1;
        setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family      = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        addr.sin_port        = htons(port);

        if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("bind"); exit(1);
        }
        if (listen(listen_fd, 1) < 0) {
            perror("listen"); exit(1);
        }

        /* non-blocking listen socket */
        fcntl(listen_fd, F_SETFL, O_NONBLOCK);

        printf("[RBB] Listening on localhost:%d\n", port);
        fflush(stdout);
    }

    ~RemoteBitbang() {
        if (client_fd >= 0) close(client_fd);
        if (listen_fd >= 0) close(listen_fd);
    }

    /* Accept pending connection (non-blocking) */
    void accept_client() {
        if (client_fd >= 0) return;
        client_fd = accept(listen_fd, NULL, NULL);
        if (client_fd >= 0) {
            int flag = 1;
            setsockopt(client_fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));
            fcntl(client_fd, F_SETFL, O_NONBLOCK);
            printf("[RBB] Client connected\n");
            fflush(stdout);
        }
    }

    /*
     * Process one character from the Remote Bitbang protocol.
     * Returns true if simulation should quit ('Q').
     * Protocol: ASCII chars '0'-'7' encode {tdi, tms, tck} as 3-bit value.
     *           'R' = read TDO, 'r'/'s' also read, 'Q' = quit.
     */
    bool tick() {
        accept_client();
        if (client_fd < 0) return false;

        /* Process exactly one Remote Bitbang command per sim step.
         * This preserves TCK edges (OpenOCD relies on each ASCII command
         * being observed individually). */
        char c = 0;
        ssize_t n = read(client_fd, &c, 1);
        if (n == 0) {
            /* client disconnected */
            printf("[RBB] Client disconnected\n");
            fflush(stdout);
            close(client_fd);
            client_fd = -1;
            return false;
        }
        if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) return false;
            perror("[RBB] read");
            close(client_fd);
            client_fd = -1;
            return false;
        }

        if (c >= '0' && c <= '7') {
            int val = c - '0';
            /* OpenOCD remote_bitbang encoding uses bit2=tck, bit1=tms, bit0=tdi. */
            tck = (val >> 2) & 1;
            tms = (val >> 1) & 1;
            tdi = (val >> 0) & 1;
        } else if (c == 'R') {
            char resp = tdo ? '1' : '0';
            if (send(client_fd, &resp, 1, MSG_NOSIGNAL) < 0) {
                perror("[RBB] send");
            }
            fflush(stdout);
        } else if (c == 'r' || c == 's' || c == 't' || c == 'u') {
            /* Reset commands:
             *   r=reset 0 0, s=0 1, t=1 0, u=1 1 (trst,srst).
             * This SoC model has no TRST/SRST pins, but we must parse these
             * commands to stay protocol-aligned with OpenOCD. */
            trst = (c == 't' || c == 'u') ? 1 : 0;
            srst = (c == 's' || c == 'u') ? 1 : 0;
        } else if (c == 'Q' || c == 'q') {
            printf("[RBB] Quit command received — closing client (sim stays alive)\n");
            fflush(stdout);
            close(client_fd);
            client_fd = -1;
            return false;
        } else if (c == 'B' || c == 'b') {
            /* blink — ignore */
        }
        fflush(stdout);
        return false;
    }

    /* JTAG signal accessors */
    int get_tck() const { return tck; }
    int get_tms() const { return tms; }
    int get_tdi() const { return tdi; }
    void set_tdo(int v) { tdo = v; }

private:
    int listen_fd;
    int client_fd;
    int tck, tms, tdi, tdo;
    int trst, srst;
};

/* ── Interactive UART Bridge ─────────────────────────────────────────
 * Pin-level 8N1 bridge between the SoC UART pins and the host terminal:
 *   - uart_tx  (SoC output) is decoded and written to stdout
 *   - stdin keystrokes are serialized onto uart_rx (SoC input)
 *
 * Bit period must match the firmware: uart_init(14) → baud_div = 14,
 * 16x oversampling → CYCLES_PER_BIT = 14 * 16 = 224 clock cycles/bit.
 *
 * tick_rx() / tick_tx() are each called once per CPU clock cycle.
 * ──────────────────────────────────────────────────────────────────── */
#define UART_BAUD_DIV        14
#define UART_OVERSAMPLE      16
#define UART_CYCLES_PER_BIT  (UART_BAUD_DIV * UART_OVERSAMPLE)   /* 224 */
#define STDIN_POLL_INTERVAL  256      /* poll stdin every N clock cycles */

class UartBridge {
public:
    UartBridge() {
        /* RX (driven into SoC) idle state is logic high. */
        rx_line = 1; rx_sending = false; rx_bit_idx = 0;
        rx_cycle = 0; cur_byte = 0; stdin_eof = false; poll_cnt = 0;

        /* TX decoder state. */
        tx_state = TX_IDLE; tx_prev = 1; tx_counter = 0;
        tx_bit_idx = 0; tx_data = 0; tx_sample_at = 0;

        /* Non-blocking stdin. */
        int fl = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, fl | O_NONBLOCK);

        /* Raw terminal mode (only if interactive) so keystrokes pass
         * through immediately without local echo/line buffering. */
        is_tty = isatty(STDIN_FILENO);
        if (is_tty) {
            tcgetattr(STDIN_FILENO, &orig_termios);
            struct termios raw = orig_termios;
            raw.c_lflag &= ~(ICANON | ECHO);   /* keep ISIG so Ctrl-C quits */
            raw.c_iflag &= ~(IXON | ICRNL);
            raw.c_cc[VMIN]  = 0;
            raw.c_cc[VTIME] = 0;
            tcsetattr(STDIN_FILENO, TCSANOW, &raw);
            printf("[UART] Interactive console ready — type into this terminal.\n");
            printf("[UART] (Ctrl-C to quit)\n");
            fflush(stdout);
        }
    }

    ~UartBridge() {
        if (is_tty) tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    }

    /* Current bit to drive onto uart_rx (call before the posedge eval). */
    int rx_bit() const { return rx_line; }

private:
    /* ── RX (host → SoC) serializer state ── */
    int  rx_line;
    bool rx_sending;
    int  rx_bit_idx;          /* 0=start, 1..8=data LSB-first, 9=stop */
    int  rx_cycle;            /* cycle counter within current bit */
    unsigned char cur_byte;
    std::deque<unsigned char> rx_queue;
    bool stdin_eof;
    int  poll_cnt;

    /* ── TX (SoC → host) decoder state ── */
    enum { TX_IDLE, TX_RECV } tx_state;
    int tx_prev;
    int tx_counter;
    int tx_bit_idx;
    int tx_data;
    int tx_sample_at;

    bool is_tty;
    struct termios orig_termios;

public:
    /* Pull available bytes from stdin into the RX queue (non-blocking). */
    void poll_stdin() {
        if (stdin_eof) return;
        unsigned char buf[64];
        ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
        if (n > 0) {
            for (ssize_t i = 0; i < n; i++) rx_queue.push_back(buf[i]);
        } else if (n == 0) {
            stdin_eof = true;          /* piped input reached EOF */
        }
        /* n < 0 with EAGAIN: nothing available, ignore. */
    }

    /* Advance the RX serializer one clock cycle (drives uart_rx). */
    void tick_rx() {
        if (++poll_cnt >= STDIN_POLL_INTERVAL) {
            poll_cnt = 0;
            poll_stdin();
        }

        if (!rx_sending) {
            rx_line = 1;                       /* idle high */
            if (!rx_queue.empty()) {
                cur_byte   = rx_queue.front();
                rx_queue.pop_front();
                rx_sending = true;
                rx_bit_idx = 0;
                rx_cycle   = 0;
            }
            return;
        }

        /* Drive the current frame bit. */
        if      (rx_bit_idx == 0) rx_line = 0;                          /* start  */
        else if (rx_bit_idx <= 8) rx_line = (cur_byte >> (rx_bit_idx - 1)) & 1; /* data */
        else                      rx_line = 1;                          /* stop   */

        if (++rx_cycle >= UART_CYCLES_PER_BIT) {
            rx_cycle = 0;
            if (++rx_bit_idx >= 10) rx_sending = false;   /* frame complete */
        }
    }

    /* Sample uart_tx one clock cycle and emit decoded bytes (call after eval). */
    void tick_tx(int tx_bit) {
        switch (tx_state) {
        case TX_IDLE:
            if (tx_prev == 1 && tx_bit == 0) {            /* falling edge = start */
                tx_state     = TX_RECV;
                tx_counter   = 0;
                tx_bit_idx   = 0;
                tx_data      = 0;
                /* sample bit0 at 1.5 bit periods after the start edge */
                tx_sample_at = UART_CYCLES_PER_BIT + UART_CYCLES_PER_BIT / 2;
            }
            break;
        case TX_RECV:
            tx_counter++;
            if (tx_counter == tx_sample_at) {
                tx_data |= (tx_bit & 1) << tx_bit_idx;
                tx_bit_idx++;
                tx_sample_at += UART_CYCLES_PER_BIT;
                if (tx_bit_idx == 8) {
                    putchar((char)(tx_data & 0xFF));
                    fflush(stdout);
                    tx_state = TX_IDLE;
                }
            }
            break;
        }
        tx_prev = tx_bit;
    }
};

/* ── Globals ─────────────────────────────────────────────────────── */
static volatile bool g_quit = false;

static void sig_handler(int) { g_quit = true; }

/* ── Main ────────────────────────────────────────────────────────── */
int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(TRACE_ENABLE);

    signal(SIGINT,  sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGPIPE, SIG_IGN);

    auto top = new Vsoc_top;
    RemoteBitbang rbb(RBB_PORT);
    UartBridge uart;

#if TRACE_ENABLE
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("soc_top.vcd");
#endif

    /* ── Reset ───────────────────────────────────────────────────── */
    top->clk     = 0;
    top->rst_n   = 0;
    top->jtag_tck = 0;
    top->jtag_tms = 1;
    top->jtag_tdi = 0;
    top->uart_rx  = 1;          /* UART line idle = high */

    vluint64_t sim_time = 0;

    printf("[SIM] Reset for %d cycles ...\n", RESET_CYCLES);
    fflush(stdout);

    for (int i = 0; i < RESET_CYCLES * 2; i++) {
        top->clk = !top->clk;
        top->eval();
#if TRACE_ENABLE
        tfp->dump(sim_time);
#endif
        sim_time++;
    }

    top->rst_n  = 1;
    printf("[SIM] Reset released. Running ...\n");
    fflush(stdout);

    /* ── Monitoring state ────────────────────────────────────────── */
    uint32_t last_gpio_out = 0;
    int gpio_toggle_count = 0;
    bool trap_seen = false;
    bool success_reported = false;
    vluint64_t trap_time = 0;
    uint64_t apb_write_count = 0;
    uint64_t gpio_apb_write_count = 0;

    /* Always run forever — debug sessions require an indefinitely-running sim.
     * To restore old behaviour, set SIM_LIMIT_RUN=1. */
    bool run_forever = (getenv("SIM_LIMIT_RUN") == nullptr);

    /* When SIM_QUIET is set, suppress the chatty GPIO/periodic diagnostics so
     * stdout carries only the UART console output (clean interactive shell). */
    bool quiet = (getenv("SIM_QUIET") != nullptr);

    /* ── Main simulation loop ────────────────────────────────────── */
    while (!Verilated::gotFinish() && !g_quit) {

        /* Positive edge */
        top->clk = 1;

        /* Drive UART RX line (host keystrokes → SoC), before the edge. */
        uart.tick_rx();
        top->uart_rx = uart.rx_bit();

        /* Drive JTAG from Remote Bitbang */
        bool quit = rbb.tick();
        if (quit) break;

        top->jtag_tck = rbb.get_tck();
        top->jtag_tms = rbb.get_tms();
        top->jtag_tdi = rbb.get_tdi();

        top->eval();
        auto *root = top->rootp;

        /* Decode UART TX (SoC → host stdout), after the edge. */
        uart.tick_tx(top->uart_tx);

        /* Internal APB debug: confirm writes leave AXI2APB and reach GPIO window */
        if (root->soc_top__DOT__u_soc_core__DOT__apb_psel &&
            root->soc_top__DOT__u_soc_core__DOT__apb_penable &&
            root->soc_top__DOT__u_soc_core__DOT__apb_pwrite) {
            apb_write_count++;
            uint32_t apb_addr = root->soc_top__DOT__u_soc_core__DOT__apb_paddr;
            uint32_t apb_data = root->soc_top__DOT__u_soc_core__DOT__apb_pwdata;

            if (apb_addr >= 0x20002000u && apb_addr <= 0x20002FFFu) {
                gpio_apb_write_count++;
            }

        }

        /* Sample TDO */
        rbb.set_tdo(top->jtag_tdo);

        /* ── Monitor trap signal ─────────────────────────────────── */
        if (top->trap && !trap_seen) {
            trap_seen = true;
            trap_time = sim_time;
            if (!quiet) {
                printf("[SIM] *** TRAP detected at time %llu ***\n",
                       (unsigned long long)sim_time);
                fflush(stdout);
            }
        }

        /* ── Monitor GPIO output changes ─────────────────────────── */
        uint32_t gpio_now = top->gpio_out;
        if (gpio_now != last_gpio_out) {
            gpio_toggle_count++;
            if (!quiet && gpio_toggle_count <= 50) {
                printf("[SIM] GPIO_OUT changed to 0x%08X at time %llu (toggle #%d)\n",
                       gpio_now, (unsigned long long)sim_time, gpio_toggle_count);
                fflush(stdout);
            }
            last_gpio_out = gpio_now;

            /* GPIO activity confirms firmware is driving peripheral writes. */
            if (gpio_toggle_count >= 2 && !success_reported) {
                success_reported = true;
                if (!quiet) {
                    printf("[SIM] *** SUCCESS: GPIO activity detected ***\n");
                    fflush(stdout);
                }
            }
        }

        /* Periodic status print */
        if (!quiet && (sim_time & 0xFFFFF) == 0 && sim_time > 0) {
            printf("[SIM] time=%llu trap=%d gpio=0x%08X toggles=%d\n",
                   (unsigned long long)sim_time, (int)top->trap,
                   (unsigned int)top->gpio_out, gpio_toggle_count);
            fflush(stdout);
        }

        /* If we've seen enough GPIO toggles, we're done */
        if (!run_forever && gpio_toggle_count >= 20) {
            printf("[SIM] Sufficient GPIO toggles detected — exiting.\n");
            fflush(stdout);
            break;
        }

#if TRACE_ENABLE
        tfp->dump(sim_time);
#endif
        sim_time++;

        if (!run_forever && MAX_SIM_TIME != 0 && sim_time >= MAX_SIM_TIME)
            break;

        /* Negative edge */
        top->clk = 0;
        top->eval();
#if TRACE_ENABLE
        tfp->dump(sim_time);
#endif
        sim_time++;

        if (!run_forever && MAX_SIM_TIME != 0 && sim_time >= MAX_SIM_TIME)
            break;
    }

    printf("\n[SIM] ═══════════════════════════════════════════════\n");
    printf("[SIM] Simulation Summary:\n");
    printf("[SIM]   Total time: %llu ticks (%llu cycles)\n",
           (unsigned long long)sim_time, (unsigned long long)sim_time/2);
    printf("[SIM]   Trap: %s", trap_seen ? "YES" : "NO");
    if (trap_seen) printf(" (at time %llu)", (unsigned long long)trap_time);
    printf("\n");
    printf("[SIM]   GPIO toggles: %d\n", gpio_toggle_count);
    printf("[SIM]   Final GPIO_OUT: 0x%08X\n", (unsigned int)top->gpio_out);
    printf("[SIM]   Final GPIO_OE:  0x%08X\n", (unsigned int)top->gpio_oe);
    printf("[SIM]   APB writes observed: %llu (GPIO window: %llu)\n",
           (unsigned long long)apb_write_count,
           (unsigned long long)gpio_apb_write_count);
    printf("[SIM]   GPIO reg_output_en=0x%08X reg_output_val=0x%08X\n",
           (unsigned int)top->rootp->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en,
           (unsigned int)top->rootp->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val);
    if (gpio_toggle_count >= 2) {
        printf("[SIM]   Result: PASS — firmware produced GPIO activity\n");
    } else if (trap_seen) {
        printf("[SIM]   Result: FAIL — CPU trapped\n");
    } else {
        printf("[SIM]   Result: INCONCLUSIVE — no GPIO activity detected\n");
    }
    printf("[SIM] ═══════════════════════════════════════════════\n\n");
    fflush(stdout);

#if TRACE_ENABLE
    tfp->close();
    delete tfp;
#endif
    top->final();
    delete top;
    return (gpio_toggle_count >= 2) ? 0 : 1;
}
