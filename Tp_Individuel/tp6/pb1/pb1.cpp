#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

#define GREEN Color::green
#define RED Color::red
#define AMBER Color::amber
#define CLOSED Color::closed



void setIOPorts()
{
    //Mode input au port D
    DDRD &= ~(1 << PD2);

    //Mode output au port B
    DDRB |= ( (1 << PB1) | (1<< PB0) );

}

//Cette fonction établie un delay de temps  en millisecondes
void msDelay(int delay)
{
    for(int i=0; i < delay ;i++)
    {
        _delay_ms(1);
    }
}

bool buttonIsPressed()
{
    if (PIND & 0x04)
    {
        //Pour s'assurer que le button est bien appuyé on met un delay de 5 ms
        msDelay(5);
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

        case CLOSED:

            //Le DEL fermé signifique que le port B est 0x00 
            PORTB &= ~( (1 << PA0) | (1 << PA1) );
            break;
    }
}

void blinkingLED(Color color,int delay)
{
    setDelColor(color);
    msDelay(delay);
    setDelColor(Color::closed);
    msDelay(delay);
}

//Fonction que résout la situation dans l'énoncé
void problem1()
{
    uint8_t counter = 0;
    while(true)
    {

        if(buttonIsPressed())
        {
            while(buttonIsPressed())
            {
                //Si le compteur atteint 120, on sort de la  while
                if(counter==120)
                {
                    break;
                }
                //On incrémente 10 au compteur à chaque seconde
                counter+=10;
                msDelay(1000);
            }

            //la lumière clignote vert pendant 1/2 seconde
            for(int i=0;i<10;i++)
            {
                blinkingLED(GREEN,25);
            }

            //Attendre 2 secondes
            msDelay(2000);
            
            //Le LED clignote (compteur / 2) fois au rythme de 2 fois par seconde
            for(int i=0;i<int(counter/2);i++)
            {
                blinkingLED(RED,250);
                blinkingLED(RED,250);
            }

            //la lumière tourne au vert pendant une seconde
            setDelColor(GREEN);
            msDelay(1000);
        }
    }
}

int main()
{
    setIOPorts();
    problem1();
}