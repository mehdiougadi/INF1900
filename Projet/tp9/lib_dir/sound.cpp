#include "sound.h"

TIMER timer0(waveform::ctc, compare::toggle); //compare??

SOUND::SOUND()
{
    //ports du haut-parleur
}

void SOUND::playSound(uint8_t note)
{
    TIMER timer0(waveform::ctc, compare::toggle);

    //switch-case
}

void SOUND::stopSound()
{

}