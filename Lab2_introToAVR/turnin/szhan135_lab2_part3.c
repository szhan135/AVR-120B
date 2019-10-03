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
    unsigned char temp = 0x00; //Hold the value of A - represents the binary of a four space parking lot
    unsigned char cntavail = 0x00; //Hold the count of available parking spaces - set to c
	
    while (1) 
    {
		temp = PINA & 0x0F;		// 1) Read input from PINA
		
		if (temp == 0x0F) {		//first condition when spaces are full
			cntavail = (cntavail & 0xF0) | 0x08;		//no space left
		}
		else if (temp == 0x07 || temp == 0x0B || temp == 0x0D || temp == 0x0E) {
			cntavail = (cntavail & 0xF0) | 0x01;		//only one available
		}
		else if (temp == 0x03 || temp == 0x05 || temp == 0x06 || temp == 0x09 || temp == 0x0A || temp == 0x0C){
			cntavail = (cntavail & 0xF0) | 0x02;		//two available
		}
		else if (temp == 0x01 || temp == 0x02 || temp == 0x04 || temp == 0x08) {
			cntavail = (cntavail & 0xF0) | 0x03;
		}
		else if (temp == 0x00){
			cntavail = (cntavail & 0xF0) | 0x04;
		}
		// 3) set up cntavail as output
		PORTC = cntavail;
		 			}
 		return 0;
}

