// dynamic lighting for the 3-digit 7-segment LED display
// the segments (anodes) are connected to the ports through resistors 750 Ohm
// common cathodes are connected through NPN transistors
// 05-Sep-2015


#include <htc.h>


#define SEG_H_PIN   0
#define SEG_H_PORT  PORTC
#define SEG_H_TRIS  TRISC

#define SEG_A_PIN   1
#define SEG_A_PORT  PORTC
#define SEG_A_TRIS  TRISC

#define SEG_B_PIN   2
#define SEG_B_PORT  PORTC
#define SEG_B_TRIS  TRISC

#define SEG_C_PIN   3
#define SEG_C_PORT  PORTC
#define SEG_C_TRIS  TRISC

#define SEG_D_PIN   0
#define SEG_D_PORT  PORTD
#define SEG_D_TRIS  TRISD

#define SEG_E_PIN   1
#define SEG_E_PORT  PORTD
#define SEG_E_TRIS  TRISD

#define SEG_F_PIN   2
#define SEG_F_PORT  PORTD
#define SEG_F_TRIS  TRISD

#define SEG_G_PIN   3
#define SEG_G_PORT  PORTD
#define SEG_G_TRIS  TRISD


#define COM_1_PIN   4
#define COM_1_PORT  PORTC
#define COM_1_TRIS  TRISC

#define COM_2_PIN   5
#define COM_2_PORT  PORTC
#define COM_2_TRIS  TRISC

#define COM_3_PIN   6
#define COM_3_PORT  PORTC
#define COM_3_TRIS  TRISC


#define BIT_IS_SET(reg, bit) ((reg>>bit)&1)

#define SET_BIT(reg, bit) (reg |= (1<<bit))
#define CLR_BIT(reg, bit) (reg &= (~(1<<bit)))


#define SEG_A_CLR     CLR_BIT(SEG_A_PORT, SEG_A_PIN)
#define SEG_A_SET     SET_BIT(SEG_A_PORT, SEG_A_PIN)
#define SEG_A_OUTPUT  CLR_BIT(SEG_A_TRIS, SEG_A_PIN)
#define SEG_A_INPUT   SET_BIT(SEG_A_TRIS, SEG_A_PIN)

#define SEG_B_CLR     CLR_BIT(SEG_B_PORT, SEG_B_PIN)
#define SEG_B_SET     SET_BIT(SEG_B_PORT, SEG_B_PIN)
#define SEG_B_OUTPUT  CLR_BIT(SEG_B_TRIS, SEG_B_PIN)
#define SEG_B_INPUT   SET_BIT(SEG_B_TRIS, SEG_B_PIN)

#define SEG_C_CLR     CLR_BIT(SEG_C_PORT, SEG_C_PIN)
#define SEG_C_SET     SET_BIT(SEG_C_PORT, SEG_C_PIN)
#define SEG_C_OUTPUT  CLR_BIT(SEG_C_TRIS, SEG_C_PIN)
#define SEG_C_INPUT   SET_BIT(SEG_C_TRIS, SEG_C_PIN)

#define SEG_D_CLR     CLR_BIT(SEG_D_PORT, SEG_D_PIN)
#define SEG_D_SET     SET_BIT(SEG_D_PORT, SEG_D_PIN)
#define SEG_D_OUTPUT  CLR_BIT(SEG_D_TRIS, SEG_D_PIN)
#define SEG_D_INPUT   SET_BIT(SEG_D_TRIS, SEG_D_PIN)

#define SEG_E_CLR     CLR_BIT(SEG_E_PORT, SEG_E_PIN)
#define SEG_E_SET     SET_BIT(SEG_E_PORT, SEG_E_PIN)
#define SEG_E_OUTPUT  CLR_BIT(SEG_E_TRIS, SEG_E_PIN)
#define SEG_E_INPUT   SET_BIT(SEG_E_TRIS, SEG_E_PIN)

#define SEG_F_CLR     CLR_BIT(SEG_F_PORT, SEG_F_PIN)
#define SEG_F_SET     SET_BIT(SEG_F_PORT, SEG_F_PIN)
#define SEG_F_OUTPUT  CLR_BIT(SEG_F_TRIS, SEG_F_PIN)
#define SEG_F_INPUT   SET_BIT(SEG_F_TRIS, SEG_F_PIN)

