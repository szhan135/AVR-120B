/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab #1  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;//use port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00;//use port B's pins as output
	unsigned char inputSensor = 0x00;// Hold the input value
	unsigned char outLED = 0x00;//output to B0
    /* Insert your solution below */
    while (1) {
	inputSensor = PINA & 0x03; // set up inputs and read
	if (inputSensor = 0x01){
		outLED = (outLED & 0xFC)|0x01;//only focus on the very first two bits of outLed;the only case that LED is on;
}	
	else {
		outLED = (outLED & 0xFC)|0x00;//else,LED is off	
		}
	PORTB = outLED; //write output	
    }	
    return 1;
}
