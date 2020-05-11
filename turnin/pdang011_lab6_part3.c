/*	Author: Patrick Dang
 * 	Partner(s) Name: 
 *	Lab Section: 028
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * 	Video Link: https://drive.google.com/file/d/16XvoyGTKD0i1WleeKZji8uEtYGJhBhLa/view?usp=sharing 
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Wait_Press, Increment, Decrement, Reset} state;

unsigned char LED;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = Wait_Press;
			LED = 0x07;
			PORTB = LED;
			break;
		case Wait_Press:
		case Increment:
		case Decrement:
		case Reset:
			if((~PINA & 0x01) && (~PINA & 0x02)){
				state = Reset;
			}
			else if(~PINA & 0x01){
				state = Increment;
			}
			else if (~PINA & 0x02){
				state = Decrement;
			}
			else{
				state = Wait_Press;
			}
			break;
		default:
			state = Start;
			break;
	}

	//State Actions
	switch(state){
		case Start:
			break;
		case Wait_Press:
			break;
		case Increment:
		       	PORTB = (LED < 0x09) ? ++LED : LED;
			break;
		case Decrement:
			PORTB = (LED > 0x00) ? --LED : LED;
			break;
		case Reset:
			LED = 0x00;
			PORTB = 0x00;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	state = Start;
	TimerSet(100);
	TimerOn();
	
	while(1){
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}

    }
    return 1;
}
