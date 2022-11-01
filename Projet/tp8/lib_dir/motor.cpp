#include "motor.h"


motor::motor()
{
    DDRD |= ((1<< PD4) | (1<< PD5)| (1<< PD6) | (1<< PD7));
    TCCR1A |= (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1)|(1<<COM1A0)|(1<<COM1B0);
	TCCR1B |= (1<< CS11); //prescaler à 8
    moveStraight(0);
}
void motor::moveLeftWheel(direction direction)
{
    if (direction == direction::forward)
    {
        PORTD &= ~(1 << PB6);
    }
    else if (direction == direction::backward)
    {
        PORTD |= (1 << PB6);
    }
}
void motor::moveRightWheel(direction direction)
{
    if (direction == direction::forward)
    {
        PORTB &= ~(1 << PB7);
    }
     else if (direction == direction::backward)
    {
        PORTB |= (1 << PB7);
    }
}
void motor::adjustPWM ( uint8_t rightPWM,uint8_t leftPWM) 
{
	OCR1A = rightPWM;
	OCR1B = leftPWM;
}
uint8_t motor::percentageToInt(int percentage)
{
    return 255 - (percentage*maxValue)/100;
}
void motor::moveStraight(uint8_t percentage)
{
    uint8_t pwm = percentageToInt(percentage);
    moveRightWheel(direction::forward);
    moveLeftWheel(direction::forward);
    adjustPWM(pwm, pwm);
}
void motor::moveBack(uint8_t percentage)
{
    uint8_t pwm = percentageToInt(percentage);
    motor::moveRightWheel(direction::backward);
    motor::moveLeftWheel(direction::backward);
    motor::adjustPWM(pwm, pwm);
}
void motor::turn(uint8_t pwm1 , uint8_t pwm2)
{
    pwm1= percentageToInt(pwm1);
    pwm2= percentageToInt(pwm2);
    motor::moveRightWheel(direction::forward);
    motor::moveLeftWheel(direction::forward);
    motor::adjustPWM(pwm1, pwm2);
}