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

typedef enum States {init, waitA0, pressA0, waitA1, pressA1, reset} States;
int buttonState (int);

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;



	

    /* Insert your solution below */
	States state = init;
	
    while (1) {
	state = buttonState(state);
    }
    return 1;
}

int buttonState (int state){
	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;

	if(A0 && A1){
		state = reset;
	}
	switch (state) {
		case init:
			state = A0? pressA0: init;
			state = A1? pressA1: state;
			break;
		case pressA0:
			state = waitA0;
			if(PORTC != 9){ 
				PORTC = PORTC + 1;
			}
			break;
		case waitA0:
			state = !A0? init: waitA0;
			break;
		case pressA1:
			state = waitA1;
			if (PORTC != 0){
				PORTC = PORTC - 1;
			}
			break;
		case waitA1:
			state = !A1? init: waitA1;
			break;
		case reset:
			PORTC = 0;
			if(!(A0 | A1)){
				state = init;
			}
			break;
	}
	return state;
}
