// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#include "LED.h"

LED::LED()
{
    DDRB |= ( ( 1 << PINB0) | ( 1 << PINB1 ) );
}

void LED::colorGreen()
{
    PORTB &= ( 0 << PB1 );
    PORTB |= ( 1 << PB0 );
}
 void LED::noColor()
{
    PORTB &= ( 0 << PB0 );
    PORTB &= ( 0 << PB1 );
}

void LED::colorRed()
{
    PORTB &= ( 0 << PB0 );
    PORTB |= ( 1 << PB1 );
}

void LED::colorAmber()
{
    colorGreen();
    _delay_ms(10);
    colorRed();
    _delay_ms(5);
}