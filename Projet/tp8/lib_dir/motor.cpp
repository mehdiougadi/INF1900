#include "motor.h"

void Engine::start(){
    pwm_.generatePWM();
    DDRD |= ((1<< PD4) | (1<< PD5)| (1<< PD6) | (1<< PD7));
}

void Engine::stop(){
    pwm_.stopPWM();
}

void Engine::forward(uint8_t percentage){
    PORTD |= (1 << PD4);
    PORTD |= (1 << PD5);
    PIND &= ~(1 << PD6); 
    PIND &= ~(1 << PD7);  
    pwm_.setPercentageLeft(percentage);
    pwm_.setPercentageRight(percentage);
    pwm_.resumePWM();
}

void Engine::backward(uint8_t percentage){
    PORTD |= (1 << PD4);
    PORTD |= (1 << PD5);
    PIND |= (1 << PD6); 
    PIND |= (1 << PD7);   
    pwm_.setPercentageLeft(percentage);
    pwm_.setPercentageRight(percentage);
    pwm_.resumePWM();
}

void Engine::turnRight(){
    uint8_t previousPWM = pwm_.getPercentageRight();
    pwm_.setPercentageRight(0);
    pwm_.resumePWM();

    _delay_ms(100);
    
    pwm_.setPercentageRight(previousPWM);
    pwm_.resumePWM();
}

void Engine::turnLeft()
{
    uint8_t previousPWM = pwm_.getPercentageLeft();
    pwm_.setPercentageLeft(0);
    pwm_.resumePWM();

    _delay_ms(100);
    
    pwm_.setPercentageLeft(previousPWM);
    pwm_.resumePWM();
}

void Engine::uTurn(){
    uint8_t previousPWM1 = pwm_.getPercentageRight();
    uint8_t previousPWM2 = pwm_.getPercentageLeft();

    PIND &= ~(1 << PD6);
    PIND |= (1 << PD7);   

    pwm_.setPercentageRight(50);
    pwm_.setPercentageLeft(50);

    pwm_.resumePWM();

    _delay_ms(200);


    pwm_.setPercentageRight(previousPWM1);
    pwm_.setPercentageLeft(previousPWM2);
    pwm_.stopPWM();
}