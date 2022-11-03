// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#ifndef LED_H
#define LED_H

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

class LED 
{
public:
    LED();
    void colorGreen();
    void colorRed();
    void colorAmber();
    void noColor();
};

#endif