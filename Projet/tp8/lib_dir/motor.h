#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#include <pwm.h>
#include <util/delay.h>

class Engine
{
public:

    //Méthode Publique
    Engine()=default;
    void start();
    void stop();
    void forward(uint8_t percent);
    void backward(uint8_t percent);
    void turnRight();
    void turnLeft();
    void uTurn();
private:

    //Attributs
    PWM pwm_=PWM();
    bool direction_;
};

#endif