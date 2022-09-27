#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"
#include <avr/interrupt.h>

//Constante de Delay
const uint8_t delay= 5;

//Initialisation des entrées et sorties
void setIOPorts()
{
    //Mode input
    DDRD &= ~( 1<< PD2);

    //Mode output
    DDRA |= ((1<< PA1) | (1<< PA0));

}

//Le button a été appuyé
bool buttonPressed()
{
    if (PIND & 0x04)
    {
        _delay_ms(delay);
        return (PIND & 0x04);
    }
    return false;
}

//Liaison entre le port et les couleurs
enum class color{red, green, amber, closed};

void setDelColor(color color)
{
    switch (color)
    {
        case color::green:
            PORTA |= (1<<PA0);
            PORTA &= ~(1<<PA1);
            break;

        case color::red:
            PORTA |= (1<<PA1);
            PORTA &= ~(1<<PA0);
            break;

        case color::amber:

            setDelColor(color::green);
            _delay_ms(delay*2);
            setDelColor(color::red);
            _delay_ms(delay-4);

            break;

        case color::closed:
            PORTA &= ~((1<<PA0) | (1<<PA1));
            break;
    }
}

volatile uint8_t gMinuterieExpiree=0;
volatile uint8_t gBoutonPoussoir=0;

ISR(TIMER1_COMPA_vect)
{
    gMinuterieExpiree=1;
}

ISR(INT0_vect)
{
    gBoutonPoussoir=1;
    _delay_ms(30);
}

void partirMinuterie(uint16_t duree)
{
    TCNT1=0;

    TCCR1A=(1<< WGM12); //Mode CTC
    TCCR1B=(1<< CS10)|(1<< CS12); //prescale 1024
    TCCR1C=0;
    
    TIMSK1=(1<<OCIE1A); //Interrupt comp A

    OCR1A=duree;
    
}

void initInterrupt()
{
    cli(); //Est une routine qui bloque toutes les interruptions

    setIOPorts();

    EICRA|=(1<<ISC10) | (1<<ISC11); //Rising edge Clock

    EIMSK|=(1<<INT0); //Ajuste le registre EIMSK de l'ATmega324PA pour permettre les interruptions externes

    sei(); //Permet de recevoir à nouveau des interruptions
}

int main()
{;
    initInterrupt();

    _delay_ms(3000);
    setDelColor(color::red);
    _delay_ms(100);
    setDelColor(color::closed);

    partirMinuterie(7812);

    do
    {

    }while(gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );

    cli();

    if (gMinuterieExpiree == 1 && gBoutonPoussoir==0)
    {
        setDelColor(color::red);
    }

    else if(gBoutonPoussoir ==1 && gMinuterieExpiree==0)
    {
        setDelColor(color::green);
    }

    
}