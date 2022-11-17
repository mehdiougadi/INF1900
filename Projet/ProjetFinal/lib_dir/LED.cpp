// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        31 octobre 2022

#include "LED.h"

Led::Led()
{
    DDRC |= ( ( 1 << PINC6) | ( 1 << PINC7 ) );
}

void Led::colorGreen()
{
    PORTC &= ( 0 << PC7 );
    PORTC |= ( 1 << PC6 );
}

void Led::noColor()
{
    PORTC &= ( 0 << PC6 );
    PORTC &= ( 0 << PC7 );
}

void Led::colorRed()
{
    PORTC &= ( 0 << PC6 );
    PORTC |= ( 1 << PC7 );
}

void Led::colorAmber()
{
    colorGreen();
    _delay_ms(10);
    colorRed();
    _delay_ms(5);
}