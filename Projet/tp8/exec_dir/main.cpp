#include "motor.h"
#include "LED.h"
#include "timer.h"

int main()
{
    motor motor1;
    LED ledLibre;
    ledLibre.initLED();

    ledLibre.colorGreen();
    motor1.moveStraight(100);
    _delay_ms(3000);
    motor1.stop();
    _delay_ms(3000);

    ledLibre.colorRed();
    motor1.turn(0,50);
    _delay_ms(2000);
    motor1.stop();
    _delay_ms(3000);    

    ledLibre.colorGreen();
    motor1.moveStraight(100);
    _delay_ms(3000);
    motor1.stop();
    _delay_ms(3000);

    ledLibre.colorRed();
    motor1.turn(0,50);
    _delay_ms(2000);
    motor1.stop();
    _delay_ms(3000);  

    ledLibre.colorGreen();
    motor1.moveStraight(100);
    _delay_ms(3000);
    motor1.stop();
    _delay_ms(3000);

    ledLibre.colorRed();
    motor1.turn(0,50);
    _delay_ms(2000);
    motor1.stop();
    _delay_ms(3000); 

    ledLibre.colorGreen();
    motor1.moveStraight(100);
    _delay_ms(3000);
    motor1.stop();
    _delay_ms(3000);

    ledLibre.colorRed();
    motor1.turn(0,50);
    _delay_ms(2000);
    motor1.stop();
    _delay_ms(3000); 

    ledLibre.noColor();
}