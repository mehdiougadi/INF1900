#include "pwm.h"
#include "motor.h"

int main()
{
    motor motor1;

    motor1.moveStraight(100);
    _delay_ms(3000);
    motor1.moveStraight(0);
    _delay_ms(3000);
    motor1.moveBack(100);
    _delay_ms(3000);
    motor1.moveStraight(100);
    _delay_ms(3000);
    motor1.moveStraight(0);
}