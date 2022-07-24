#include <stdio.h>
#include <stm32f4xx.h>
void lcd_ini(void);
void lcd_data(char j);
void lcd_cmd(char i);
unsigned int read(unsigned int val);
void lcdString(char *String);



void display_value(unsigned int value);
void display_float(float value);
float T=0 , V =0,Counter=0,Ir=0,Er=0,rr=0;
float rrE=0.5,rrI=0.5;
unsigned int flagI=1;flagE=1;
volatile uint32_t msTicks; /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
 SysTick_Handler
*----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
 msTicks++;
}
void Delay (uint32_t dlyTicks) 
{ 
uint32_t loop=0,dly=0,loope=0;
dly = dlyTicks ; 
for(loop=0;loop<dly;loop++)
 {
for(loope=0;loope<29000;loope++)
 {
__NOP();
 }}}
unsigned long LCDDATA=0;
unsigned int value;
 unsigned int sensor;
/*----------------------------------------------------------------------------
 MAIN function
*----------------------------------------------------------------------------*/
int main (void) {
 SystemCoreClockUpdate(); // Get Core Clock Frequency
/*----------------------------------------------------------------------------
 Add your code to enable Ports that can be used for this program.
*----------------------------------------------------------------------------*/
	
	//sensor
	RCC->AHB1ENR |=(1<<0); //gpioA enable
	GPIOA->MODER =0X00000000;
	GPIOA->OTYPER=0X00000000 ;
	GPIOA->OSPEEDR=0X00000000;
	GPIOA->PUPDR=0X00000000;
	//lcd

	//
RCC->AHB1ENR |=(1<<1); //gpioB enable
RCC->AHB1ENR |=(1<<4); //gpioe enable

GPIOB->MODER =0X00000005;
GPIOB->OTYPER=0X00000000 ;
GPIOB->OSPEEDR=0X00000000;
GPIOB->PUPDR=0X00000000;
	
GPIOE->MODER =0X55555555;
GPIOE->OTYPER=0X00000000;
GPIOE->OSPEEDR=0X00000000;
GPIOE->PUPDR=0X00000000;
//	
//read(value);
	

	
GPIOB->BSRR= ((1 << 16) ); // LCD RW -> 0
lcd_ini();



while(Counter<=24 ){

lcd_cmd(0x80); // line 1
lcd_data('I');
lcd_data('N');
lcd_data('H');
lcd_data('A');
lcd_data('L');
lcd_data('E');
lcd_data('=');	
	sensor=read(value);

	Counter=Counter+1;
	if(sensor == 0X00000001){
		T=T+1;
		if(flagE==1){
		rrI=0.5;
	
			flagE=0;
			flagI=1;
		}
		

	}
	else{
				V=V+1;
				if(flagI==1){
				rrE=0.5;
			
						flagI=0;
			flagE=1;
				}

	}
	Ir=(T/Counter)*100.0;
	Er=	(V/Counter)*100.0;
	rr=rrI+rrE+rr; 
	rrI=rrE=0;
display_value(Ir);

	lcd_data(' ');
lcd_data('R');


lcd_data('=');	
	display_value(rr);
	lcd_cmd(0xC0); // line 2
lcd_data('E');
lcd_data('X');
lcd_data('H');
lcd_data('A');
lcd_data('L');
lcd_data('E');
lcd_data('=');	
//T = 85.543*(1.8663 - V);
display_value(Er);
//lcd_data(value); // S
//display_value( sensor);
	//delay(100);
	lcd_data(' ');
lcd_data('T');
lcd_data('=');
display_value(Counter);

if(Counter==25){
	if(rr<6){
		lcd_ini();
lcd_cmd(0x80); // line 1
lcd_data('B');
lcd_data('R');
lcd_data('E');
lcd_data('T');
lcd_data('H');
lcd_data('E');
lcd_data(' ');	
		
lcd_data('R');
lcd_data('A');
lcd_data('T');
lcd_data('E');
lcd_data(' ');
		lcd_cmd(0xC0); 
lcd_data('I');
lcd_data('S');	
lcd_data(' ');
lcd_data('L');
lcd_data('O');
lcd_data('W');
Delay(10);
	}
	
	if(rr>=20){
		lcd_ini();
lcd_cmd(0x80); // line 1
lcd_data('B');
lcd_data('R');
lcd_data('E');
lcd_data('T');
lcd_data('H');
lcd_data('E');
lcd_data(' ');	
		
lcd_data('R');
lcd_data('A');
lcd_data('T');
lcd_data('E');
lcd_data(' ');
		lcd_cmd(0xC0); 
lcd_data('I');
lcd_data('S');	
lcd_data(' ');
lcd_data('H');
lcd_data('I');
lcd_data('G');
lcd_data('H');
Delay(10);
	}
	
		if(rr>=6 & rr<=12){
		lcd_ini();
lcd_cmd(0x80); // line 1
lcd_data('B');
lcd_data('R');
lcd_data('E');
lcd_data('T');
lcd_data('H');
lcd_data('E');
lcd_data(' ');	
		
lcd_data('R');
lcd_data('A');
lcd_data('T');
lcd_data('E');
lcd_data(' ');
		lcd_cmd(0xC0); 
lcd_data('I');
lcd_data('S');	
lcd_data(' ');
lcd_data('N');
lcd_data('O');
lcd_data('R');
lcd_data('M');
lcd_data('A');
lcd_data('L');
Delay(10);
	}
		
}
}
}

//}
void lcd_ini(void)
{
 Delay(10);
	//lcd_cmd(0X0F);
 lcd_cmd(0x38);
 lcd_cmd(0x0C);
 lcd_cmd(0x01);
 Delay(10);
	}
void lcd_cmd(char i)
{
unsigned long r=0;
char loop=0;
r |= i;
for(loop=0;loop<=7;loop++)
{
 r = r << 1;
}
GPIOB->BSRR = ((1 << 17) );
LCDDATA = r;
GPIOE->ODR &= 0x000000FF;
GPIOE->ODR |= LCDDATA;
GPIOE->BSRR = ((1 << 7) );
Delay(10);//100
GPIOE->BSRR = ((1 << 23) );
}
void lcd_data(char j)
{
 unsigned long r=0;
char loop=0;
r |= j;
for(loop=0;loop<=7;loop++)
{
 r = r << 1;
}
GPIOB->BSRR = ((1 << 1) ); //rs
LCDDATA = r;
GPIOE->ODR &= 0x000000FF;
GPIOE->ODR |= LCDDATA;
GPIOE->BSRR = ((1 << 7) );
Delay(10);
GPIOE->BSRR= ((1 << 23) ); 
}

unsigned int read(unsigned int val){
val=GPIOA->IDR & 0X00000001;
	return val;
}

void display_value(unsigned int value){
unsigned int seg1=0,seg2=0,seg3=0,seg=0;
seg3=value%10;
seg2=(value%100)/10;
seg1= value/100;
//lcd_cmd(0x80);  // line 1
lcd_data(seg1 + 0x30 ); // S
lcd_data(seg2 + 0x30); // S
lcd_data(seg3 + 0x30); // S
}// End void display_value(unsigned int value


