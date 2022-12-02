// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        02 decembre 2022

#include "memory.h"
#include "LED.h"
#include "usart.h"

int main()
{
    //Objet
    Usart transmit;
    Memory mem;
    Led led;

    uint16_t address = 0x00;
    uint8_t data;

    while (true)
    {
       mem.lecture(address, &data);
        transmit.transmissionUART(data);
        _delay_ms(500);
        address++;
    }
}