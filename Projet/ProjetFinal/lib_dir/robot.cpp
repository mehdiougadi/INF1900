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
        if (counter!=90)
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

    else if (gMinuterieExpiree ==0)
    {
        if (counter!=190)
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
    else if (gMinuterieExpiree ==1)
    {
        if (counter!=565)
        {
            counter++;
            TCNT2 = 0;
        }
        else
        {
            gMinuterieExpiree=2;
            counter = 0;
        }
    }
    else if (gMinuterieExpiree ==2)
    {
        if (counter!=540)
        {
            counter++;
            TCNT2 = 0;
        }
        else
        {
            gMinuterieExpiree=3;
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
        speaker.introSong();
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
       mem.lecture(0x01, &p1);
       _delay_ms(15);
       mem.lecture(0x02, &p2);
       _delay_ms(15);
       mem.lecture(0x03, &p3);
       _delay_ms(15);
        led.clignoterRouge();
        mainMoteur.turn(55,58);
        _delay_ms(800);
        startingB = false;
    }
    partirMinuterie(255);
    while(gMinuterieExpiree==0){capteurIR.suivreLigneSimple();}
    mainMoteur.stop();
    _delay_ms(1000);
    partirMinuterie(255);
    while(gMinuterieExpiree==1){capteurIR.suivreLigneB(p1,p2,p3);}
    mainMoteur.stop();
    _delay_ms(1000);
    partirMinuterie(255);
    while(gMinuterieExpiree==2){capteurIR.suivreLigneB(p1,p2,p3);}
    mainMoteur.stop();
    _delay_ms(1000);
    while(gMinuterieExpiree==3){capteurIR.suivreLigneSimple();}
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
