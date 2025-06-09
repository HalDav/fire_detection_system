/*
Project: Fire detection system

*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart.h"


#define EMERGENCY_LIGHT PB0

void interrupt_init(){
    EICRA |= (1 << ISC10) | (1 << ISC11) | (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 <<  INT1) | (1 << INT0);
    sei();
}

ISR(INT0_vect){
    _delay_ms(100);
    PORTB ^= (1 << PB0);    //testing ISR
}

ISR(INT1_vect){
    _delay_ms(100);
    PORTB ^= (1 << PB0);        //testing ISR
}


int main(void) {
    DDRD  |= (1 << PD2) | (1 << PD3);       //INT0 and INT1 as input 
    PORTD |= (1 << PD2) | (1 << PD3);       //INT0 and INT1 pull up resistor activation
    DDRB = (1 << EMERGENCY_LIGHT);          //EMERGENCY_LIGHT init

    interrupt_init();
    usart_init();
    

    while (1) {
        send_string("Input float: ");
        usart_flush();
        float c = get_float();
        send_string("Your float is: ");
        send_float(c);
        send_string(" \n");
        _delay_ms(250);


    }

    return 0;
}
