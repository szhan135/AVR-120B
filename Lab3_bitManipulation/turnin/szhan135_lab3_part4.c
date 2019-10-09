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
unsigned char getBit(unsigned char x, unsigned char k) ;
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) ;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00 ; PORTA = 0x00 ;			//configure A's 8 pins as
											//inputs
    DDRB = 0x0F ; PORTB = 0x00 ;            //configure B's 8 pins as
                                            //inputs
	DDRC = 0xF0 ; PORTC = 0x00 ;			//configure C's 8 pins as
											//outputs
											
	//create intermediate vars in order to read from PINx
	unsigned char intermediateA = 0x00 ;
	unsigned char intermediateB = 0x00 ;
	unsigned char intermediateC = 0x00 ;
//    //create int i = 0 that will be used in the for loop inside while()
      int i = 0 ;
//    //same thing for j
//    int j = 0 ;

    /* Insert your solution below */
    
    //read from PINA and PINB using 0xFF in order to copy
    //directly from PINA and PINB
//    intermediateA = PINA & 0xFF ;
    //intermediateB = PINB & 0xFF ;
    
    
    while (1) {
        //create vars for shift vals
        int x = 0 ;
        int shiftB = 0x00 ;
        int shiftC = 0x00 ;
        //read from PINA
        intermediateA = PINA & 0xFF ;
        
        for(i = 4; i < 8; i++){
            if(getBit(intermediateA, i)){
                x = 1;
                intermediateB = setBit(intermediateB, 0, x) ;
                intermediateB = intermediateB * 2
                //increase count for B
                shiftB = shiftB + 0x01 ;
                
                if(shiftB == 0x04){
                    //if shiftB = 4, then divide by 2 in order to right shift once
                    intermediateB = intermediateB / 2 ;
                }
            }
            else{
                x = 0x00 ;
                intermediateB = setBit(intermediateB, 0, x) ;
                intermediateB = intermediateB * 2 ;
                shiftB = shiftB + 0x01 ;
                if(shiftB == 0x04){
                    //if shiftB = 4, then divide by 2 in order to right shift once
                    intermediateB = intermediateB / 2 ;
                }
            }
        }
        for(i = 0; i < 4; i++){
            if(getBit(intermediateA, i)){
                x = 1;
                intermediateC = setBit(intermediateC, 4, x) ;
                intermediateC = intermediateC * 2 ;
                shiftC = shiftC + 0x01 ;
                if(shiftC = 0x04){
                    shiftC = shiftC / 2;
                }
            }
            else{
                x = 0x00 ;
                intermediateC = setBit(intermediateC, 0, x) ;
                intermediateC = intermediateC * 2 ;
                shiftC = shiftC + 0x01 ;
                if(shiftC == 0x04){
                    intermediateC = intermediateC / 2 ;
                }
            }
        }
        //give PORTB and PORTC the vals we got
        PORTB = intermediateB ;
        PORTC = intermediateC ;
    }
    return 1;
}

unsigned char setBit(unsigned char x, unsigned char k, unsigned char b){
    return (b ? x|(0x01 << k) : x& ~(0x01 <<k)) ;
}

unsigned char getBit(unsigned char x, unsigned char k){
	return ((x & (0x01 << k)) != 0) ;
}

