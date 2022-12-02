 #include "robot.h"

volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gMinuterieExpiree2 = 0;
volatile uint16_t counter = 0;
volatile bool startingA = true;
volatile bool startingB = true;
volatile bool startingC = true;

ISR(TIMER2_COMPA_vect)
{
    
    if(gMinuterieExpiree2==0)
    {
        if (counter!=110)
        {
            counter++;
            TCNT2 = 0;
        }
        else
        {
            gMinuterieExpiree2=1;
            counter = 0;
        }
    }

    if (gMinuterieExpiree ==0)
    {
        if (counter!=830)
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
    if(startingA)
    {
        led.clignoterVert();
        mainMoteur.turn(55,58);
        _delay_ms(800);
        startingA = false;
    }
    capteurIR.suivreLigneA();
}

void Robot::modeB()
{
    if(startingB)
    {
        led.clignoterRouge();
        mainMoteur.turn(55,58);
        _delay_ms(800);
        startingB = false;
    }
    partirMinuterie(255);
    while(gMinuterieExpiree == 0){capteurIR.suivreLigneB();}
    mainMoteur.stop();
}

void Robot::modeS()
{
    if(startingC)
    {
        led.clignoterAmbre();
        mainMoteur.turn(55,58);
        _delay_ms(800);
        startingC = false;
    }
    partirMinuterie(255);
    while(gMinuterieExpiree2 == 0){capteurIR.suivreLigneS();}
    capteurIR.Rebondissement();
    while(gMinuterieExpiree2 == 1){capteurIR.suivreLigneS();}
}
