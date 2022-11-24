#include "CapteurLigne.h"



CapteurLigne::CapteurLigne()
{
    DDRA &= ~((1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) |  (1<<PA4) | (1<<PA5));
}

void CapteurLigne::updateCondition()
{
    isON=0x00;
    DS1 = (PINA & pin5) == pin5;
    DS2 = (PINA & pin4) == pin4;
    DS3 = (PINA & pin3) == pin3;
    DS4 = (PINA & pin2) == pin2;
    DS5 = (PINA & pin1) == pin1;
    if(DS1){isON++;}
    if(DS2){isON++;}
    if(DS3){isON++;}
    if(DS4){isON++;}
    if(DS5){isON++;}
}

void CapteurLigne::suivreLigne()
{
        updateCondition();
        switch(isON)
        {
            case 0x01:
                if (DS3)
                {
                    motorCapteur.moveStraight(55);
                }
                else if (DS4)
                {
                    motorCapteur.turn(65,40);
                }
                else if (DS5)
                {
                    motorCapteur.turn(75,40);
                }
                else if (DS1)
                {
                    motorCapteur.turn(40,75);
                }
                else if (DS2)
                {
                    motorCapteur.turn(40,65);
                }
                break;
            case 0x02:
                else if(DS1 && DS2)
                {
                    motorCapteur.turn(40,50);
                }
                else if(DS5 && DS4)
                {
                    motorCapteur.turn(50,40);
                }
                else if(DS2 && DS3)
                {
                    motorCapteur.turn(40,50);
                }
                else if(DS4 && DS3)
                {
                    motorCapteur.turn(50,40);
                }
                break;
            case 0x03:
                break;
            default:
                break;
        }
        if(DS1 && DS2 && DS3 && DS4 && DS5)
        {
            motorCapteur.stop();
        }
        else if(DS3 && DS4 && DS5)
        {
            motorCapteur.moveStraight(60);
            _delay_ms(100);
            while(true)
            {
                updateCondition();
                if(DS3)
                {
                    break;
                }
                motorCapteur.turn(50,20);
            }
        }
        else if(DS1 && DS2 && DS3)
        {
            motorCapteur.moveStraight(35);
            _delay_ms(100);
            while(true)
            {
                updateCondition();
                if(DS3)
                {
                    break;
                }
                motorCapteur.turn(20,50);
            }
        }
        else
        {}
}

/*
void CapteurLigne::Rebondissement()
{
    counter = 0x00;
    uint8_t leftSpeed= 70;
    uint8_t rightSpeed = 50;
    uint8_t temp;
    while(true)
    {
        while(!DS1 && ((counter%0x02)==0x00))
        {
            updateCondition();
            if(DS1)
            {
                counter++;
            }
            motorCapteur.turn(leftSpeed,rightSpeed);
        }

        temp = leftSpeed;
        leftSpeed = rightSpeed;
        rightSpeed = leftSpeed;

        while(DS1 && ((counter%0x02) !=0x00))
        {
            updateCondition();
        }
    }
}
*/
