#ifndef UART_H
#define UART_H

#include <avr/io.h>

class usart {
public:
    usart();
    void transmissionUART (uint8_t data);
    uint8_t receive();
    void sendMessage(uint8_t message[], uint8_t messageLength);
    void sendMessage(const char message[], uint8_t messageLength);
};


#endif