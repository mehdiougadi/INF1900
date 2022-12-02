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
    _delay_ms(15);
    colorRed();
    _delay_ms(5);
}
    
void Led::clignoterVert()
{
    for(uint8_t i=0;i<10;i++)
    {
        colorGreen();
        _delay_ms(100);
        noColor();
        _delay_ms(100);
    }
}
void Led::clignoterRouge()
{
    for(uint8_t i=0;i<10;i++)
    {
        colorRed();
        _delay_ms(100);
        noColor();
        _delay_ms(100);
    }
}
void Led::clignoterAmbre()
{
    for(uint8_t i=0;i<10;i++)
    {
        for(uint8_t i=0;i<7;i++){
        colorGreen();
        _delay_ms(10);
        colorRed();
        _delay_ms(5);
 }
        noColor();
        _delay_ms(100);
    }
}