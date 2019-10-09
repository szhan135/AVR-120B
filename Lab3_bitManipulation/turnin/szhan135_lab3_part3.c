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
unsigned char getBit(unsigned char temp1, unsigned char temp2){//helper function from zybook
	return ((temp1 & (0x01 << temp2))!=0);
}
unsigned char setBit(unsigned char temp1, unsigned char temp2, unsigned char temp3){
	return (temp3 ? temp1 | (0x01 << temp2):temp1 & ~(0x01<<temp2));
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00 ; PORTA = 0x00 ;			//configure A's 8 pins as
											//inputs
//    DDRB = 0x00 ; PORTB = 0xFF ;            //configure B's 8 pins as
//                                            //inputs
	DDRC = 0xFF ; PORTC = 0x00 ;			//configure C's 8 pins as
											//outputs
											
	//create intermediate vars in order to read from PINx
	unsigned char intermediateA = 0x00 ;
	//unsigned char intermediateB = 0x00 ;
	unsigned char intermediateC = 0x00 ;
//    //create int i = 0 that will be used in the for loop inside while()
      int i = 0 ;
//    //same thing for j
//    int j = 0 ;

    /* Insert your solution below */
    
    //create read vars for A, B, C
//    int readA = 0x00 ;
//    int readB = 0x00 ;
//    int readC = 0x00 ;
    
    //read from PINA and PINB using 0xFF in order to copy
    //directly from PINA and PINB
    //intermediateA = PINA & 0xFF ;
    //intermediateB = PINB & 0xFF ;
    
    while (1) {
        //read from PINA
        intermediateA = PINA & 0xFF ;
        
        //if bits are 1 or 2, then light 5 is on
        if(intermediateA == 0x01 || intermediateA == 0x02){
            for(i = 0; i < 8; i++){
                if(i == 5 || i == 6){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        //bits 4-5 are on
        else if(intermediateA == 0x03 || intermediateA == 0x04){
            for(i = 0; i < 8; i++){
                if(i == 4 || i == 5 || i == 6){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x05 || intermediateA == 0x06){
            for(i = 0; i < 8; i++){
                if(i == 3 || i == 4 || i == 5){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x07 || intermediateA == 0x08 || intermediateA == 0x09){
            for(i = 0; i < 8; i++){
                if(i == 2 || i == 3 || i == 4){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x0A || intermediateA == 0x0B || intermediateA == 0x0C){
            for(i = 0; i < 8; i++){
                if(i == 1 || i == 2 || i == 3 || i == 4){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x0D || intermediateA == 0x0E || intermediateA == 0x0F){
            for(i = 0; i < 8; i++){
                if(i == 1 || i == 2 || i == 3 || i == 4 || i == 0 || i == 5){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        //begin turning on seatbelt icon
        else if(intermediateA == 0x31 || intermediateA == 0x32){
            for(i = 0; i < 8; i++){
                if(i == 7 || i == 5){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x33 || intermediateA == 0x34){
            for(i = 0; i < 8; i++){
                if(i == 7 || i == 4 || i == 5){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x35 || intermediateA == 0x36){
            for(i = 0; i < 8; i++){
                if(i == 7 || i == 4 || i == 5 || i == 3){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x37 || intermediateA == 0x38 || intermediateA == 0x39){
            for(i = 0; i < 8; i++){
                if(i == 7 || i == 4 || i == 5 || i == 3 || i == 2){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x3A || intermediateA == 0x3B || intermediateA == 0x3C){
            for(i = 0; i < 8; i++){
                if(i == 7 || i == 4 || i == 5 || i == 3 || i == 2 || i == 1){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else if(intermediateA == 0x3D || intermediateA == 0x3E || intermediateA == 0x3F){
            for(i = 0; i < 8; i++){
                if(i == 7 || i == 4 || i == 5 || i == 3 || i == 2 || i == 1 || i == 0){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        else{
            for(i = 0; i < 8; i++){
                if(i == 6){
                    intermediateC = setBit(intermediateC, i, 1) ;
                }
                else{
                    intermediateC = setBit(intermediateC, i, 0) ;
                }
            }
        }
        //give intermediateC value into PORTC
        PORTC = intermediateC ;
    }
    return 0;
}

