#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include "usart.h"


void usart_init(){
    UCSR0A &= ~(1 << U2X0);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0B &= ~(1 << UCSZ02);
    UCSR0C &= ~((1 << UMSEL00) | (1 << UMSEL01));
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    UBRR0H = (ubrr_value >> 8);
    UBRR0L = ubrr_value;
}

void send_char(char c){
   while(!(UCSR0A & (1 << UDRE0))){

   }
   UDR0 = c;
}

void send_string(const char *word){
    for(int j = 0; word[j] != '\0'; j++){
        send_char(word[j]);
    }
}

void send_float(float float_number){
    char buffer[40];
    dtostrf(float_number, 0, 4, buffer);
    send_string(buffer);
}

char get_char(){
    while(!(UCSR0A & (1 << RXC0)));
    return UDR0;
    
}

/* 
float get_float(){
    char buffer[40];
    int j = 0;
    while(j < (sizeof(buffer)-1)){
        char c = get_char();
        if(c == '\r'){
            continue;
        }
        if(c == '\n'){
            break;
        }
        
        buffer[j] = c;
        j++;
    }
    buffer[j] = '\0';

    send_string(buffer);

    return (float)atof(buffer);
} */

void usart_flush() {
    while (UCSR0A & (1 << RXC0)) {
        volatile char dummy = UDR0; 
    }
}