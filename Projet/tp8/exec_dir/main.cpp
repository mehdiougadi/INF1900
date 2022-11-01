#include "pwm.h"
#include "motor.h"


int main()
{
    Engine motor;

    motor.start();
    motor.forward(10);
    _delay_ms(3000);
    motor.forward(1);
    _delay_ms(3000);
    motor.stop();

}