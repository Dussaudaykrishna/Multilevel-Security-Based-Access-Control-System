#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"
#define RS (1<<8)
#define EN (1<<9)
#define LCDDATA (0xFF<<16)
void lcd_cmd(unsigned char cmd)
{
IO0CLR = RS;
IO1CLR = LCDDATA;
IO1SET = (cmd<<16);
IO0SET = EN;
delay_ms(2);
IO0CLR = EN;
}
void lcd_data(unsigned char data)
{
IO0SET = RS;
IO1CLR = LCDDATA;
IO1SET = (data<<16);
IO0SET = EN;
delay_ms(2);
IO0CLR = EN;
}
void lcd_print(char *s)
{
while(*s)
lcd_data(*s++);
}

void lcd_init()
{
IO0DIR |= RS | EN;
IO1DIR |= LCDDATA;
delay_ms(100);
lcd_cmd(0x38);
lcd_cmd(0x0C);
lcd_cmd(0x06);
lcd_cmd(0x01);
}