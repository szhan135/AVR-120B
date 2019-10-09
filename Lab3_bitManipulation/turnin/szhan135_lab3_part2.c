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
unsigned char GetBit(unsigned char temp1, unsigned char temp2){//helper function from zybook
	return ((temp1 & (0x01 << temp2))!=0);
}
unsigned char SetBit(unsigned char temp1, unsigned char temp2, unsigned char temp3){
	return (temp3 ? temp1 | (0x01 << temp2):temp1 & ~(0x01<<temp2));
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //inputs
	//DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x7F; PORTC = 0x00; //outputs
    /* Insert your solution below */
    unsigned char inputA=0x00;
    //unsigned char inputB;
    unsigned char outputC=0x00;
    while (1) {
		//unsigned char temp = 0;
		//unsigned char i = 0;
		inputA = PINA & 0xFF;
		//inputB = PINB & 0xFF;
		if ((inputA == 0x01) || (inputA == 0x02)){	//when fuel level is 1 or 2, bit 5 is one
			outputC = SetBit(outputC, 0, 0);			//when low fuel icon, bit 6 is one
			outputC = SetBit(outputC, 1, 0);
			outputC = SetBit(outputC, 2, 0);
			outputC = SetBit(outputC, 3, 0);
			outputC = SetBit(outputC, 4, 0);
			outputC= SetBit(outputC, 5, 1);		//when set bit 5 to 1
			outputC = SetBit(outputC, 6, 1);
		}
		else if ((inputA == 0x03) || (inputA == 0x04)){   //when bits 4-5 are on
			outputC = SetBit(outputC, 0, 0);
			outputC = SetBit(outputC, 1, 0);
			outputC = SetBit(outputC, 2, 0);
			outputC = SetBit(outputC, 3, 0);
			outputC = SetBit(outputC, 4, 1);
			outputC = SetBit(outputC, 5, 1);
			outputC = SetBit(outputC, 6, 1);
		}
		else if ((inputA == 0x05) || (inputA == 0x06)){  //low fuel icon is off because fuel's above 4
			outputC = SetBit(outputC, 0, 0);				 //when bits 3-5 are on 
			outputC = SetBit(outputC, 1, 0);
			outputC = SetBit(outputC, 2, 0);
			outputC = SetBit(outputC, 3, 1);
			outputC = SetBit(outputC, 4, 1);
			outputC = SetBit(outputC, 5, 1);
			outputC = SetBit(outputC, 6, 0);
		}
		else if ((inputA == 0x07) || (inputA == 0x08) || (inputA == 0x09)){   //case when bits 2-5 are on 
			outputC = SetBit(outputC, 0, 0);				
			outputC = SetBit(outputC, 1, 0);
			outputC = SetBit(outputC, 2, 1);
			outputC = SetBit(outputC, 3, 1);
			outputC = SetBit(outputC, 4, 1);
			outputC = SetBit(outputC, 5, 1);
			outputC = SetBit(outputC, 6, 0);
		}
		else if ((inputA == 0x0A) || (inputA == 0x0B) || (inputA == 0x0C)){  //when bits 1-5 are on 
			outputC = SetBit(outputC, 0, 0);
			outputC = SetBit(outputC, 1, 1);
			outputC = SetBit(outputC, 2, 1);
			outputC = SetBit(outputC, 3, 1);
			outputC = SetBit(outputC, 4, 1);
			outputC = SetBit(outputC, 5, 1);
			outputC = SetBit(outputC, 6, 0);
		}
		else if ((inputA == 0x0D) || (inputA == 0x0E) || (inputA == 0x0F)){  //when bits 0-5 are on 
			outputC = SetBit(outputC, 0, 1);
			outputC = SetBit(outputC, 1, 1);
			outputC = SetBit(outputC, 2, 1);
			outputC = SetBit(outputC, 3, 1);
			outputC = SetBit(outputC, 4, 1);
			outputC = SetBit(outputC, 5, 1);
			outputC = SetBit(outputC, 6, 0);
		}
		else{					// only low fuel icon is on when no fuel
			outputC = SetBit(outputC, 6, 1);
			outputC = SetBit(outputC, 5, 0);
			outputC = SetBit(outputC, 4, 0);
			outputC = SetBit(outputC, 3, 0);
			outputC = SetBit(outputC, 2, 0);
			outputC = SetBit(outputC, 1, 0);
			outputC = SetBit(outputC, 0, 0);
		}
		PORTC = outputC;
    }
    return 0;
}
