// 3x7segment LED display test
// 05-Sep-2015


#define _XTAL_FREQ 8000000


#include <htc.h>

#include "led.h"


__CONFIG(1, RCIO );
__CONFIG(2, BORDIS & WDTDIS );


#define TMR0_LOAD 64910 //preload Timer 0 for overflow ~200Hz //65535-64910=625 125kHz/625=200


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
led_clear();
	
led_print(0,"123");
	
led_dot(0,1);
led_dot(1,1);
led_dot(2,1);
		
for(;;);
}