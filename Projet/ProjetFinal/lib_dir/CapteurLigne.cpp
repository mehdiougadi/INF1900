#include "CapteurLigne.h"

CapteurLigne::CapteurLigne()
{
    DDRA &= ~((1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) |  (1<<PA4) | (1<<PA5));
    DDRA &= ~(1<<PA7);
}

uint8_t CapteurLigne::readValueDM()
{
    uint8_t value = sensor.lecture(PIN) >> BITSHIFT;
    _delay_ms(40);
    uint8_t value2 = sensor.lecture(PIN) >> BITSHIFT;
    if (value<=CLOSE && value>=FAR)
    {
        if((value<=CLOSE && value>=MEDIUM) && (value2<=CLOSE && value2>=MEDIUM)){return value;}
        else if((value<=MEDIUM && value>=FAR) && (value2<=MEDIUM && value2>=FAR)){return value;}
        else{return ZERO;}
        }
    else
    {
        return ONE;
    }
}

bool CapteurLigne::distance()
{
    uint8_t value = readValueDM();
    use.transmissionUART(value);
    if (value>=MEDIUM && value<=CLOSE)
    {
        grave = false;
        return false;
    }
    else if(value<=MEDIUM && value>=FAR)
    {
        grave =true;
        return false;
    }
    else if (value<FAR)
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
    bool postIsNotHere = distance();
    if(postIsNotHere)
    {
        updateCondition();
        switch(isON)
        {
            case usedValue::ZERO:
                motorCapteur.stop();
                break;
            case usedValue::ONE:
                if      (DS3){ motorCapteur.moveStraight(45);}
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
                _delay_ms(10);
                mem.ecriture(0x01,P1);
                _delay_ms(10);
                mem.ecriture(0x02,P2);
                _delay_ms(10);
                mem.ecriture(0x03,P3);
                _delay_ms(10);
                motorCapteur.stop();
                break;
            default:
                break;       
        }
    }
    else
    {
        nbrPoteau ++;
        if (grave == false)
        {
            if(nbrPoteau==1){P1=1;}
            else if(nbrPoteau==2){P2=1;}
            else if(nbrPoteau==3){P3=1;}
            motorCapteur.stop();
            sonCapteur.playSound(81);
            _delay_ms(1000);
            sonCapteur.stopSound();

        }
        else
        {
            if(nbrPoteau==1){P1=2;}
            else if(nbrPoteau==2){P2=2;}
            else if(nbrPoteau==3){P3=2;}
            motorCapteur.stop();
            sonCapteur.playSound(45);
            _delay_ms(1000);
            sonCapteur.stopSound();
        }
        for(uint16_t i=0;i<15;i++)
        {
            suivreLigneS();
            _delay_ms(100);
        }
    }
}

