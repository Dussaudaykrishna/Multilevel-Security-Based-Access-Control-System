#include <lpc21xx.h>
#include <string.h>
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "delay.h"
#include "gsm.h"
#define LED (1<<16)
#define MOTOR_IN1 (1<<17)
#define MOTOR_IN2 (1<<18)
#define SWITCH (1<<11)
unsigned long seed=12345;
unsigned int generate_otp()
{
seed = seed * 1103515245 + 12345;
return (seed>>16)%9000 + 1000;
}
int main()
{
char password[5]="7777";
char entered[5];
char otp_entered[5];
char otp_string[5];
unsigned int otp;
int i;
IO0DIR |= LED|MOTOR_IN1|MOTOR_IN2;
IO0DIR &= ~SWITCH;

lcd_init();
uart_init();
lcd_print("Multilevel Security");
delay_ms(2000);
while(1)
{
lcd_cmd(0x01);
lcd_print("Enter Password");
lcd_cmd(0xC0);
for(i=0;i<4;i++)
{
char k=0;
while(k==0) k=keypad_read();
entered[i]=k;
lcd_data(k);
}
entered[4]='\0';
if(strcmp(entered,password)==0)
{
otp = generate_otp();
otp_string[0]=(otp/1000)+'0';
otp_string[1]=(otp/100)%10+'0';
otp_string[2]=(otp/10)%10+'0';
otp_string[3]=(otp%10)+'0';
otp_string[4]='\0';
char sms_msg[30];
strcpy(sms_msg,"Your OTP: ");
strcat(sms_msg,otp_string);
gsm_send_sms(sms_msg);
lcd_cmd(0x01);
lcd_print("Enter OTP");
lcd_cmd(0xC0);
for(i=0;i<4;i++)
{
char k=0;
while(k==0) k=keypad_read();
otp_entered[i]=k;
lcd_data(k);
}
otp_entered[4]='\0';
if(strcmp(otp_entered,otp_string)==0)
{
lcd_cmd(0x01);
lcd_print("Access Granted");
IO0SET = MOTOR_IN1;
IO0CLR = MOTOR_IN2;
delay_ms(5000);

IO0CLR = MOTOR_IN1;
}
}
}
}