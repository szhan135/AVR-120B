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

enum LT_states{INIT,INC,DEC,WAIT,RESET}LT_state;//initialize a state for four states
void Tick(){
	switch(LT_state){
		case INIT:
			PORTC = 0x07;
			if((PINA & 0x03)==0x01){
				LT_state = INC;
				break;
			}
			else if((PINA & 0x03)==0x02){
				LT_state = DEC;
				break;
			}
			else if((PINA & 0x03)==0x03){
				LT_state = RESET;
				break;
			}
			else{
				LT_state = INIT;
				break;
			}
		case INC:
             if(PORTC >= 0x09){
				PORTC = 0x09;
				LT_state = WAIT;
				break;
			}
             else{
                 PORTC = PORTC + 0x01; 
                 LT_state = WAIT;
			     break;
             }
		case DEC:
             if(PORTC <= 0x00){
                PORTC = 0x00;
				LT_state = WAIT;
                 break;
             }
             else{
                PORTC = PORTC - 0x01;
                LT_state = WAIT;
				break;
             }
		case WAIT:
			if((PINA & 0x03) == 0x01){
				LT_state = INC;
				break;
			}
			else if((PINA & 0x03)==0x02){	
				LT_state = DEC;
				break;
			}
			else if((PINA & 0x03) == 0x03){
				LT_state = RESET;
				break;
			}
			else{
				LT_state = WAIT;
				break;
			}
                case RESET:
			if((PINA& 0x03) == 0x03){
                LT_state = RESET;
                PORTC = 0x07;
                break;
			}
            else{
                LT_state = INIT;
                break;
            }
		default:
			break;
	}
}
int main(void){
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	
	DDRC = 0xFF; PORTC = 0x00;
	//DDRB = 0xFF; PORTB = 0x00;
	LT_state = INIT;
	while (1)
	{
		Tick();
	}
	return 1;
}
