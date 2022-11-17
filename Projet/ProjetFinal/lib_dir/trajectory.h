#include "Robot.h"

//Constantes globaux
volatile uint8_t counter=0x01;

static enum Mode
{
    modeA=0x01;
    modeB=0x02;
    modeC=0x03;
}
static enum Action
{
    forward = 0b00100;
    turnRight = 0b00011;
    turnLeft = 0b11000;
    changeMode = 0b11111;
}

//ISR
ISR(INT0_vect)
{
    if(counter>=0x01 && counter<=0x03)
    {
        changeMode(++counter);
    }
    else
    {
        changeMode(Mode::mode1);
    }
}

//Fonctions d'interruption
void initInterrupt()
{
    cli(); //Est une routine qui bloque toutes les interruptions

    DDRD &= ~( 1<< PD2);

    EICRA|=(1<<ISC00) | (1<<ISC01); //Rising edge Clock

    EIMSK|=(1<<INT0); //Ajuste le registre EIMSK de l'ATmega324PA pour permettre les interruptions externes

    sei(); //Permet de recevoir à nouveau des interruptions
}

//Section de traitement
uint8_t changeMode(Robot robot,Mode mode)
{
    switch(mode)
    {
        case mode::modeA:
            robot.turnLED(0x01);
            break;
        case mode::modeB:
            robot.turnLED(0x02);
            break;
        case mode::modeC:
            robot.turnLED(0x03);
            break;
    }
}

void trajectory()
{
    while(true)
    {
        switch(robot.getValueIR())
        {
            case Action::forward:
                robot.forward();
                break;
            case Action::turnRight:
                robot.turnRight();
                break;
            case Action::turnLeft:
                robot.turnLeft();
                break;
            case Action::changeMode:
                changeMode(++counter);
                break;
        }
    }
}