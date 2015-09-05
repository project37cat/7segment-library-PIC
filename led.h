// dynamic lighting for the 3-digit 7-segment LED display
// the segments (anodes) are connected to the ports through resistors 750 Ohm
// common cathodes are connected through NPN transistors
// 05-Sep-2015
// compiler: HI-TECH C PRO for the PIC18 MCU Family  V9.63PL3


#include <htc.h>


#define SEGM_A_PIN   RC0
#define SEGM_A_TRIS  TRISC0

#define SEGM_B_PIN   RC1
#define SEGM_B_TRIS  TRISC1

#define SEGM_C_PIN   RC2
#define SEGM_C_TRIS  TRISC2

#define SEGM_D_PIN   RC3
#define SEGM_D_TRIS  TRISC3

#define SEGM_E_PIN   RD0
#define SEGM_E_TRIS  TRISD0

#define SEGM_F_PIN   RD1
#define SEGM_F_TRIS  TRISD1

#define SEGM_G_PIN   RD2
#define SEGM_G_TRIS  TRISD2

#define SEGM_H_PIN   RD3
#define SEGM_H_TRIS  TRISD3


#define COMMON_1       RC4
#define COMMON_1_TRIS  TRISC4

#define COMMON_2       RC5
#define COMMON_2_TRIS  TRISC5

#define COMMON_3       RC6
#define COMMON_3_TRIS  TRISC6


#define BIT_IS_SET(reg, bit) ((reg>>bit)&1)

#define SET_BIT(reg, bit) (reg |= (1<<bit))
#define CLR_BIT(reg, bit) (reg &= (~(1<<bit)))


typedef unsigned char uint8_t;


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

if(BIT_IS_SET(sbuff[digit],0)) SEGM_A_PIN=1;
else SEGM_A_PIN=0;

if(BIT_IS_SET(sbuff[digit],1)) SEGM_B_PIN=1;
else SEGM_B_PIN=0;

if(BIT_IS_SET(sbuff[digit],2)) SEGM_C_PIN=1;
else SEGM_C_PIN=0;

if(BIT_IS_SET(sbuff[digit],3)) SEGM_D_PIN=1;
else SEGM_D_PIN=0;

if(BIT_IS_SET(sbuff[digit],4)) SEGM_E_PIN=1;
else SEGM_E_PIN=0;

if(BIT_IS_SET(sbuff[digit],5)) SEGM_F_PIN=1;
else SEGM_F_PIN=0;

if(BIT_IS_SET(sbuff[digit],6)) SEGM_G_PIN=1;
else SEGM_G_PIN=0;

if(BIT_IS_SET(sbuff[digit],7)) SEGM_H_PIN=1;
else SEGM_H_PIN=0;

	
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
void led_print(uint8_t pos, const char *str) //print a string  //pos - 0..3 //str - text
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

SEGM_A_PIN=0;
SEGM_A_TRIS=0;

SEGM_B_PIN=0;
SEGM_B_TRIS=0;

SEGM_C_PIN=0;
SEGM_C_TRIS=0;

SEGM_D_PIN=0;
SEGM_D_TRIS=0;

SEGM_E_PIN=0;
SEGM_E_TRIS=0;

SEGM_F_PIN=0;
SEGM_F_TRIS=0;

SEGM_G_PIN=0;
SEGM_G_TRIS=0;

SEGM_H_PIN=0;
SEGM_H_TRIS=0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_off(void)
{
COMMON_1_TRIS=1;
COMMON_2_TRIS=1;
COMMON_3_TRIS=1;

SEGM_A_TRIS=1;
SEGM_B_TRIS=1;
SEGM_C_TRIS=1;
SEGM_D_TRIS=1;
SEGM_E_TRIS=1;
SEGM_F_TRIS=1;
SEGM_G_TRIS=1;
SEGM_H_TRIS=1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_clear(void)
{
sbuff[0]=0;
sbuff[1]=0;
sbuff[2]=0;
}
