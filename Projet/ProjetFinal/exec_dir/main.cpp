// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        03 novembre 2022

#include "robot.h"
#include <avr/interrupt.h>

volatile uint8_t gMinuterieExpiree=0;
uint16_t counter = 0;

ISR(TIMER2_COMPA_vect)
{
    if (counter!=90)
    {
        counter++;
        TCNT2 = 0;
    }
    else{gMinuterieExpiree=1;}
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

int main()
{
    Robot test;
    test.modeS();
}