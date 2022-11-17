// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        15 novembre 2022

#ifndef CAPTEUR_H
#define CAPTEUR_H
#include "can.h"
#define F_CPU 8000000

class CAPTEUR 
{
public:

CAPTEUR();
uint8_t getIRvalue();
uint8_t getDMvalue();

private:

const uint8_t position = 0;

}