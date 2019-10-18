/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{INIT,INC,DEC,WAIT,RESET}state;//initialize a state for four states
void Tick(){
	unsigned char button = 0x00;
	button = ~PINA & 0x0F;
	switch(state){
		case INIT:
			PORTC = 0x00;
			if(button==0x01){
				state = INC;
				break;
			}
			else if(button==0x02){
				state = DEC;
				break;
			}
			else if(button==0x03){
				state = RESET;
				break;
			}
			else{
				state = INIT;
				break;
			}
		case INC:
             if(PORTC >= 0x09){
				PORTC = 0x09;
				state = WAIT;
				break;
			}
             else{
                 PORTC = PORTC + 0x01; 
                 state = WAIT;
			     break;
             }
		case DEC:
             if(PORTC <= 0x00){
                PORTC = 0x00;
				state = WAIT;
                 break;
             }
             else{
                PORTC = PORTC - 0x01;
                state = WAIT;
				break;
             }
		case WAIT:
			if(button == 0x01){
				state = INC;
				break;
			}
			else if(button==0x02){	
				state = DEC;
				break;
			}
			else if(button == 0x03){
				state = RESET;
				break;
			}
			else{
				state = WAIT;
				break;
			}
                case RESET:
			if(button == 0x03){
                state = RESET;
                PORTC = 0x07;
                break;
			}
            else{
                state = INIT;
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
	state = INIT;
	while (1)
	{
		Tick();
	}
	return 1;
}
