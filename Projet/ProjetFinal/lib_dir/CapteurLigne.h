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
#include "can.h"
#include "sound.h"
#include "usart.h"
#include "memory.h"
#define F_CPU 8000000

enum usedValue
{
    ZERO =0x00,
    ONE  =0x01,
    TWO  =0x02,
    THREE=0x03,
    FOUR =0x04,
    FIVE =0x05
};

class CapteurLigne 
{
public:
    CapteurLigne();
    void suivreLigneA();
    void suivreLigneB();
    void suivreLigneS();
    void Rebondissement();

    void updateCondition();
    bool distance();
    uint8_t readValueDM();
    
private:
//Objects
Motor motorCapteur;
Led led;
Can sensor;
Memory mem;
Sound sonCapteur;

//Number of triggered sensor
uint8_t isON=0x00;
const uint8_t PIN = 0x07;

//Poteau
uint8_t nbrPoteau =0;
int listPoteau[3];

//Bool
bool parking=false;
bool grave;


//PIN used for sensor
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
const uint8_t BITSHIFT = 2;
const uint8_t CLOSE = 255;
const uint8_t MEDIUM = 77;
const uint8_t FAR = 40;
};

#endif