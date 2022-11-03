#include "sound.h"

SOUND::SOUND()
{
    //ports
}

void SOUND::playSound(uint8_t note)
{
    TIMER timer0(waveform::ctc, compare::toggle); //compare??

    //switch-case
}

void SOUND::stopSound()
{

}