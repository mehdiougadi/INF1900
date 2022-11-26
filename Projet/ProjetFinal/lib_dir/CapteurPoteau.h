#ifndef CAPTEURPOTEAU_H
#define CAPTEURPOTEAU_H

#include "can.h"
#include "sound.h"
#include <avr/io.h> 
#include <util/delay.h>
#include "motor.h"
#include "usart.h"
class CapteurPoteau{

    public:
        CapteurPoteau();
        uint8_t readValueDM();
        bool distance();
    private:
        Motor moteurDistance;
        Can sensor;
        Usart use;
        Sound sonCapteur;
        const uint8_t PIN = 0x07;

        //Constante
        const uint8_t BITSHIFT = 2;
        const uint8_t CLOSE = 255;
        const uint8_t MEDIUM = 77;
        const uint8_t FAR = 50;
        
};

#endif