#define SEG_G_CLR     CLR_BIT(SEG_G_PORT, SEG_G_PIN)
#define SEG_G_SET     SET_BIT(SEG_G_PORT, SEG_G_PIN)
#define SEG_G_OUTPUT  CLR_BIT(SEG_G_TRIS, SEG_G_PIN)
#define SEG_G_INPUT   SET_BIT(SEG_G_TRIS, SEG_G_PIN)

#define SEG_H_CLR     CLR_BIT(SEG_H_PORT, SEG_H_PIN)
#define SEG_H_SET     SET_BIT(SEG_H_PORT, SEG_H_PIN)
#define SEG_H_OUTPUT  CLR_BIT(SEG_H_TRIS, SEG_H_PIN)
#define SEG_H_INPUT   SET_BIT(SEG_H_TRIS, SEG_H_PIN)


#define COM_1_CLR     CLR_BIT(COM_1_PORT, COM_1_PIN)
#define COM_1_SET     SET_BIT(COM_1_PORT, COM_1_PIN)
#define COM_1_OUTPUT  CLR_BIT(COM_1_TRIS, COM_1_PIN)
#define COM_1_INPUT   SET_BIT(COM_1_TRIS, COM_1_PIN)

#define COM_2_CLR     CLR_BIT(COM_2_PORT, COM_2_PIN)
#define COM_2_SET     SET_BIT(COM_2_PORT, COM_2_PIN)
#define COM_2_OUTPUT  CLR_BIT(COM_2_TRIS, COM_2_PIN)
#define COM_2_INPUT   SET_BIT(COM_2_TRIS, COM_2_PIN)

#define COM_3_CLR     CLR_BIT(COM_3_PORT, COM_3_PIN)
#define COM_3_SET     SET_BIT(COM_3_PORT, COM_3_PIN)
#define COM_3_OUTPUT  CLR_BIT(COM_3_TRIS, COM_3_PIN)
#define COM_3_INPUT   SET_BIT(COM_3_TRIS, COM_3_PIN)


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

COM_1_CLR; //turn off all digits
COM_2_CLR;
COM_3_CLR;

if(BIT_IS_SET(sbuff[digit],0)) SEG_H_SET;
else SEG_H_CLR;

if(BIT_IS_SET(sbuff[digit],1)) SEG_A_SET;
else SEG_A_CLR;

if(BIT_IS_SET(sbuff[digit],2)) SEG_B_SET;
else SEG_B_CLR;

if(BIT_IS_SET(sbuff[digit],3)) SEG_C_SET;
else SEG_C_CLR;

if(BIT_IS_SET(sbuff[digit],4)) SEG_D_SET;
else SEG_D_CLR;

if(BIT_IS_SET(sbuff[digit],5)) SEG_E_SET;
else SEG_E_CLR;

if(BIT_IS_SET(sbuff[digit],6)) SEG_F_SET;
else SEG_F_CLR;

if(BIT_IS_SET(sbuff[digit],7)) SEG_G_SET;
else SEG_G_CLR;

	
if(digit==0) COM_1_SET;
if(digit==1) COM_2_SET;
if(digit==2) COM_3_SET;

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
COM_1_CLR;
COM_1_OUTPUT;

COM_2_CLR;
COM_2_OUTPUT;

COM_3_CLR;
COM_3_OUTPUT;

SEG_A_CLR;
SEG_A_OUTPUT;

SEG_B_CLR;
SEG_B_OUTPUT;

SEG_C_CLR;
SEG_C_OUTPUT;

SEG_D_CLR;
SEG_D_OUTPUT;

SEG_E_CLR;
SEG_E_OUTPUT;

SEG_F_CLR;
SEG_F_OUTPUT;

SEG_G_CLR;
SEG_G_OUTPUT;

SEG_H_CLR;
SEG_H_OUTPUT;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void led_off(void)
{
COM_1_INPUT;
COM_2_INPUT;
COM_3_INPUT;

SEG_A_INPUT;
SEG_B_INPUT;
SEG_C_INPUT;
SEG_D_INPUT;
SEG_E_INPUT;
SEG_F_INPUT;
SEG_G_INPUT;
SEG_H_INPUT;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void led_clear(void)
{
sbuff[0]=0;
sbuff[1]=0;
sbuff[2]=0;
}
