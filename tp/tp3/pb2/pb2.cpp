#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

//Ports
void setIOPorts()
{
    //Mode output
    DDRA |= ((1<< PA1) | (1<< PA0));
}

//Couleur
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
            _delay_ms(2);
            setDelColor(color::red);
            _delay_ms(4);

            break;

        case color::closed:
            PORTA &= ~((1<<PA0) | (1<<PA1));
            break;
    }
}

//Le button a été appuyé
bool buttonPressed()
{
    if (PIND & 0x04)
    {
        _delay_ms(10);
        return (PIND & 0x04);
    }
    return false;
}

int main()
{

    
}
