#include "CapteurLigne.h"



CapteurLigne::CapteurLigne()
{
    DDRA &= ~((1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) |  (1<<PA4) | (1<<PA5));
}
void CapteurLigne::updateCondition()
{
    isON = 0x00;
    DS1 = (PINA & pin5) == pin5;
    DS2 = (PINA & pin4) == pin4;
    DS3 = (PINA & pin3) == pin3;
    DS4 = (PINA & pin2) == pin2;
    DS5 = (PINA & pin1) == pin1;
    if (DS1) {isON++;}
    if (DS2) {isON++;}
    if (DS3) {isON++;}
    if (DS4) {isON++;}
    if (DS5) {isON++;}
}
void CapteurLigne::suivreLigne()
{
    updateCondition();
    if(isON>=0x04)
    {
        motorCapteur.stop();
    }
    else if(isON == 0x01 && DS3)
    {
        motorCapteur.moveStraight(40);
    }


    else if (isON ==0x02 && DS3 && DS4)
    {
        motorCapteur.turn(50,40);
    }
    else if (isON ==0x02 && DS3 && DS2)
    {
        motorCapteur.turn(40,50);
    }
    else if (isON ==0x01 && DS4)
    {
        motorCapteur.turn(60,40);
    }
    else if (isON ==0x01 && DS2)
    {
        motorCapteur.turn(40,60);
    }
    else if (isON ==0x01 && DS5)
    {
        motorCapteur.turn(70,40);
    }
    else if (isON ==0x01 && DS1)
    {
        motorCapteur.turn(40,70);
    }
    else 
    {
        motorCapteur.stop();
    }
}
