#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"
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
    DDRD = 0xff;
    partirMinuterie(255);

    do
    {
        PORTD =0xff;
        PORTC =0xff;
    }while(gMinuterieExpiree == 0 );

    OCR2A =0;

    if (gMinuterieExpiree == 1)
    {
        PORTD =0x00;
        PORTC =0x00;
    }

}