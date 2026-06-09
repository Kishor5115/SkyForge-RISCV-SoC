/*
 * cli.h — Public interface for the SkyForge FreeRTOS+CLI UART shell.
 */
#ifndef CLI_H
#define CLI_H

/*
 * Register the built-in commands and create the interactive CLI task.
 * Call this once, after uart_init() and before vTaskStartScheduler().
 */
void cli_start(void);

#endif /* CLI_H */
