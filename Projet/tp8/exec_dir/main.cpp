#include "pwm.h"
#include "motor.h"

int main()
{
    motor motor1;

    motor1.moveStraight(10);
    _delay_ms(3000);
    motor1.moveStraight(40);
    _delay_ms(3000);
    motor1.moveStraight(0);
}