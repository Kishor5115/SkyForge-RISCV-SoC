/*
 * Minimal libc implementations for bare-metal PicoRV32
 * Provides: memset, memcpy, memmove, memcmp, strlen, strcpy, strncpy,
 *           strcmp, strncmp, snprintf, vsnprintf
 */

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

void *memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s2 = (const unsigned char *)src;
    while (n--) *d++ = *s2++;
    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s2 = (const unsigned char *)src;
    if (d < s2) {
        while (n--) *d++ = *s2++;
    } else {
        d += n; s2 += n;
        while (n--) *--d = *--s2;
    }
    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *a = (const unsigned char *)s1;
    const unsigned char *b = (const unsigned char *)s2;
    while (n--) {
        if (*a != *b) return *a - *b;
        a++; b++;
    }
    return 0;
}

size_t strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

char *strcpy(char *dest, const char *src)
{
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    char *d = dest;
    while (n && (*d++ = *src++)) n--;
    while (n--) *d++ = '\0';
    return dest;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) { s1++; s2++; }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2)) { s1++; s2++; n--; }
    if (n == 0) return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/* ── Minimal snprintf/vsnprintf ─────────────────────────────────── */

static void sn_putc(char **buf, size_t *rem, char c)
{
    if (*rem > 1) { **buf = c; (*buf)++; (*rem)--; }
}

static void sn_puts(char **buf, size_t *rem, const char *s)
{
    while (*s) sn_putc(buf, rem, *s++);
}

static void sn_utoa(char **buf, size_t *rem, uint32_t val, int base, int width, char pad)
{
    char tmp[12];
    int i = 0;
    if (val == 0) { tmp[i++] = '0'; }
    else { while (val) { int d = val % base; tmp[i++] = (d < 10) ? '0'+d : 'a'+d-10; val /= base; } }
    while (i < width) tmp[i++] = pad;
    while (i--) sn_putc(buf, rem, tmp[i]);
}

int vsnprintf(char *str, size_t size, const char *fmt, va_list ap)
{
    char *buf = str;
    size_t rem = size;

    while (*fmt) {
        if (*fmt != '%') { sn_putc(&buf, &rem, *fmt++); continue; }
        fmt++;

        /* Parse width and padding */
        char pad = ' ';
        int width = 0;
        if (*fmt == '0') { pad = '0'; fmt++; }
        while (*fmt >= '0' && *fmt <= '9') { width = width*10 + (*fmt - '0'); fmt++; }

        /* Skip 'l' modifier */
        if (*fmt == 'l') fmt++;

        switch (*fmt) {
            case 'd': case 'i': {
                int32_t v = va_arg(ap, int32_t);
                if (v < 0) { sn_putc(&buf, &rem, '-'); v = -v; if (width > 0) width--; }
                sn_utoa(&buf, &rem, (uint32_t)v, 10, width, pad);
                break;
            }
            case 'u':
                sn_utoa(&buf, &rem, va_arg(ap, uint32_t), 10, width, pad);
                break;
            case 'x': case 'X':
                sn_utoa(&buf, &rem, va_arg(ap, uint32_t), 16, width, pad);
                break;
            case 'p':
                sn_puts(&buf, &rem, "0x");
                sn_utoa(&buf, &rem, (uint32_t)(uintptr_t)va_arg(ap, void*), 16, 8, '0');
                break;
            case 's': {
                const char *s = va_arg(ap, const char *);
                sn_puts(&buf, &rem, s ? s : "(null)");
                break;
            }
            case 'c':
                sn_putc(&buf, &rem, (char)va_arg(ap, int));
                break;
            case '%':
                sn_putc(&buf, &rem, '%');
                break;
            default:
                sn_putc(&buf, &rem, '%');
                sn_putc(&buf, &rem, *fmt);
                break;
        }
        fmt++;
    }

    if (size > 0) *buf = '\0';
    return (int)(buf - str);
}

int snprintf(char *str, size_t size, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vsnprintf(str, size, format, ap);
    va_end(ap);
    return ret;
}
