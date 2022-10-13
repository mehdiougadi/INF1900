#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

#define GREEN Color::green
#define RED Color::red
#define AMBER Color::amber
#define CLOSED Color::closed

//Constante utilisé
const uint8_t delay=5; 

enum class Color {red, green, amber, closed};

//Fonctions de base nécessaires 

void setIOPorts()
{
    //Mode input au port D
    DDRD &= ~(1 << PD2);

    //Mode output au port B
    DDRB |= ( (1 << PB1) | (1<< PB0) );

}

void setDelColor (Color color)
{
    switch (color)
    {
        case GREEN:

            //La couleur verte correspond à 0x01 sur le port B
            PORTB |= (1 << PB0);
            PORTB &= ~(1 << PB1);
            break;

        case RED:

            //La couleur rouge correspond à 0x02 sur le port B
            PORTB |= (1 << PB1);
            PORTB &= ~(1 << PB0);
            break;

        case AMBER:

            //Le DEL ambré signifie que le vert et le rouge alterne rapidement
            while(true)
            {
                setDelColor(GREEN);
                _delay_ms(delay*2);
                setDelColor(RED);
                _delay_ms(delay-4);
            }
            break;
    }
}

void problem2()
{
    while(true)
    {
        if()
        {
            setDelColor(GREEN);
        }
        else if()
        {
            setDelColor(AMBER);
        }
        else
        {
            setDelColor(RED);
        }
    }
}

int main()
{
    setIOPorts();
    problem2();
}

