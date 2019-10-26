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
volatile unsigned char TimerFlag = 0; //TimerISR() sets this to a 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; //Start count from here, down to 0. Default to 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1 ms ticks

void TimerOn()
{
	//AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B; //bit3 = 0: CTC mode (clear timer on compare)
	//bit2bit1bit0 = 011: pre-scaler /64
	// 00001011: 0x0B
	// so, 8MHz clock or 8,000,000 /64 =125,000 ticks/s
	// Thus, TCNT1 register will count as 125,000 ticks/s
	//AVR output compare register OCR1A.
	OCR1A = 125;   // Timer interrupt will be generated when TCNT1 == OCR1A
	// We want a 1 ms tick. 0.001s *125,000 ticks/s = 125
	// so when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	//AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	// Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |=0x80; // 0x80: 1000000

}

void TimerOff()
{
	TCCR1B = 0x00; // bit3bitbit0 -000: Timer off
}

void TimerISR()
{
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{
	//CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) //results in a more efficient compare
	{
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
//Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

typedef enum States {init, waitA0, pressA0, waitA1, pressA1, reset} States;
int buttonState (int);

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	
	TimerSet(1000);
	TimerOn();
	LCD_ClearScreen(void);	

    /* Insert your solution below */
	States state = init;
	
    while (1) {
	state = buttonState(state);
	while(!TimerFlag);
	TimerFlag = 0;
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
			if(temp != 9){ 
				temp = temp + 1;
			}
			break;
		case waitA0:
			state = !A0? init: waitA0;
			if(temp != 9){ 
				temp = temp + 1;
			}
			break;
		case pressA1:
			state = waitA1;
			if (temp != 0){
				temp = temp - 1;
			}
			break;
		case waitA1:
			state = !A1? init: waitA1;
			if (temp != 0){
				temp = temp - 1;
			}
			break;
		case reset:
			temp = 0;
			if(!(A0 | A1)){
				state = init;
			}
			LCD_WriteData( temp + ‘0’ );
			break;
	}
	return state;
}
