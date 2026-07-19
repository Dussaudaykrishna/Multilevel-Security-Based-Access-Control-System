#include <lpc21xx.h>

#include "uart.h"
#include "gsm.h"
void gsm_send_sms(char *msg)
{
uart_string("AT\r");
delay_ms(1000);
uart_string("AT+CMGF=1\r");
delay_ms(1000);
uart_string("AT+CMGS=\"+917995108589\"\r"); // change phone
number
delay_ms(1000);
uart_string(msg);
uart_tx(26); // CTRL+Z
delay_ms(3000);
}
void send_sms_alert()
{
gsm_send_sms("Alert! 3 Wrong Password Attempts");
}