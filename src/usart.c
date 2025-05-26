#include <avr/io.h>
#include "usart.h"


void usart_init(){
    UCSR0A &= ~(1 << U2X0);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0B &= ~(1 << UCSZ02);
    UCSR0C &= ~(1 << UMSEL00) | (1 << UMSEL01);
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    UBRR0H = (ubrr_value >> 8);
    UBRR0L = ubrr_value;
}

void send_char(char c){
   while(!(UCSR0A & (1 << UDRE0))){

   }
   UDR0 = c;
}
void send_string(char word[]){

}
void send_float(float float_number){

}
char get_char(){
    
}
void get_string(char* buffer, uint8_t length){

}
float get_float(){

}
void usart_flush(){

}