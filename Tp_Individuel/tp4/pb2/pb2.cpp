#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"
#include <avr/interrupt.h>

uint16_t counter = 0;

/*
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
}*/

ISR(INT0_vect)
{
    counter =2;
}

ISR(INT1_vect)
{
    counter = 1;
}

void confirm()
{
    cli(); //Est une routine qui bloque toutes les interruptions
    DDRD &= ~( 1<< PD2);
    EICRA|=(1<<ISC00) | (1<<ISC01); //Rising edge Clock
    EIMSK|=(1<<INT0); //Ajuste le registre EIMSK de l'ATmega324PA pour permettre les interruptions externes
    sei(); //Permet de recevoir à nouveau des interruptions
}

void pending()
{
    cli(); //Est une routine qui bloque toutes les interruptions
    DDRD &= ~( 1<< PD3);
    EICRA|=(1<<ISC10) | (1<<ISC11); //Rising edge Clock
    EIMSK|=(1<<INT1); //Ajuste le registre EIMSK de l'ATmega324PA pour permettre les interruptions externes
    sei(); //Permet de recevoir à nouveau des interruptions
}

int main()
{
    DDRC  = 0xff;
    pending();
    confirm();

    while(true)
    {
        if(counter == 0){PORTC = 0x01;}
        else if(counter ==1){PORTC = 0x02;}
        else{PORTC = 0x00;}
    }

}