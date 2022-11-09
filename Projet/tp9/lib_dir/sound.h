#ifndef SOUND_H
#define SOUND_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

const double boardFrequency[] =
    {110.0, 
	116.54, 
	123.47, 
	130.81, 
	130.59, 
	146.83, 
	155.56, 
	164.81, 
	174.61,
    185.0,
	196.0,
	207.65,
	220.0,
	233.08,
	246.94,
	261.63,
	277.18,
	293.66,
	311.13,
    329.63,
	349.23,
	369.99,
	392.0,
	415.30,
	440.0,
	466.16,
	493.88,
	523.25,
	554.37,
    587.33,
	622.25,
	659.26,
	69.46,
	739.99,
	783.99,
	830.61,
	880.0};

class SOUND
{
public:
	SOUND();
	void playSound(uint8_t note);
	void stopSound();
};

#endif