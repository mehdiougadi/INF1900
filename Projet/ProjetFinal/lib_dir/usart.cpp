#include "usart.h"

USART::USART()
{
    // 2400 bauds
    UBRR0H = 0;
    UBRR0L = 0xCF;
    //Permet réception et transmission par UART0
    UCSR0B |= ( 1 << TXEN0) | (1 << RXEN0);
    //Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 );
}

void USART::transmissionUART ( uint8_t data )
{
    while ( ! ( UCSR0A & ( 1 << UDRE0 ) ) ) {};
    UDR0 = data;
}

uint8_t USART::receive()
{
    while ( ! ( UCSR0A & ( 1 << RXC0 ) ) ) {};
    return UDR0;
}

void USART::sendMessage(uint8_t message[], uint8_t messageLength)
{
    for ( uint8_t i = 0; i < messageLength; i++)
    {
        transmissionUART(message[i]);
    }
}