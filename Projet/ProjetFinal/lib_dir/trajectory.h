#include "Robot.h"

//Section d'interruption
volatile uint8_t counter=0x01;

enum Mode
{
    mode1=0x01;
    mode2=0x02;
    mode3=0x03;
}

ISR(INT0_vect)
{
    if(counter>=0x01 && counter<=0x03)
    {
        changeMode(++counter);
    }
    else
    {
        changeMode(Mode::mode1);
    }
}

void initInterrupt()
{
    cli(); //Est une routine qui bloque toutes les interruptions

    DDRD &= ~( 1<< PD2);

    EICRA|=(1<<ISC00) | (1<<ISC01); //Rising edge Clock

    EIMSK|=(1<<INT0); //Ajuste le registre EIMSK de l'ATmega324PA pour permettre les interruptions externes

    sei(); //Permet de recevoir à nouveau des interruptions
}

//Section de code
uint8_t changeMode(Mode mode)
{
    switch(mode)
    {
        case mode::mode1:
            break;
        case mode::mode2:
            break;
        case mode::mode3:
            break;
    }
}

void trajectory()
{

}