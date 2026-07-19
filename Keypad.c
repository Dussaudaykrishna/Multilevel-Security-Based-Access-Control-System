#include <lpc21xx.h>
#include "keypad.h"
#include "delay.h"
/* Rows */
#define ROW1 (1<<27)
#define ROW2 (1<<28)
#define ROW3 (1<<29)
#define ROW4 (1<<30)
/* Columns */
#define COL1 (1<<12)
#define COL2 (1<<10)
#define COL3 (1<<14)
#define COL4 (1<<15)
#define ALL_ROWS (ROW1|ROW2|ROW3|ROW4)
#define ALL_COLS (COL1|COL2|COL3|COL4)
char keypad_read()
{
PINSEL0 &= ~(0xFF<<20);
IO0DIR |= ALL_ROWS;
IO0DIR &= ~ALL_COLS;

IO0SET = ALL_ROWS;
/* Row1 */
IO0CLR = ROW1;
delay_ms(5);
if(!(IO0PIN & COL1)){while(!(IO0PIN & COL1));IO0SET=ROW1;return '7';}
if(!(IO0PIN & COL2)){while(!(IO0PIN & COL2));IO0SET=ROW1;return '8';}
if(!(IO0PIN & COL3)){while(!(IO0PIN & COL3));IO0SET=ROW1;return '9';}
IO0SET = ROW1;
/* Row2 */
IO0CLR = ROW2;
delay_ms(5);
if(!(IO0PIN & COL1)){while(!(IO0PIN & COL1));IO0SET=ROW2;return '4';}
if(!(IO0PIN & COL2)){while(!(IO0PIN & COL2));IO0SET=ROW2;return '5';}
if(!(IO0PIN & COL3)){while(!(IO0PIN & COL3));IO0SET=ROW2;return '6';}
IO0SET = ROW2;
/* Row3 */
IO0CLR = ROW3;
delay_ms(5);
if(!(IO0PIN & COL1)){while(!(IO0PIN & COL1));IO0SET=ROW3;return '1';}
if(!(IO0PIN & COL2)){while(!(IO0PIN & COL2));IO0SET=ROW3;return '2';}
if(!(IO0PIN & COL3)){while(!(IO0PIN & COL3));IO0SET=ROW3;return '3';}
IO0SET = ROW3;
/* Row4 */
IO0CLR = ROW4;
delay_ms(5);
if(!(IO0PIN & COL2)){while(!(IO0PIN & COL2));IO0SET=ROW4;return '0';}
IO0SET = ROW4;
return 0;
}