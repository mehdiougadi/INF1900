 #include "robot.h"

//Constructeur robot
Robot::Robot()
{
    Led led;
    Memory memory;
    Sound speaker;
}

void Robot::trajet()
{  
    switch(currentMode)
    {
        case mode::MODEA:
            modeA();
            currentMode = mode::MODEB;
            break;
        case mode::MODEB:
            modeB();
            currentMode = mode::MODES;
            break;
        case mode::MODES:
            modeA();
            currentMode = mode::MODEA;
            break;
    }
}
    
void Robot::modeA()
{
    while(true)
    {
        capteurIR.suivreLigne();
    }
}
void Robot::modeB()
{}
void Robot::modeS(){}
