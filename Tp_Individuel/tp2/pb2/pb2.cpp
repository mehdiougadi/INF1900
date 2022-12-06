#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

const uint8_t delay= 5;

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

//Énumération des États
enum etat{INIT,E1,E2,E3,E4,E5};

//Algorithme pour probleme 2
void problem2()
{
    //État initial
    etat state=INIT;

    while(true)
    {

        //Changement d'état
        switch (state)
            {
                case INIT:
                    //Couleur rouge dans INIT
                    setDelColor(color::red);

                    //Si Button est appuyé, change d'état
                    if(buttonPressed())
                    {
                      state=E1;
                    }
                    break;

                case E1:
                    //Couleur ambré dans E1
                    setDelColor(color::amber);

                    //Si le button est relaché, change d'état
                    if (!buttonPressed())
                    {
                        state = E2;
                    }
                    break;

                case E2:
                    //Couleur vert dans E2
                    setDelColor(color::green);

                    //Si le button est appuyé, change d'état
                    if (buttonPressed())
                    {
                        state = E3;
                    }
                    break;

                case E3:
                    //Couleur rouge dans E3
                    setDelColor(color::red);

                    //Si le button est relaché, change d'état
                    if (!buttonPressed())
                    {
                        state = E4;
                    }
                    break;

                case E4:
                    //Le LED est fermé dans E4
                    setDelColor(color::closed);

                    //Si le button est appuyé, change d'état
                    if (buttonPressed())
                    {
                        state = E5;
                    }
                    break;

                case E5:
                    //Couleur vert dans E5
                    setDelColor(color::green);
                    //si le button est relaché, change d'état
                    if (!buttonPressed())
                    {
                        state = INIT;
                    }
                    break;

            } 
        }
}

int main()
{
    DDRB = 0b11111111;

    PORTB = 0xff;

}