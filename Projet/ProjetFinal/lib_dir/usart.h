// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        31 octobre 2022

#ifndef UART_H
#define UART_H

#include <avr/io.h>

class Usart {
public:
    USART();
    void transmissionUART (uint8_t data);
    uint8_t receive();
    void sendMessage(uint8_t message[], uint8_t messageLength);
    void sendMessage(const char message[], uint8_t messageLength);
};

#endif