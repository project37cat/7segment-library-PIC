// 3x7segment LED display test
// 09-Sep-2015
// HI-TECH C compiler


#include <htc.h>

#include "led.h"


/* Config Bits for PIC18F4320 */
__CONFIG(1, RCIO ); //RC oscillator
__CONFIG(2, BORDIS & WDTDIS ); //disable Brown-out Reset  //disable  Watchdog Timer


#define TMR0_LOAD 64911 //preload Timer 0 for overflow ~200Hz //65536-64911=625 125kHz/625=200


///////////////////////////////////////////////////////////////////////////////////////////////////
void interrupt handler(void)
{
if (TMR0IF) //the timer 0 overflow interrupt
	{
	TMR0IF=0;
	TMR0=TMR0_LOAD;

	led_scan(); //dynamic lighting
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
IRCF2=1; IRCF1=1; IRCF0=1; //8MHz internal RC oscillator

ADCON1=0b1111; //disable analog inputs

T0CON=0b10010011; //prescaler 011 - 1:16  Fosc/4=2000, 2000/16=125kHz
TMR0=TMR0_LOAD; //preload
TMR0IE=1; //timer overflow intterrupt enable

PEIE=1; //peripheral interrupt enable
GIE=1; //global interrupts enable

led_init();
	
led_print(0,"123");

led_dot(0,1);
led_dot(1,1);
led_dot(2,1);

//led_clear();

for(;;);
}
