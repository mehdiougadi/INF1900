// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#include "pwm.h"

void PWM::percentageToInt(uint8_t percentage)
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
    TCNT0 = 0;

    OCR0A = leftPWM;
    OCR0B = rightPWM;

    TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0);
    TCCR0B |= (1 << CS01);

}

void PWM::stopPWM()
{
    OCR0A = 0xFF;
    OCR0B = 0xFF;
    TCCR0A = 0;
    TCCR0B = 0;
}