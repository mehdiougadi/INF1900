#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

#define GREEN Color::green
#define RED Color::red
#define AMBER Color::amber
#define CLOSED Color::closed

//Les constantes de délais
const uint8_t delayButton=5;
uint8_t delay;
void setIOPorts()
{
    //Mode input au port D
    DDRD &= ~(1 << PD2);

    //Mode output au port B
    DDRB |= ( (1 << PB1) | (1<< PB0) );

}

bool buttonIsPressed()
{
    if (PIND & 0x04)
    {
        _delay_ms(delayButton);
        return (PIND & 0x04);
    }
    return false;
}

enum class Color {red, green, amber, closed};

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

            //La couleur verte et rouge alterne pour donner un jaune ambré
            setDelColor(GREEN);
            _delay_ms(delayButton*2);
            setDelColor(RED);
            _delay_ms(delayButton-4);
            break;

        case CLOSED:

            //Le DEL fermé signifique que le port B est 0x00 
            PORTB &= ~( (1 << PA0) | (1 << PA1) );
            break;
    }
}

void blinkingLED(Color color)
{
    setDelColor(color);
    _delay_ms(delay);
    setDelColor(color);
    _delay_ms(delay);
}

void problem1()
{
    uint8_t counter = 0;
    while(true)
    {

        //Si le button est appuyé
        if(buttonIsPressed())
        {
            while(buttonIsPressed())
            {
                if(counter==120)
                {
                    break;
                }
                counter+=10;
                _delay_ms(1000);
            }

            //la lumière clignote vert pendant 1/2 seconde
            delay=25;
            for(int i=0;i<10;i++)
            {
                blinkingLED(GREEN);
            }

            //Attendre 2 secondes
            _delay_ms(2000);
            
            //Le LED clignote (compteur / 2) fois au rythme de 2 fois par seconde 
            delay=250;
            for(int i=0;i<int(counter/2);i++)
            {
                blinkingLED(RED);
                blinkingLED(RED);
            }

            //la lumière tourne au vert pendant une seconde
            setDelColor(GREEN);
            _delay_ms(1000);
        }
    }
}

int main()
{
    setIOPorts();

    //Problème 1
    problem1();

}