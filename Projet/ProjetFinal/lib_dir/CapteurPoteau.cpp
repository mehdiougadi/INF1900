#include "CapteurPoteau.h"

CapteurPoteau::CapteurPoteau()
{
    DDRA &= ~(1<<PA7);
}
uint8_t CapteurPoteau::readValueDM()
{
    return sensor.lecture(PIN) >> BITSHIFT;
}

void CapteurPoteau::distance()
{
    uint8_t value = readValueDM();
    if (value>=MEDIUM)
    {
        sonCapteur.playSound(81); //AIGUE
        motorDistance.stop();
        _delay_ms(1000);
    }
    else if(value<=MEDIUM && value>=FAR)
    {
        sonCapteur.playSound(45); //GRAVE
        moteurDistance.stop();
        _delay_ms(1000);
    }
    sonCapteur.stopSound();
}
