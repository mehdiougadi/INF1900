#define F_CPU 8000000

//Color values
#define DEL_GREEN 1
#define DEL_RED 2
#define DEL_CLOSED 0

#include <util/delay.h>
#include "avr/io.h"
#include <avr/interrupt.h>

bool ButtonPressed()
{
    uint8_t data= (PIND & 0x04);
    if (data!= 0)
    {
        _delay_us(50);
        return data;
    }
    return false;
}

void setIOPorts()
{
    //Mode input
    DDRD = 0x00;

    //Mode output
    DDRA = 0xff;

}

void setDELcolor(uint8_t x)
{
    if (x==1)
    {
        PORTA = DEL_GREEN;
    }

    else if (x==2)
    {
        PORTA = DEL_RED;
    }
    else
    {
        PORTA = DEL_CLOSED;
    }
}

void setDELcolorYellow(const int delay)
{
    for(int i=0;i<delay;i++)
    {
        setDELcolor(1);
        _delay_us(60);
        setDELcolor(2);
        _delay_us(10);
    }
}


int main()
{
    setIOPorts();

    while(true)
    {
        setDELcolor(0);
        if(ButtonPressed())
        {
            setDELcolor(1);
            _delay_ms(2000);
            if (ButtonPressed())
            {  
                setDELcolor(2);
                _delay_ms(2000);
                if (ButtonPressed())
                {
                    while(true)
                    {
                    setDELcolorYellow(2000);
                    if (ButtonPressed())
                    {
                        continue;
                    }
                    else
                    {
                        setDELcolor(0);
                        break;
                    }
                    } 
                }
                setDELcolor(0);
            }
            setDELcolor(0);
        }
    }
}