void CapteurLigne::suivreLigneB(uint8_t p1, uint8_t p2, uint8_t p3)
{
    updateCondition();
    if(counter==0)
    {
    use.transmissionUART(p1);
    use.transmissionUART(p2);
    use.transmissionUART(p3);
    counter++;
    }
    led.noColor();
    switch(isON)
    {
        case usedValue::ZERO:
            motorCapteur.stop();
            break;
        case usedValue::ONE:
            if      (DS3){ motorCapteur.moveStraight(50);}
            else if (DS4){ motorCapteur.turn(65,40);}
            else if (DS5)
            {                   
                while(true)
                {
                    updateCondition();
                    if(DS3){ break;}
                    motorCapteur.turn(50,20);
                }
            }
            else if (DS1)
            {                     
                while(true)
                {
                    updateCondition();
                    if(DS3){ break;}
                    motorCapteur.turn(20,50);
                }
            }
            else if (DS2){ motorCapteur.turn(40,65);}
            break;
        case usedValue::TWO:
            if     (DS1 && DS2){ motorCapteur.turn(40,50);}
            else if(DS5 && DS4){ motorCapteur.turn(50,40);}
            else if(DS2 && DS3){ motorCapteur.turn(40,50);}
            else if(DS4 && DS3){ motorCapteur.turn(50,40);}
            else if(!DS3 || (DS2 && DS3 && DS4) || (DS2 && DS4) || (DS1 && DS5))
            {
                if(p3==0x00)
                {   
                    if (!post1)
                    {
                        if(p1==0x01)
                        {
                            led.colorRed();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(50,20);
                            }
                        }
                        else if(p1==0x02)
                        {
                            led.colorGreen();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(20,50);
                            }
                        }
                        post1=false;
                    }
                    if (post1)
                    {
                        if(p2==0x01)
                        {
                            led.colorRed();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(50,20);
                            }
                        }
                        else if(p2==0x02)
                        {
                            led.colorGreen();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(20,50);
                            }
                        }
                        post1=false;
                    }
                }
                else
                {

                }
            }
            break;
        case usedValue::THREE:
            if(!DS3 || (DS2 && DS3 && DS4) || (DS2 && DS4) || (DS1 && DS5))
            {
                if(p3==0x00)
                {   
                    if (!post1)
                    {
                        if(p1==0x01)
                        {
                            led.colorRed();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(50,20);
                            }
                        }
                        else if(p1==0x02)
                        {
                            led.colorGreen();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(20,50);
                            }
                        }
                        post1=false;
                    }
                    if (post1)
                    {
                        if(p2==0x01)
                        {
                            led.colorRed();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(50,20);
                            }
                        }
                        else if(p2==0x02)
                        {
                            led.colorGreen();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(20,50);
                            }
                        }
                        post1=false;
                    }
                }
                else
                {

                }
            }
            else if(DS3 && DS4 && DS5)
            {
                if(counter2%2==0)
                {
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(20,50);
                    }
                    counter2++;
                }
                if(counter2!=0)
                {
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(50,20);
                    }
                    counter2++;
                }
            }
            else if(DS1 && DS2 && DS3)
            {
                if(counter2%2==0)
                {
                    
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(50,20);
                    }
                }
                if(counter2!=0)
                {
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(20,50);
                    }
                    counter2++;
                }
            } 
            break;
        case usedValue::FOUR:
            if(DS2 && DS3 && DS4 && DS5)
            {
                if(counter2%2==0)
                {
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(20,50);
                    }
                if(counter2!=0)
                {
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(50,20);
                    }
                    counter2++;
                }
                }
            }
            else if(DS1 && DS2 && DS3 && DS4)
            {
                if(counter2%2==0)
                {
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(50,20);
                    }
                }
                if(counter2!=0)
                {
                    motorCapteur.stop();
                    _delay_ms(1000);
                    motorCapteur.moveStraight(60);
                    _delay_ms(1000);
                    while(true)
                    {
                        updateCondition();
                        if(DS3){ break;}
                        motorCapteur.turn(20,50);
                    }
                    counter2++;
                }
            } 
            else if(!DS3 || (DS2 && DS3 && DS4) || (DS2 && DS4) || (DS1 && DS5))
            {
                if(p3==0x00)
                {   
                    if (!post1)
                    {
                        if(p1==0x01)
                        {
                            led.colorRed();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(50,20);
                            }
                        }
                        else if(p1==0x02)
                        {
                            led.colorGreen();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(20,50);
                            }
                        }
                        post1=false;
                    }
                    if (post1)
                    {
                        if(p2==0x01)
                        {
                            led.colorRed();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(50,20);
                            }
                        }
                        else if(p2==0x02)
                        {
                            led.colorGreen();
                            motorCapteur.stop();
                            _delay_ms(2000);
                            motorCapteur.moveStraight(60);
                            _delay_ms(1000);
                            while(true)
                            {
                                updateCondition();
                                if(DS3){ break;}
                                motorCapteur.turn(20,50);
                            }
                        }
                        post1=false;
                    }
                }
                else
                {

                }
            }
            break;
        case usedValue::FIVE:
            motorCapteur.stop();
            break;
        default:
            break;       
    }
}

void CapteurLigne::suivreLigneSimple()
{
    updateCondition();
    switch(isON)
    {
        case usedValue::ZERO:
            break;
        case usedValue::ONE:
            if      (DS3){ motorCapteur.moveStraight(60);}
            else if (DS4){ motorCapteur.turn(55,40);}
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
            else if (DS2){ motorCapteur.turn(40,55);}
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
void CapteurLigne::suivreLigneS()
{
    updateCondition();
    switch(isON)
    {
        case usedValue::ZERO:
            motorCapteur.stop();
            motorCapteur.moveBack(45);
            _delay_ms(2000);
            while(true)
            {
                    updateCondition();
                    motorCapteur.turn(55,0);
                    if(DS1){break;}
            }
            while(true)
            {
                    updateCondition();
                    motorCapteur.turn(0,50);
                    if(isON == usedValue::FIVE){break;}
            }
            motorCapteur.moveBack(50);
            _delay_ms(1500);
            motorCapteur.stop();
            _delay_ms(4000);
            break;
        case usedValue::ONE:
            if      (DS3){ motorCapteur.moveStraight(60);}
            else if (DS4){ motorCapteur.turn(55,40);}
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
            else if (DS2){ motorCapteur.turn(40,55);}
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

void CapteurLigne::Rebondissement()
{
    uint8_t leftSpeed= 70;
    uint8_t rightSpeed = 0;
    for(uint8_t i=0; i<4;i++)
    {
        updateCondition();
        while(!DS5)
        {
            updateCondition();
            motorCapteur.turn(leftSpeed,rightSpeed);
            if(DS5){ break;}
        }
        for(uint8_t i=0; i<100;i++)
        {
            motorCapteur.turn(rightSpeed,leftSpeed);
        }
        updateCondition();
        while(!DS1)
        {
            updateCondition();
            motorCapteur.turn(rightSpeed,leftSpeed);
            if(DS1){ break;}
        }
        for(uint8_t i=0; i<100;i++)
        {
            motorCapteur.turn(leftSpeed,rightSpeed);
        }
    }
    for(uint8_t i=0; i<100;i++)
    {
        motorCapteur.turn(leftSpeed,rightSpeed);
    }
    updateCondition();
    while(!DS5)
    {
        updateCondition();
        motorCapteur.turn(leftSpeed,rightSpeed);
        if(DS5){ break;}
    }
}


