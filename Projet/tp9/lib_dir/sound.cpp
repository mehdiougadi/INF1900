#include "sound.h"

SOUND::SOUND()
{
    DDRB |= (1 << PB2);
    TCCR0A |= (1<<WGM11)|(1<<COM0A1)|(1<<COM0B1)|(1<<COM0A0)|(1<<COM0B0);
	TCCR0B |= (1<< CS01); //prescaler à 8
}

void SOUND::playSound(uint8_t note)
{
    
}

void SOUND::stopSound()
{
    OCR0A = 0xFF;
}