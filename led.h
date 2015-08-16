// dynamic lighting for LED 3-digit 7-segment display
// the segments (anodes) are connected to the ports through resistors 750 Ohm
// common cathodes are connected through npn transistors
// 16-Aug-2015


#include <htc.h>


#define SEGMENT_PORT  PORTD
#define SEGMENT_TRIS  TRISD

#define COMMON_1       RC5
#define COMMON_1_TRIS  TRISC5

#define COMMON_2       RC6
#define COMMON_2_TRIS  TRISC6

#define COMMON_3       RC7
#define COMMON_3_TRIS  TRISC7


#define SET_BIT(reg, bit) (reg |= (1<<bit))
#define CLR_BIT(reg, bit) (reg &= (~(1<<bit)))


typedef signed char int8_t; //stdint
typedef unsigned char uint8_t;
typedef signed int int16_t;
typedef unsigned int uint16_t;


const uint8_t scode[] = //codes of symbols //segments: g-f-e-d-c-b-a-h(dot)
{
0b01111110, //0  //0
0b00001100, //1  //1
0b10110110, //2  //2
0b10011110, //3  //3  
0b11001100, //4  //4
0b11011010, //5  //5
0b11111010, //6  //6
0b00001110, //7  //7
0b11111110, //8  //8
0b11011110, //9  //9
0b00000000, //10 //space
0b10000000, //11 //-
0b11110010, //12 //E
0b01110010  //13 //C
};

uint8_t sbuff[] =
{
0x00,
0x00,
0x00
};


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_scan(void) //dynamic lighting (run 200-250 times per second)
{
static uint8_t digit=0;

COMMON_1=0; //turn off all digits
COMMON_2=0;
COMMON_3=0;

SEGMENT_PORT=sbuff[digit]; //load code of segments
	
if(digit==0) COMMON_1=1;
if(digit==1) COMMON_2=1;
if(digit==2) COMMON_3=1;

if(++digit>2) digit=0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_char(uint8_t pos, uint8_t sign) //print a character
{
uint8_t tmp=0;

switch(sign) //select the code of symbol
	{
	case 32: tmp=scode[10]; break; //space
	case 45: tmp=scode[11]; break; //"-"
	case 48: tmp=scode[0]; break; //"0"
	case 49: tmp=scode[1]; break; //"1"
	case 50: tmp=scode[2]; break; //"2"
	case 51: tmp=scode[3]; break; //"3"
	case 52: tmp=scode[4]; break; //"4"
	case 53: tmp=scode[5]; break; //"5"
	case 54: tmp=scode[6]; break; //"6"
	case 55: tmp=scode[7]; break; //"7"
	case 56: tmp=scode[8]; break; //"8"
	case 57: tmp=scode[9]; break; //"9"
	case 67: tmp=scode[13]; break; //"C"
	case 69: tmp=scode[12]; break; //"E"
	case 79: tmp=scode[0]; break; //"O"
	}

if(pos<=2) sbuff[pos]=(tmp|(sbuff[pos]&0b00000001));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void led_print(uint8_t pos, const char *str) //print a string
{
for(;*str;) led_char(pos++,*str++);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_dot(uint8_t pos, uint8_t dot) //position 0..2 //dot 0-off 1-on
{
if(pos<=2)
	{
	if(dot) SET_BIT(sbuff[pos],0);
	else CLR_BIT(sbuff[pos],0);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_init(void)
{
COMMON_1_TRIS=0;
COMMON_1=0;
COMMON_2_TRIS=0;
COMMON_2=0;
COMMON_3_TRIS=0;
COMMON_3=0;

SEGMENT_TRIS=0;
SEGMENT_PORT=0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void led_off(void)
{
COMMON_1_TRIS=1;
COMMON_2_TRIS=1;
COMMON_3_TRIS=1;

SEGMENT_TRIS=1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_clear(void)
{
sbuff[0]=0;
sbuff[1]=0;
sbuff[2]=0;
}
