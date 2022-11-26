 #include "robot.h"

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
    capteurIR.suivreLigne();
}
void Robot::modeB(){}
void Robot::modeS(){}
