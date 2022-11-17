// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        16 novembre 2022

#ifndef ROBOT_H
#define ROBOT_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "LED.h"
#include "memory.h"
#include "motor.h"
#include "sound.h"
#include "usart.h"

class Robot
{
public:
    Robot();

    //Movement
    void turnRight();
    void turnLeft();
    void forward();
    void backward();
    void freeze();

    //Getter
    uint8_t getValueDM();
    uint8_t getValueIR();

private:
    //Objets
    Motor motor;
    Led led;
    Memory memory;
    Sound speaker;
    Capteur capteur;

};

#endif