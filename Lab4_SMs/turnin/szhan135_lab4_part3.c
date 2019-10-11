/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//initialize a state for states
enum States {Start, INIT, POUND, KEY_Y, WAIT, LOCK, PAUSE}state;

void Tick(){
	switch(state){ //Transitions
		case Start:
			state = INIT;
			break;
		
		case INIT:
			if(PINA == 0x04){
				state = POUND;
				break;
			}
			if(PINA == 0x80){
				state = LOCK;
				break;
			}
			else{
				state = INIT;
				break;
			}
				
		case POUND:
			state = WAIT;
			break;
		
		case WAIT:
			if(PINA == 0x04){
				state = WAIT;
			}
			else if(PINA == 0x02){
				state = KEY_Y;
			}
			else if((PINA != 0x04) & (PINA != 0x02)){
				state = LOCK;
			}
			break;
		
		case KEY_Y:
			state = PAUSE;
			break;
		
		case LOCK:
			state = INIT;
			break;
		
		case PAUSE:
			if (PINA == 0x80){
				state = LOCK;
			}
			else{
				state = PAUSE;
			}
		
		default:
			break;
	}
	switch(state){ //State actions
		case Start:
			PORTB = 0x00;
			break;
		
		case INIT:
			PORTB = 0x00;
			break;
		
		case POUND:
			PORTB = 0x00;
			break;
		
		case WAIT:
			PORTB = 0x00;
			break;
		
		case KEY_Y:
			PORTB = 0x01;
			break;
		
		case LOCK:
			PORTB = 0x00;
			break;
		
		case PAUSE:
			PORTB = 0x01;
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
	
	while(1){
		Tick();
	}
}
