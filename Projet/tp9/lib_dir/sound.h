#ifndef SOUND_H
#define SOUND_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

const double boardFrequency[] =
    {
	//Octave 2
	110.0,  //A  index 45
	116.54, //A# index 46
	123.47, //B  index 47
	//Octave 3
	130.81, //C  index 48
	130.59, //C# index 49
	146.83, //D  index 50
	155.56, //D# index 51
	164.81, //E  index 52
	174.61, //F  index 53
    185.0,  //F# index 54
	196.0,  //G  index 55
	207.65, //G# index 56
	220.0,  //A  index 57
	233.08, //A# index 58
	246.94, //B  index 59
	//Octave 4
	261.63, //C  index 60
	277.18, //C# index 61
	293.66, //D  index 62
	311.13, //D# index 63
    329.63, //E  index 64
	349.23, //F  index 65
	369.99, //F# index 66
	392.0,  //G  index 67
	415.30, //G# index 68
	440.0,  //A  index 69
	466.16, //A# index 70
	493.88, //B  index 71
	//Octave 5
	523.25, //C  index 72
	554.37, //C# index 73
    587.33, //D  index 74
	622.25, //D# index 75
	659.26, //E  index 76
	698.46, //F  index 77
	739.99, //F# index 78
	783.99, //G  index 79
	830.61, //G# index 80
	880.0   //A  index 81
	};

class SOUND
{
public:
	SOUND();
	void playSound(uint8_t note);
	void stopSound();
	
	void introSong();
	void outroSong();
};

#endif