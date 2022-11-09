#include "sound.h"
#include "LED.h"

SOUND::SOUND()
{
    DDRB |= (1 << PB3);
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);
    TCCR0B |= (1 << CS02);
}

void SOUND::playSound(uint8_t note)
{
    PORTB |= (1 << PB2);
    double frequenceNote = boardFrequency[note - 45];
    OCR0A = 8000000 * (1 / frequenceNote) / 2 / 256;
}

void SOUND::stopSound()
{
   PORTB &= ~(1 << PB2);
}
