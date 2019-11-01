/*	Author: kmaka003
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_inti (){
	ADCSRA |= (1 << ADEN) |= (1 <<  ADSC) |= (1 << ADATE);
}


void SM ();

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
		

    /* Insert your solution below */
	unsigned char tempB;
	unsgned char tempD;
    while (1) {
	ADC_intt();
	SM9();
    }
    return 1;
}

void SM(){
	unsigned short tempADC = ADC;
	tempB = (char)tempADC;
	tempD = (char)(tempADC >> 8);
	PORTB = tempB;
	PORTD = tempD;
}
	
