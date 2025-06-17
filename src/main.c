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
         
        usart_flush();
        send_string("\nInput character: ");
        _delay_ms(10);
        char c = get_char();
        _delay_ms(10);
        send_string("\nYour char is: ");
        send_char(c);
        send_string("\nFloat number: ");
        send_float(7.3256);

    }

    return 0;
}
