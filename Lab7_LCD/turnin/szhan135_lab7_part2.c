/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab # 7 Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include "io.c"
#include "io.h"

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

void TimerOn()
{

	TCCR1B = 0x0B;
	
	OCR1A = 125;
	

	TIMSK1 = 0x02;
	
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	
	SREG |= 0x80;
}
void TimerOff()
{
	TCCR1B = 0x00;
}
void TimerISR()
{
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{

	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
enum States {Start, LED1, LED2, LED3, CHECK, WAIT,RESET}state;
unsigned char counter = 0;
unsigned char msg[7] = "Winner!";
void Tick(){
	switch(state){ 
		case Start:
		{
			counter = 5;
			LCD_Cursor(1);
			LCD_WriteData('5');
			state = LED1;
			break;
		}
		
		case LED1:
		if((~PINA & 0x01) == 0x01)
		{
			state = CHECK; break;
		}
		else
		{
			state = LED2; break;
		}
		
		case LED2:
		if((~PINA & 0x01) == 0x01)
		{
			state = CHECK; break;
		}
		else
		{
			state = LED3; break;
		}
		
		case LED3:
		if((~PINA & 0x01) == 0x01)
		{
			state = CHECK; break;
		}
		else
		{
			state = LED1; break;
		}
		
		case CHECK:
		state = WAIT;
		break;
		
		case WAIT:
		if((~PINA & 0x01) == 0x01)
		{
			state = WAIT; break;
		}
		else
		{
			state = RESET; break;
		}
		
		case RESET:
		if((~PINA & 0x01) == 0x01)
		{
			if(counter >= 9)
			{
				counter = 5;
				LCD_ClearScreen();	
				LCD_Cursor(1);
				LCD_WriteData('5');
				}
				state = LED1;
				break;	
			}
			else
			{
				state = RESTART; break;
			}
		
		default:
		break;
	}
	
	
	
	switch(state){
		case Start:
		{
		}
		break;
		
		case LED1:
		PORTB = 0x01;
		break;
		
		case LED2:
		PORTB = 0x02;
		break;
		
		case LED3:
		PORTB = 0x04;
		break;
		
		case CHECK:
		if(PORTB == 0x02)
			{
				counter = counter +1;
				if(counter >= 9)
				{
					LCD_DisplayString(1, msg); 
					break;
				}
				else
				{
					LCD_Cursor(1);
					LCD_WriteData(counter + '0'); 
					break;
				}
			}
			else
			{
				counter = counter -1;
				if(counter <= 0)
				{
					counter = 0;
				}
				LCD_Cursor(1);
				LCD_WriteData(counter + '0'); 
				break;
			}
		
		case WAIT:
		break;
		
		case RESET:
		break;
		
		default: 
		break;
	}
}

int main(void)
{
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x05;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	LCD_init();
	TimerSet(30);
	TimerOn();
	state = Start;
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
