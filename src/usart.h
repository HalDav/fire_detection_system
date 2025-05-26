#ifndef USART_H
#define USART_H

#define F_CPU 16000000UL
#define baud_rate 9600UL
#define ubrr_value ((F_CPU / (16UL * baud_rate))-1)

void usart_init();
void send_char(char c);
void send_string(char word[]);
void send_float(float float_number);
char get_char();
void get_string(char* buffer, uint8_t length);
float get_float(); 
void usart_flush();
#endif      