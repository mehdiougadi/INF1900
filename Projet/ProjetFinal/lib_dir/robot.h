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
#include <avr/interrupt.h>
#include "CapteurLigne.h"

enum class mode
{
    MODEA,
    MODEB,
    MODES
};

class Robot
{
public:

    Robot()=default;

    //Mode
    void modeA();
    void modeB();
    void modeS();

    //Objets
    Led led;
    Sound speaker;
    Motor mainMoteur;
private:
    
    //Objets
    Memory memory;
    CapteurLigne capteurIR;

};

#endif