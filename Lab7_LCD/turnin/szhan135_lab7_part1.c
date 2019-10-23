/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab # 7 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include "io.c"
#include "io.h"
// TimerISR() sets this to 1. C programmer should clear to 0.
volatile unsigned char TimerFlag = 0;

//Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1 ms ticks

void TimerOn()
{
	// AVR timer/counter controller register TCCR1
	// bit3 = 0; CTC mode (clear timer on compare)
	// bit2bit1bit0 = 011: prescaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 / 64 = 125,000 ticks/s
	// THUS, TCNT! register will count at 125,000 ticks/s
	TCCR1B = 0x0B;
	
	//AVR output compare register OCR1A.
	// Timer interrupt will be generated when TCNT! == OCR1A
	// We want a 1 ms tick. 0.001S * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// ! ms has passed. Thus, we compare to 125.
	OCR1A = 125;
	
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff()
{
	// bit3bit1bit0=000: timer off
	TCCR1B = 0x00;
}
void TimerISR()
{
	TimerFlag = 1;
}
// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{

	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		// Call the ISR that the user uses
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
enum States {Start, INIT, INC, DEC, WAIT, RESET}state;
unsigned char counter = 0;
void Tick(){
	switch(state){ 
		case Start:
		{
			LCD_Cursor(1);
			LCD_WriteData('0');
			state = INIT;
			break;
		}
		
		case INIT:
		if((~PINA & 0x03) == 0x01)
		{
			state = INC; break;
		}
		else if((~PINA & 0x03) == 0x02)
		{
			state = DEC; break;
		}
		else if((~PINA & 0x03) == 0x03)
		{
			state = RESET; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case INC:
		state = WAIT;
		break;
		
		case DEC:
		state = WAIT;
		break;
		
		case WAIT:
		if((~PINA & 0x03) == 0x01)
			{
				state = INC; break;
			}
			else if((~PINA & 0x03) == 0x02)
			{
				state = DEC; break;
			}
			else if((~PINA & 0x03) == 0x03)
			{
				state = RESET; break;
			}
			else if((~PINA & 0x03) == 0x00)
			{
				state = INIT; break;
			}
			else 
			{
				state = WAIT; break;
			}
		
		case RESET:
		if((~PINA & 0x03) == 0x00)
		{
			state = INIT; break;
		}
			else
		{
			state = RESET; break;
		}
		
		default:
		break;
	}
	
	
	
	switch(state){
		case Start:
		{
		}
		break;
		
		case INIT:
		break;
		
		case INC:
		{
			if(counter >= 0x09)
			{
				counter = 0x09;
			}
			else
			{
				counter = counter + 0x01;
			}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
			
			
		}
		
		case DEC:
		{
			if(counter <= 0x00)
			{
				counter = 0x00; 
			}
			else
			{
				counter = counter - 0x01;
			
			}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
			
		}
		
		case WAIT:
		break;
		
		case RESET:
		{
			counter = 0; 
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
		}
		default: 
		break;
	}
}

int main(void)
{
	DDRA = 0x00;PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	LCD_init();
	TimerSet(12);
	TimerOn();
	state = Start;
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	
	}
}
