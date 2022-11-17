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

    void start();
    void startingSequence(); //Uitlisée dans la fonction start()

    //Fonctions utilisées pour l'interprétation des instructions
    void wait(uint8_t operand);
    void turnLED(uint8_t operand);
    void startLoop(uint8_t operand);
    void endLoop();
    void end();

    //Pour lire instructions et opérandes en mémoire
    void readMemory();

    //Fonctions qui traduit instructions et les exécutent
    void doInstructions(uint8_t valueInstruction);
    void sequence();

private:
    //Objets
    Motor motor;
    Led led;
    Memory memory;
    Sound speaker;
    
    //Variables
    uint8_t operand;
    volatile bool isBegin = false;
    uint16_t PC;
    uint16_t address;
    uint16_t localCounter;
    uint8_t valueInstruction;
};

#endif