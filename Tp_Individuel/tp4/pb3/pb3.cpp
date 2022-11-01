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
    DDRD = 0xff;

    //Mode output
    DDRA |= ((1<< PA1) | (1<< PA0));

    PORTA = 0x00; 

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

void ajustementPwm ( uint8_t valeurPWM ) {

// mise à un des sorties OC1A et OC1B sur comparaison
// réussie en mode PWM 8 bits, phase correcte
// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
// page 130 de la description technique du ATmega324PA)

OCR1A = valeurPWM;
OCR1B = valeurPWM;

// division d'horloge par 8 - implique une fréquence de PWM fixe


TCCR1A |= (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1)|(1<<COM1A0)|(1<<COM1B0);
//TCCR1B |= (1<< CS11); //prescaler à 8
TCCR1C |= 0;

}

int main()
{
    
    
    setIOPorts();

    /*ajustementPwm(0);
    _delay_ms(2000);
    ajustementPwm(64);
    _delay_ms(2000);
    ajustementPwm(128);
    _delay_ms(2000);
    ajustementPwm(191);
    _delay_ms(2000);
    ajustementPwm(255);
    _delay_ms(2000);*/
    

    TCCR1A |= (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1)|(1<<COM1A0)|(1<<COM1B0);
    TCCR1B |= (1<< CS11); //prescaler à 8
    TCCR1C = 0;
    OCR1A = 128;
    OCR1B = 128;
    _delay_ms(1000);
    OCR1A = 255;
    OCR1B = 255;
}