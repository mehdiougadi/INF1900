// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#include "usart.h"

usart::usart()
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A |= ( 1 << RXC0 ) | ( 1 << TXC0 );
    UCSR0B |= ( 1 << TXEN0 );
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 );
}

void usart::transmissionUART ( uint8_t data )
{
    while ( ! ( UCSR0A & ( 1 << UDRE0 ) ) ){};
    UDR0 = data;
}

uint8_t usart::receive()
{
    while ( ! ( UCSR0A & ( 1 << RXC0 ) ) ){};
    
    return UDR0;
}

void usart::sendMessage(uint8_t message[], uint8_t messageLength)
{
    for ( uint8_t i = 0; i < messageLength; i++) {
        usart::transmissionUART(message[i]);
    }
}