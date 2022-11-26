// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        03 novembre 2022

#include "robot.h"
#include <math.h>
#include <avr/interrupt.h>
Robot Sonic;

ISR(TIMER2_COMPA_vect)
{
    Sonic.gMinuterieExpiree=1;
}

void partirMinuterie(uint8_t duree)
{
    TCNT2=0;

    TCCR1A=(1<< WGM21); //Mode CTC
    TCCR2B=(1<< CS20)|(1<< CS21)|(1<< CS22); //prescale 1024
    
    TIMSK2=(1<<OCIE2A); //Interrupt comp A

    OCR2A=duree;
    
}

int main()
{
    Robot sonic;
    sonic.modeA();
}