 #include "robot.h"

uint8_t gMinuterieExpiree = 0;
uint16_t counter = 0;

ISR(TIMER2_COMPA_vect)
{
    if(gMinuterieExpiree==0)
    {
        if (counter!=110)
        {
            counter++;
            TCNT2 = 0;
        }
        else
        {
            gMinuterieExpiree=1;
            counter = 0;
        }
    }
}
void partirMinuterie(uint8_t duree)
{
    cli();
    TCNT2=0;

    TCCR2A|=(1<< COM2A0); //Mode CTC
    TCCR2B|=(1<< CS20)|(1<< CS22)|(1<< WGM21); //prescale 1024
    
    TIMSK2|=(1<<OCIE2A); //Interrupt comp A

    OCR2A=duree;
    sei();
}

void Robot::modeA()
{
    capteurIR.suivreLigneA();
}

void Robot::modeB()
{
    partirMinuterie(255);
    while(gMinuterieExpiree == 0){capteurIR.suivreLigneB();}
}

void Robot::modeS()
{
    partirMinuterie(255);
    while(gMinuterieExpiree == 0){capteurIR.suivreLigneS();}
    capteurIR.Rebondissement();
    while(gMinuterieExpiree == 1){capteurIR.suivreLigneS();}
}
