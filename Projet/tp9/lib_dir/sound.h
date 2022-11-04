#ifndef SOUND_H
#define SOUND_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

enum class octave 
{
	octave2,
	octave3,
	octave4,
	octave5
};

enum note
{
	A = 110;
	Bb = 116.54;
	B = 123.47;
	C
}


class SOUND
{
public:
	SOUND();
	void playSound(uint8_t note);
	void stopSound();

private:
	uint8_t note;
};

#endif