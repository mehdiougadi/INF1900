#include "motor.h"

void Engine::start(){
    pwm_.generatePWM();
}

void Engine::stop(){
    pwm_.stopPWM();
}

void Engine::forward(uint8_t percentage){
    PINB &= ~(1 << PB5); 
    PINB &= ~(1 << PB7);  
    pwm_.setPercentageLeft(percentage);
    pwm_.setPercentageRight(percentage);
    pwm_.resumePWM();
}

void Engine::backward(uint8_t percentage){
    PINB |= (1 << PB5); 
    PINB |= (1 << PB7);   
    pwm_.setPercentageLeft(percentage);
    pwm_.setPercentageRight(percentage);
    pwm_.resumePWM();
}

void Engine::turnRight(){
    uint8_t previousPWM = pwm_.getPercentageRight();
    pwm_.setPercentageRight(0);
    pwm_.resumePWM();

    _delay_ms();
    
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

    PINB &= ~(1 << PB5);
    PINB |= (1 << PB7);   

    pwm_.setPercentageRight(50);
    pwm_.setPercentageLeft(50);

    pwm_.resumePWM();

    _delay_ms(200);


    pwm_.setPercentageRight(previousPWM1);
    pwm_.setPercentageLeft(previousPWM2);
    pwm_.stopPWM();
}