/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab #1  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void)
{
    DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    DDRB = 0x00; PORTB = 0x00;
    DDRD = 0xFF; PORTB = 0x00;
    
    //Have the varibles to hold the binary of four space parking lot
    unsigned char tempA = 0x00; 
    unsigned char tempB = 0x00; 
    unsigned char tempC = 0x00; 
    unsigned char tempD = 0x00; //To hold the output
	
    while (1) 
    {
		// 1) Read input from PINs
		tempA = PINA & 0xFF;		
		tempB = PINB & 0xFF;
		tempC = PINC & 0xFF;
		
		if (tempA + tempB + tempC > 0x8C) {		//If the sum is greater than 140
			tempD = (tempD & 0x00) | 0x01;		//PD0 = 1
		}
		else {
			tempD = (tempD & 0x00) | 0x00; 		//PD0 = 0
		}
		
		if (abs(tempA - tempC)>0x50){			//If the difference between A and C greater than 80
			tempD = (tempD & 0xFD) | 0x02; 		//PD1 = 1
		}
		if ((tempA + tempB + tempC)<= 0x8C) {
			int sum = tempA + tempB + tempC;
			tempD = (tempD & 0x00) | sum; 		//PD2-PD7 represents the sum of weight
		}

		// 3) Write tempD as output
		PORTD = tempD;
		 			}
 		return 0;
}

