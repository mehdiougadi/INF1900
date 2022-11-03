// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        03 novembre 2022

#include "LED.h"
#include "can.h"
#include "debug.h"
#include "memory.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"

//Variables globales
volatile bool isBegin = false;
uint8_t operand;
uint8_t nameInstruction;
uint16_t PC = 0x00;
uint16_t address;
uint16_t localCounter;


enum instruction 
{
    dbt = 0x01, //Début
    att = 0x02, //Attendre
    dal = 0x44, //Allumer la del
    det = 0x45, //Eteindre la del
    sgo = 0x48, //Jouer la sonorité
    sar = 0x09, //Arreter la sonorité
    mar0 = 0x60, //Arreter les moteurs
    mar1 = 0x61, //Arreter les moteurs
    mav = 0x62, //Avancer
    mre = 0x63, //Reculer
    trd = 0x64, //Tourner à droite
    trg = 0x65, //TOurner à gauche
    dbc = 0xC0, //Début boucle
    fbc = 0xC1, //Fin boucle
    fin = 0xFF  //fin du programme
};

void setObjects()
{
    MOTOR motor;
    LED led;
    Memoire24CXXX memory;
    SOUND speaker;
}


void doInstructions()
{
    switch (instruction)
    {
        case att:
            for (uint8_t i = 0; i < operand; i++) 
            {
                _delay_ms(25);
            }
            break;

        case dal:
            if (operand == 1)
                led.colorGreen();
            else if (operand == 2)
                led.colorRed();
            else if (operand == 3)
                led.colorAmber();
            break;

        case det:
            led.noColor();
            break;

        case sgo:
            speaker.playSound(operand);
            break;

        case sar:
            speaker.stopSound();
            break;

        case mar0:
            motor.stop();
            break;

        case mar1:
            motor.stop();
            break;

        case mav:
            motor.moveStraight(motor.intToPercentage(operand));
            break;

        case mre:
            motor.moveBack(motor.intToPercentage(operand));
            break;

        case trd:
            motor.turn(50, 0);
            _delay_ms(2000);
            break;

        case trg:
            motor.turn(0, 50);
            _delay_ms(2000);
            break;

        case dbc:
            address = PC + 1;
            localCounter = operand;
            break;

        case fbc:
            if (localCounter > 0)
            {
                PC = address;
                localCounter--;
            }
            break;

        case fin:
            isBegin = false;
            break;
    }
}

int main()
{
    setObjects();

    while (true)
    {
        if (instruction == dbt)
        {
            isBegin = true;

            while (isBegin)
            {
                memory.lecture(PC, &operand);
                memory.lecture(PC, &nameInstruction);

                doInstructions();
                PC++; 
            }
        }
    }
}