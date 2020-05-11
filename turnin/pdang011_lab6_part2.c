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

enum States{Start, LED_0, LED_1, LED_2, Pause_Wait, Pause_Released} state;

unsigned char next;
unsigned char released;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = LED_0;
			break;
		case LED_0:
			state = ((~PINA & 0x01) && released) ? Pause_Wait : LED_1;
			next = LED_2;
			released = ((~PINA & 0x01) && (~released & 0x01)) ? 0x00 : 0x01;
			break;
		case LED_1:
			state = ((~PINA & 0x01) && released) ? Pause_Wait : next;
			released = ((~PINA & 0x01) && (~released & 0x01)) ? 0x00 : 0x01;
			break;
		case LED_2:
			state = ((~PINA & 0x01) && released) ? Pause_Wait : LED_1;
			next = LED_0;
			released = ((~PINA & 0x01) && (~released & 0x01)) ? 0x00 : 0x01;
			break;
		case Pause_Wait:
			state = ((~PINA & 0x01) && released) ? Pause_Wait : Pause_Released;
			break;
		case Pause_Released:
			if(~PINA & 0x01){
				state = Start;
				released = 0x00;
			}
			else{
				state = Pause_Released;
			}
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
		case Pause_Wait:
		case Pause_Released:
			break;
                default:
			PORTB = 0x00;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	state = Start;
	released = 0x01;
	TimerSet(300);
	TimerOn();
	
	while(1){
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}

    return 1;
}
