// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        15 novembre 2022

#ifndef CAPTEURLIGNE_H
#define CAPTEURLIGNE_H
#include "motor.h"
#define F_CPU 8000000

enum valueLSS05
{
    forward          = 0b00100,
    smallAdjustLeft  = 0b01000,
    bigAdjustLeft    = 0b10000,
    smallAdjustRight = 0b00010,
    bigAdjustRight   = 0b00001,
    turnLeft         = 0b11100,
    turnRight        = 0b00111,
    changeMode       = 0b11111
};

class CapteurLigne 
{
public:
    CapteurLigne();
    void suivreLigne();
    //void Rebondissement();

private:
Motor motorCapteur;
uint8_t valueIR =( (PINA0<<PA0)  //DS1
                &  (PINA1<<PA1)  //DS2
                &  (PINA2<<PA2)  //DS3
                &  (PINA3<<PA3)  //DS4
                &  (PINA4<<PA4) //DS5
                //Ces bits ne sont pas utiles pour la situation
                &  ~(1<<PA5)
                &  ~(1<<PA6)
                &  ~(1<<PA7)  );
};
#endif