// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef PWM_H
#define PWM_H


class PWM 
{
public:
    //Méthode Publique
    void generatePWM();
    void setPercentageLeft(uint8_t percentage);
    void setPercentageRight(uint8_t percentage);
    uint8_t getPercentageLeft() const;
    uint8_t getPercentageRight() const;
    void stopPWM();
    void resumePWM();

private:
    //Méthode Privée
    void adjustPWM(uint8_t counterValueLeft,uint8_t counterValueRight);
    uint8_t percentageToInt(uint8_t percentage);

    //Attributs
    const uint8_t maxValue = 255;
    uint8_t leftPWM_ = 0;
    uint8_t rightPWM_ = 0;
};

#endif // !PWM_H