#include "CapteurLigne.h"



CapteurLigne::CapteurLigne()
{
    DDRA &= ~((1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) |  (1<<PA4) | (1<<PA5));
}
void CapteurLigne::jumpStart()
{
    motorCapteur.moveStraight(100);
    _delay_ms(100);
}

void CapteurLigne::updateCondition()
{
    isON = 0x00;
    DS1 = (PINA & pin5) == pin5;
    DS2 = (PINA & pin4) == pin4;
    DS3 = (PINA & pin3) == pin3;
    DS4 = (PINA & pin2) == pin2;
    DS5 = (PINA & pin1) == pin1;
}
void CapteurLigne::suivreLigne()
{
    updateCondition();
    if(DS1 && DS2 && DS3 && DS4 && DS5)
    {
        motorCapteur.stop();
    }
    else if(DS3 && DS4 && DS5)
    {
        motorCapteur.moveStraight(60);
        _delay_ms(500);
        while(!DS3)
        {
            updateCondition();
            motorCapteur.turn(40,0);
        }
    }
    else if(DS1 && DS2 && DS3)
    {
        motorCapteur.moveStraight(60);
        _delay_ms(500);
        while(!DS3)
        {
            updateCondition();
            motorCapteur.turn(0,35);
        }
    }
    else if(DS1 && DS2)
    {
        motorCapteur.turn(0,50);
    }
    else if(DS5 && DS4)
    {
        motorCapteur.turn(50,0);
    }
    else if(DS2 && DS3)
    {
        motorCapteur.turn(0,50);
    }
    else if(DS4 && DS3)
    {
        motorCapteur.turn(50,0);
    }
    else if (DS3)
    {
        motorCapteur.moveStraight(60);
    }
        else if (DS4)
    {
        motorCapteur.turn(50,0);
    }
        else if (DS5)
    {
        motorCapteur.turn(50,0);
    }
        else if (DS1)
    {
        motorCapteur.turn(0,50);
    }
            else if (DS2)
    {
        motorCapteur.turn(0,50);
    }
    else
    {
        motorCapteur.stop();
    }
}
