// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        15 novembre 2022

#ifndef CAPTEURLIGNE_H
#define CAPTEURLIGNE_H
#include "motor.h"
#include "LED.h"
#define F_CPU 8000000

class CapteurLigne 
{
public:
    CapteurLigne();
    void suivreLigne();
    //void Rebondissement();
    void updateCondition();
    
private:
//Objects
Motor motorCapteur;
Led led;
//Number of triggered sensor
uint8_t isON=0x00;
//PIN used for LSS05
const uint8_t pin1 =0x02;  //DS5
const uint8_t pin2 =0x04;  //DS4
const uint8_t pin3 =0x08;  //DS3
const uint8_t pin4 =0x10;  //DS2
const uint8_t pin5 =0x20;  //DS1
bool DS1 = (PINA & pin5) == pin5;
bool DS2 = (PINA & pin4) == pin4;
bool DS3 = (PINA & pin3) == pin3;
bool DS4 = (PINA & pin2) == pin2;
bool DS5 = (PINA & pin1) == pin1;


};

#endif