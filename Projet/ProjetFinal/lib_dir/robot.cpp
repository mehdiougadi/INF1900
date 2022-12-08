// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        15 novembre 2022
 
#include "robot.h"

volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gMinuterieExpiree2 = 0;
volatile uint16_t counter = 0;
volatile bool startingA = true;
volatile bool startingB = true;
volatile bool startingC = true;
volatile bool ONCE = true;

ISR(TIMER2_COMPA_vect)
{
    //PARTIE S
    if(gMinuterieExpiree2==0)
    {
        if (counter!=95)
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
    
    //PARTIE B
    else if (gMinuterieExpiree ==0)
    {
        if (counter!=310)
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
        if (counter!=600)
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
        if (counter!=310)
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

    else if (gMinuterieExpiree ==3)
    {
        if (counter!=110)
        {
            counter++;
            TCNT2 = 0;
        }

        else
        {
            gMinuterieExpiree=4;
            counter = 0;
        }
    }

    else if (gMinuterieExpiree ==4)
    {
        if (counter!=62)
        {
            counter++;
            TCNT2 = 0;
        }

        else
        {
            gMinuterieExpiree=5;
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
        _delay_ms(1000);
        startingA = false;
    }
    capteurIR.suivreLigneA();
}

void Robot::modeB()
{
    if(ONCE)
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
            _delay_ms(1000);
            startingB = false;
        }
        
        //Etape 1
        partirMinuterie(255);
        while(gMinuterieExpiree==0){capteurIR.suivreLigneSimple();}
        mainMoteur.stop();
        _delay_ms(1000);

        //Etape 2
        partirMinuterie(255);
        while(gMinuterieExpiree==1){capteurIR.suivreLigneB(p1,p2,p3);}

        /*
        Pour se tourner vers le poteau du milieu
        
        mainMoteur.stop();
        _delay_ms(2000);
        switch(p3)
        {
            case 0x00:
                mainMoteur.moveStraight(45);
                _delay_ms(500);
                mainMoteur.moveBack(45);
                _delay_ms(500);
                break;
            case 0x01:
                mainMoteur.turn(40,45);
                _delay_ms(500);
                mainMoteur.turn(45,40);
                _delay_ms(500); 
                break;
            case 0x02:
                mainMoteur.turn(45,40);
                _delay_ms(500);
                mainMoteur.turn(40,45);
                _delay_ms(500);
                break;
        }
        */
        mainMoteur.stop();
        _delay_ms(1000);
        
        //Etape 3
        partirMinuterie(255);
        while(gMinuterieExpiree==2){capteurIR.suivreLigneB(p1,p2,p3);}

        //Etape 4
        partirMinuterie(255);
        while(gMinuterieExpiree==3){capteurIR.suivreLigneSimple();}

        //Etape 5
        partirMinuterie(255);
        while(gMinuterieExpiree==4){capteurIR.suivreLigneB(p1,p2,p3);}
        while(gMinuterieExpiree==5){capteurIR.suivreLigneSimple();}
        ONCE = false;
    }
    //if(capteurIR.isPointS){modeS();} // Pour cottinuer sans arret au mode S apres mode B
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
    capteurIR.rebondissement();
    while(gMinuterieExpiree2 == 1){capteurIR.suivreLigneS();}
}
