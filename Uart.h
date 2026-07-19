#ifndef UART_H
#define UART_H
void uart_init(void);
void uart_tx(char c);
void uart_string(char *s);
#endif