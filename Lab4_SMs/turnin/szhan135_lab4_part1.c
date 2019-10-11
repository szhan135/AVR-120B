/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LT_states{INIT,TURN_OFF,WAIT_FIRST,TURN_ON,WAIT_SECOND}LT_state;//initialize a state for four states
void Tick(){
	switch(LT_state){
		case INIT:
			PORTB = 0x01;
			if((PINA & 0x01)==0x01){
				LT_state = TURN_OFF;
				break;
			}
			else{
				LT_state = INIT;
				break;
			}
		case TURN_OFF:
			PORTB = 0x02;
                        if((PINA & 0x01)==0x00){
                                LT_state = WAIT_FIRST;
                                break;
                        }
                        else{
                                LT_state = TURN_OFF;
                                break;
                        }
		case WAIT_FIRST:
                        if((PINA & 0x01)==0x01){
                                LT_state = TURN_ON;
                                break;
                        }
                        else{
                                LT_state = WAIT_FIRST;
                                break;
                        }
		case TURN_ON:
			PORTB = 0x01;
                        if((PINA & 0x01)==0x00){
                                LT_state = WAIT_SECOND;
                                break;
                        }
                        else{
                                LT_state = TURN_ON;
                                break;
                        }
		case WAIT_SECOND:
                        if((PINA & 0x01)==0x01){
                                LT_state = TURN_OFF;
                                break;
                        }
                        else{
                                LT_state = WAIT_SECOND;
                                break;
                        }
		default:
			break;
	}
}
int main(void){
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	
	DDRB = 0xFF; PORTB = 0x00;
	//DDRC = 0xFF; PORTC = 0x00;
	LT_state = INIT;
	while (1)
	{
		Tick();
	}
	return 1;
}
