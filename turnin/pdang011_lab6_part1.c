/*	Author: Patrick Dang
 * 	Partner(s) Name: 
 *	Lab Section: 028
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Video Link: https://drive.google.com/file/d/16CqQcqn47kuLGRk8j-TVnfZtleIDLDai/view?usp=sharing 
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, LED_0, LED_1, LED_2} state;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = LED_0;
			break;
		case LED_0:
			state = LED_1;
			break;
		case LED_1:
			state = LED_2;
			break;
		case LED_2:
			state = LED_0;
			break;
		default:
			state = LED_0;
			break;
	}

	//State Actions
	switch(state){
		case Start:
			break;
		case LED_0:
			PORTB = 0x01;
			break;
                case LED_1:
			PORTB = 0x02;
			break;
                case LED_2:
			PORTB = 0x04;
			break;
                default:
			PORTB = 0x00;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	state = Start;
	TimerSet(1000);
	TimerOn();
	
	while(1){
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}

    }
    return 1;
}
