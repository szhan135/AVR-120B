/*	Author: szhan135
 *  Partner(s) Name: Carlos Pacheco
 *	Lab Section:
 *	Assignment: Lab # 3 Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char GetBit(unsigned char temp1, unsigned char temp2){//helper function from zybook
	return ((temp1 & (0x01 << temp2))!=0);
}
unsigned char SetBit(unsigned char temp1, unsigned char temp2, unsigned char temp3){
	return (temp3 ? temp1 | (0x01 << temp2):temp1 & ~(0x01<<temp2));
}
int main(void)
{
    DDRA = 0xFF; PORTA = 0x00; // Configure port A's 8 pins as outputs
    DDRB = 0xFE; PORTB = 0x01; // Configure port B's bit 0 pin as input, bits 1-7 as outputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs,
	DDRD = 0x00; PORTD = 0xFF; // Configure port D's 8 pins as inputs,
    // initialize to 0s
    unsigned char inputB = 0x00; //PORTB and PORTD signify 9 bit input
	unsigned char outputB2 = 0x00;//temp value to hold output for bits 1-7
    unsigned char outputA = 0x00;	//output of PORTD, PORTA and PORTC signify 9 bit output
    unsigned char outputC = 0x00;	//output of PORTB bit 0
	unsigned char inputD = 0x00;

    while (1) 
    {
		inputD = PIND & 0xFF;							//Set inputs
		inputB = PINB & 0x01;							
		
		if ((inputB + inputD) >= 0x46){					//if total sum of portB and portD is greater than or equal to 70, airbag is enabled
		
			outputB2 = SetBit(outputB2, 1, 1);			//bit 1 signifies airbag enable
			outputB2 = SetBit(outputB2, 2, 0);			//airbag disable is set off
		}
		else if(((inputB + inputD) > 0x05) & ((inputB + inputD) < 0x46)){		//if total is between 5 and 70, airbag is disabled
	
			outputB2 = SetBit(outputB2, 1, 0);			//airbag enable is off
			outputB2 = SetBit(outputB2, 2, 1);			//airbag disable is on
			outputB2 = 0x04;
		}
		else if((inputB + inputD) <= 0x05){				//total weight less than 5 means no passenger
    		outputB2 = SetBit(outputB2, 1, 0);			//airbag enable is off
    		outputB2 = SetBit(outputB2, 2, 0);			//airbag disable is off
		}
		outputA = (outputA & 0x00) | inputD;			
		outputC = (outputC & 0x00) | inputB;			

		PORTA = outputA;
		PORTC = outputC;								//To set output ports
		PORTD = inputD;
		PORTB = outputB2;
    }
	return 0;
}

