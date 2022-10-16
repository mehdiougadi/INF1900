#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"
#include "can.cpp"

#define GREEN Color::green
#define RED Color::red
#define AMBER Color::amber
#define CLOSED Color::closed


/*On sait que

Si la lumière est basse, DEL == verte.
Si la lumière est à un bon niveau, DEL == ambré.
Si la lumière est trop forte,DEL == rouge.

Étant sur 5 volts, nous prendrons des valeurs subjectives en voltage, 
trouver le pourcentage de cette valeur au 5 volts et 
les convertir en numérique sur 8 bits relative

Nous avons établie les valeurs de high(80%) et low dans la section de constante

*/

//Constantes utilisées
const uint8_t delay=5; 
const uint8_t position = 0;
const uint8_t high = 204;
const uint8_t low = 128;

void setIOPorts()
{
    //Mode input au port A
    DDRA |= ~( (1 << PA1) | (1<< PA0) );

    //Mode output au port B
    DDRB |= ( (1 << PB1) | (1<< PB0) );

}

enum class Color {red, green, amber};

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
            setDelColor(GREEN);
            _delay_ms(delay*2);
            setDelColor(RED);
            _delay_ms(delay-4);
            break;
    }
}

//Fonction que résout la situation dans l'énoncé
void problem2()
{
    can photoresistor;
    uint8_t valueCan;
    uint16_t rawValue;

    while(true)
    {
        //La méthode lecture me renvoit une valeur sur 16 bit
        //et nous voulons les 8 bits les moins significatives comme input
        rawValue = photoresistor.lecture(position);
        valueCan= rawValue >> 2;
        
        if(valueCan < low)
        {
            setDelColor(GREEN);
        }
        else if(valueCan > high)
        {
            setDelColor(RED);
        }
        else
        {
            setDelColor(AMBER);
        }
    }
}

int main()
{
    setIOPorts();
    problem2();
}
//Problème avec le makefile peut pas avoir le  pb2.elf