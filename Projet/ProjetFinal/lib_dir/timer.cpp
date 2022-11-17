#include "timer.h"

TIMER::TIMER(WAVEFORM mode1, COMPARE mode2)
{
    currentMode1 = mode1;
    currentMode2 = mode2;
    TCNT1 = 0;
    TCCR1B &= ~(1 << CS11);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 = (1 << OCIE1A);
}

void TIMER::waveformMode()
{
    switch (currentMode1) 
    {
        case WAVEFORM::normalMode:
            TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
            TCCR1B &= ~((1 << WGM11) | (1 << WGM12));
            break;

        case WAVEFORM::ctc:
            TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
            TCCR1B &= ~((1 << WGM13));
            TCCR1B |= (1 << WGM12);
            break;
    }
}

void TIMER::compareMode()
{
    switch (currentMode2) 
    {
        case COMPARE::toggle:
            TCCR1A &= ~(1 << COM1A1);
            TCCR1A |= (1 << COM1A0);
            break;

        case COMPARE::setLow:
            TCCR1A &= ~(1 << COM1A0);
            TCCR1A |= (1 << COM1A1);
            break;

        case COMPARE::setHigh:
            TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
            break;

        case COMPARE::off:
            TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
            break;
    }
}

void TIMER::timeTraduction (uint8_t time, uint16_t prescaler)
{
    uint16_t period = prescaler / F_CPU;
    uint16_t timeCounter = time / period;
    OCR1A = timeCounter;
}