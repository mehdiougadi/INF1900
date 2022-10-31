#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#include <pwm.h>

class Engine
{
public:

    //Méthode Publique
    void start();
    void stop();
    void forward(uint8_t percent);
    void backward(uint8_t percent);
    void turnRight();
    void turnLeft();
    void uTurn();
private:

    //Attributs
    PWM pwm_;
    bool direction_;
};

#endif