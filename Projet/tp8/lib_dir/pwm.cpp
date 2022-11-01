// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#include "pwm.h"

uint8_t PWM::percentageToInt(uint8_t percentage)
{
    return (percentage/100) * maxValue;
}

void PWM::setPercentageLeft(uint8_t percentage)
{
    leftPWM_ = percentage;
}

void PWM::setPercentageRight(uint8_t percentage)
{
    rightPWM_ = percentage;
}

uint8_t PWM::getPercentageLeft() const
{
    return leftPWM_;
}

uint8_t PWM::getPercentageRight() const
{
    return rightPWM_;
}

void PWM::generatePWM()
{
    uint8_t pwmLeft = percentageToInt(leftPWM_);
    uint8_t pwmRight = percentageToInt(rightPWM_);
    adjustPWM(pwmLeft, pwmRight);
}

void PWM::resumePWM()
{
    generatePWM();
}

void PWM::adjustPWM(uint8_t leftPWM, uint8_t rightPWM)
{
    TCNT1 = 0;

    OCR1A = leftPWM;
    OCR1B = rightPWM;

    TCCR1A |= (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1)|(1<<COM1A0)|(1<<COM1B0);
    TCCR1B |= (1<< CS11); //prescaler à 8


}

void PWM::stopPWM()
{
    OCR1A = 0xFF;
    OCR1B = 0xFF;
}