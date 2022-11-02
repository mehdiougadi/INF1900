#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

class motor
{
public:
	motor();
	void moveStraight(uint8_t pwm);
	void moveBack(uint8_t pwm);
	void turn(uint8_t pwm1 , uint8_t pwm2);
	void stop();
private:
	//Attribut
	const uint8_t maxValue = 255;
	uint8_t percentageToInt(int percentage);
	void adjustPWM( uint8_t rightPWM, uint8_t leftPWM);
};

#endif