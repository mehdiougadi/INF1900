#ifndef SOUND_H
#define SOUND_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

class SOUND
{
public:
	SOUND();
	void playSound(uint8_t note);
	void stopSound();

private:

};

#endif