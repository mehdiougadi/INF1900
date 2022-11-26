#include "CapteurPoteau.h"

CapteurPoteau::CapteurPoteau()
{
    DDRA &= ~(1<<PA7);
}
uint8_t CapteurPoteau::readValueDM()
{
    return sensor.lecture(PIN) >> BITSHIFT;
}

bool CapteurPoteau::distance()
{
    _delay_ms(30);
    use.transmissionUART(readValueDM());
    _delay_ms(500);
    if (readValueDM()>=MEDIUM && readValueDM()<=CLOSE)
    {
        return false;
    }
    else if(readValueDM()<=MEDIUM && readValueDM()>=FAR)
    {
        return false;
    }
    else if (readValueDM()<FAR)
    {
        return true;
    }
    return true;
}
