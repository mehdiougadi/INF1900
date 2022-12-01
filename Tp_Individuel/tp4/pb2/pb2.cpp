#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

volatile uint8_t counter=0x00;

ISR(INT0_vect)
{
    counter =1;
}

ISR(INT1_vect)
{
    counter =2;
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
    while(true)
    {
        if(counter =1){PORTC =0x01;}
        else if(counter =1){PORTC =0x02;}
        else {PORTC = 0x00;}
    }

}