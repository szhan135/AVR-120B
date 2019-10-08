/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab # 3 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char GetBit(unsigned char temp1, unsigned temp2){//helper function from zybook
	return ((temp1 & (0x01 << temp2))!=0);
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //inputs
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; //outputs
    /* Insert your solution below */
    unsigned char inputA;
    unsigned char inputB;
    unsigned char outputC;
    while (1) {
		unsigned char temp = 0;
		unsigned char i = 0;
		inputA = PINA & 0xFF;
		inputB = PINB & 0xFF;
		for (i = 0; i<8; ++i){
			if(GetBit(inputA,i)){
			temp = temp+1;
			}
			if(GetBit(inputB,i)){
			temp = temp+1;
			}	
		}
		outputC = (outputC & 0x00)|temp;
		PORTC = outputC;
    }
    return 0;
}
