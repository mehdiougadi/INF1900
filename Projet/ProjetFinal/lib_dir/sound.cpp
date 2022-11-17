#include "sound.h"

Sound::SOUND()
{
    DDRB |= (1 << PB3);
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);
    TCCR0B |= (1 << CS02);
}

void Sound::playSound(uint8_t note)
{
    PORTB |= (1 << PB2);
    double frequenceNote = boardFrequency[note - 45];
    OCR0A = 8000000 * (1 / frequenceNote) / 2 / 256;
}

void Sound::stopSound()
{
   PORTB &= ~(1 << PB2);
}

void Sound::introSong()
{
    playSound(64);
    _delay_ms(200);

    stopSound();
    
    _delay_ms(8);
    playSound(64);
    _delay_ms(208);

    stopSound();

    _delay_ms(208);
    playSound(64);
    _delay_ms(208);

    stopSound();

    _delay_ms(208);
    playSound(60);
    _delay_ms(208);
    playSound(64);
    _delay_ms(208);

    stopSound();

    _delay_ms(208);
    playSound(67);
    _delay_ms(208);

    stopSound();

    _delay_ms(624);
    playSound(55);
    _delay_ms(208);

    stopSound();
}

void Sound::outroSong()
{
    playSound(71);
    _delay_ms(300);
    playSound(77);
    _delay_ms(150);

    stopSound();

    _delay_ms(450);
    playSound(77);
    _delay_ms(290);

    stopSound();

    _delay_ms(10);
    playSound(77);
    _delay_ms(300);
    playSound(76);
    _delay_ms(300);
    playSound(74);
    _delay_ms(300);
    playSound(72);
    _delay_ms(300);
    playSound(64);
    _delay_ms(150);

    stopSound();

    _delay_ms(300);
    playSound(64);
    _delay_ms(150);
    playSound(60);
    _delay_ms(150);

    stopSound();
}
