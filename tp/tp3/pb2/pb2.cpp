#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

//Ports
void setIOPorts()
{
    //Mode output
    DDRB |= ((1<< PB1) | (1<< PB0));
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

void mydelay(int n)
{
    while(n--)
    {
        _delay_us(5);
    }
}

void rotation(int a,int b)
{
    for(int i=0;i<120;i++)
    {
        PORTB=0x02;
        mydelay(a);
        PORTB=0x00;
        mydelay(b-a);
    }
}


int main()
{
    setIOPorts();


    //Sur 60Hz
    int b=16666;
    int a=0;
    int counter=0;

    while(counter<5)
    {
        switch (a)
        {
            case 0:

                PORTB=0x00;
                _delay_ms(2000);
                a=4166;
                counter++;
                break;

            case 4166:

                rotation(a,b);
                a=8333;
                counter++;
                break;

            case 8333:

                rotation(a,b);
                a=12499;
                counter++;
                break;

            case 12499:

                rotation(a,b);
                a=16666;
                counter++;
                break;

            case 16666:

                rotation(a,b);
                a=0;
                counter++;
                break;                                                            
        }   
    } 
}
