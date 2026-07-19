#include <lpc21xx.h>
#include "uart.h"
void uart_init()
{
VPBDIV = 0x01;
PINSEL0 |= 0x00000005;
U0LCR = 0x83;
U0DLL = 78;
U0DLM = 0;
U0LCR = 0x03;
U0FCR = 0x07;
}
void uart_tx(char c)
{
while(!(U0LSR & 0x20));
U0THR = c;
}
void uart_string(char *s)
{
while(*s)
uart_tx(*s++);
}