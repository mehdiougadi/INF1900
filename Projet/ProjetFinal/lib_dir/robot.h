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
#include "CapteurLigne.h"
#include "CapteurPoteau.h"

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
    void trajet();

    //Mode
    void modeA();
    void modeB();
    void modeS();
    uint8_t gMinuterieExpiree = 0;
private:
    //Mode attributs
    mode currentMode = mode::MODEA;

    //Objets
    Led led;
    Memory memory;
    Sound speaker;
    CapteurLigne capteurIR;
    CapteurPoteau capteurDistance;
    Motor mainMoteur;

};

#endif