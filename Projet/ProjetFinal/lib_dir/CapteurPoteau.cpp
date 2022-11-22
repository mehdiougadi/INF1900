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
        son.playSound(81); //AIGUE
        _delay_ms(1000);
    }
    else if(value<=MEDIUM && value>=FAR)
    {
        son.playSound(45); //GRAVE
        _delay_ms(1000);
    }
    son.stopSound();
}
