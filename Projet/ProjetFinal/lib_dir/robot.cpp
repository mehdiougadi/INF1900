 #include "robot.h"

//Constructeur robot
Robot::Robot()
{
    Motor motor;
    Led led;
    Memory memory;
    Sound speaker;
    Capteur capteur;
}

void Robot::forward()
{
    motor.moveStraight();
}
void Robot::backward()
{
    motor.moveBack();
}
void Robot::freeze()
{
    motor.stop();
}
void Robot::turnRight(){};
void Robot::turnLeft(){};

uint8_t Robot::valueDM()
{
    return capteur.getDMvalue();
}

uint8_t Robot::valueIR()
{
    return capteur.getIRvalue();
}