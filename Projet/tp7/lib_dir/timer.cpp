// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#include "timer.h"

timer::timer(waveform mode1, compare mode2)
{
    currentMode1 = mode1;
    currentMode2 = mode2;
    TCNT1 = 0;
    TCCR1B &= ~(1 << CS11);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 = (1 << OCIE1A);
}
void timer::waveformMode()
{
    switch (currentMode1) 
    {
        case waveform::normalMode:
            TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
            TCCR1B &= ~((1 << WGM11) | (1 << WGM12));
            break;
        case waveform::ctc:
            TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
            TCCR1B &= ~((1 << WGM13));
            TCCR1B |= (1 << WGM12);
            break;
    }
}
void timer::compareMode()
{
    switch (currentMode2) 
    {
        case compare::toggle:
            TCCR1A &= ~(1 << COM1A1);
            TCCR1A |= (1 << COM1A0);
            break;
        case compare::setLow:
            TCCR1A &= ~(1 << COM1A0);
            TCCR1A |= (1 << COM1A1);
            break;
        case compare::setHigh:
            TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
            break;
        case compare::off:
            TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
            break;
    }
}
void timer::timeTraduction (uint8_t time, uint16_t prescaler)
{
    uint16_t period = prescaler / F_CPU;
    uint16_t timeCounter = time / period;
    OCR1A = timeCounter;
}