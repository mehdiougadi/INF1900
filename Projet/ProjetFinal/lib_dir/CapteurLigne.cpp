#include "CapteurLigne.h"

CapteurLigne::CapteurLigne()
{
    DDRA &= ~((1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) |  (1<<PA4) | (1<<PA5));
    DDRA &= ~(1<<PA7);
}

uint8_t CapteurLigne::readValueDM()
{
    _delay_ms(20);
    use.transmissionUART(sensor.lecture(PIN) >> BITSHIFT);
    return (sensor.lecture(PIN) >> BITSHIFT);
}


bool CapteurLigne::distance()
{
    if (readValueDM()>=MEDIUM && readValueDM()<=CLOSE)
    {
        grave = false;
        return false;
    }
    else if(readValueDM()<=MEDIUM && readValueDM()>=FAR)
    {
        grave =true;
        return false;
    }
    else if (readValueDM()<FAR)
    {
        return true;
    }
    return true;
}

void CapteurLigne::updateCondition()
{
    isON = ZERO;
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

void CapteurLigne::suivreLigneA()
{
    while(true)
    {
        if(distance()==true)
        {
            updateCondition();
            switch(isON)
            {
                case usedValue::ZERO:
                    motorCapteur.stop();
                    break;
                case usedValue::ONE:
                    if      (DS3){ motorCapteur.moveStraight(60);}
                    else if (DS4){ motorCapteur.turn(65,40);}
                    else if (DS5){                   
                        while(true)
                        {
                            updateCondition();
                            if(DS3){ break;}
                            motorCapteur.turn(50,20);
                        }}
                    else if (DS1){                     
                        while(true)
                        {
                            updateCondition();
                            if(DS3){ break;}
                            motorCapteur.turn(20,50);
                        }}
                    else if (DS2){ motorCapteur.turn(40,65);}
                    break;
                case usedValue::TWO:
                    if     (DS1 && DS2){ motorCapteur.turn(40,50);}
                    else if(DS5 && DS4){ motorCapteur.turn(50,40);}
                    else if(DS2 && DS3){ motorCapteur.turn(40,50);}
                    else if(DS4 && DS3){ motorCapteur.turn(50,40);}
                    break;
                case usedValue::THREE:
                    if(DS3 && DS4 && DS5)
                    {
                        motorCapteur.moveStraight(60);
                        _delay_ms(100);
                        while(true)
                        {
                            updateCondition();
                            if(DS3){ break;}
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
                            if(DS3){ break;}
                            motorCapteur.turn(20,50);
                        }
                    }
                    break;
                case usedValue::FOUR:
                    break;
                case usedValue::FIVE:
                    motorCapteur.stop();
                    break;
                default:
                    break;       
            }
        }
        else
        {
            if (grave == false)
            {
                motorCapteur.stop();
                sonCapteur.playSound(81);
                _delay_ms(1000);
                sonCapteur.stopSound();
                motorCapteur.moveStraight(50);
                for(uint16_t i = 0;i< 65000; i++)
                {
                    suivreLigneB();
                }
            }
            else
            {
                motorCapteur.stop();
                sonCapteur.playSound(45);
                _delay_ms(1000);
                sonCapteur.stopSound();
                motorCapteur.moveStraight(50);
                for(uint16_t i = 0;i< 65000; i++)
                {
                    suivreLigneB();
                }
            }
        }
    }
}

void CapteurLigne::suivreLigneB()
{
    updateCondition();
    switch(isON)
    {
        case usedValue::ZERO:
            motorCapteur.stop();
            break;
        case usedValue::ONE:
            if      (DS3){ motorCapteur.moveStraight(60);}
            else if (DS4){ motorCapteur.turn(65,40);}
            else if (DS5){                   
                while(true)
                {
                    updateCondition();
                    if(DS3){ break;}
                    motorCapteur.turn(50,20);
                }}
            else if (DS1){                     
                while(true)
                {
                    updateCondition();
                    if(DS3){ break;}
                    motorCapteur.turn(20,50);
                }}
            else if (DS2){ motorCapteur.turn(40,65);}
            break;
        case usedValue::TWO:
            if     (DS1 && DS2){ motorCapteur.turn(40,50);}
            else if(DS5 && DS4){ motorCapteur.turn(50,40);}
            else if(DS2 && DS3){ motorCapteur.turn(40,50);}
            else if(DS4 && DS3){ motorCapteur.turn(50,40);}
            break;
        case usedValue::THREE:
            if(DS3 && DS4 && DS5)
            {
                motorCapteur.moveStraight(60);
                _delay_ms(100);
                while(true)
                {
                    updateCondition();
                    if(DS3){ break;}
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
                    if(DS3){ break;}
                    motorCapteur.turn(20,50);
                }
            }
            else
            {
                motorCapteur.stop();
            }
            break;
        case usedValue::FOUR:
            break;
        case usedValue::FIVE:
            motorCapteur.stop();
            break;
        default:
            break;       
    }
}

void CapteurLigne::suivreLigneS()
{
    while(true)
    {
        updateCondition();
        switch(isON)
        {
            case usedValue::ZERO:
                parking =true;
                motorCapteur.stop();
                motorCapteur.moveBack(50);
                break;
            case usedValue::ONE:
                if      (DS3){ motorCapteur.moveStraight(60);}
                else if (DS4){ motorCapteur.turn(65,40);}
                else if (DS5){                   
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(50,20);
                    }}
                else if (DS1){                     
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(20,50);
                    }}
                else if (DS2){ motorCapteur.turn(40,65);}
                break;
            case usedValue::TWO:
                if     (DS1 && DS2){ motorCapteur.turn(40,50);}
                else if(DS5 && DS4){ motorCapteur.turn(50,40);}
                else if(DS2 && DS3){ motorCapteur.turn(40,50);}
                else if(DS4 && DS3){ motorCapteur.turn(50,40);}
                break;
            case usedValue::THREE:
                if(DS3 && DS4 && DS5)
                {
                    motorCapteur.moveStraight(60);
                    _delay_ms(100);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
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
                        if(DS3){ break;}
                        motorCapteur.turn(20,50);
                    }
                }
                break;
            case usedValue::FOUR:
                break;
            case usedValue::FIVE:
                motorCapteur.stop();
                break;
            default:
                break;       
        }
        if(parking)
        {
            motorCapteur.moveBack(60);
            _delay_ms(1900);
            while(true)
            {
                    updateCondition();
                    motorCapteur.turn(60,0);
                    if(DS1){break;}
            }
            while(true)
            {
                    updateCondition();
                    motorCapteur.turn(0,54);
                    if(isON == usedValue::FIVE){break;}
            }
            motorCapteur.moveBack(60);
            _delay_ms(1500);
            motorCapteur.stop();
            break;
        }
    }
}

void CapteurLigne::Rebondissement()
{
    uint8_t leftSpeed= 60;
    uint8_t rightSpeed = 40;
    while(true)
    {
        updateCondition();
        while(!DS5)
        {
            updateCondition();
            for(uint16_t i=0; i<100;i++)
            {
                motorCapteur.turn(leftSpeed,rightSpeed);
            }
            if(DS5){ break;}
        }

        updateCondition();
        while(!DS1)
        {
            updateCondition();
            for(uint16_t i=0; i<100;i++)
            {
                motorCapteur.turn(rightSpeed,leftSpeed);
            }
            if(DS1){ break;}
        }
    }
    
}


