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
#include "usart.h"
#include "sound.h"

#include <math.h>

//Variables globales
volatile bool isBegin = false;
uint8_t operand;
uint16_t PC = 0x00;
uint16_t address;
uint16_t localCounter;

//Objets globaux
MOTOR motor;
LED led;
Memoire24CXXX memory;
SOUND speaker;

enum instruction 
{
    dbt = 0x01, //Début
    att = 0x02, //Attendre
    dal = 0x44, //Allumer la del
    det = 0x45, //Eteindre la del
    sgo = 0x48, //Jouer la sonorité
    sar = 0x09, //Arreter la sonorité
    mar = 0x61, //Arreter les moteurs
    mav = 0x62, //Avancer
    mre = 0x63, //Reculer
    trd = 0x64, //Tourner à droite
    trg = 0x65, //TOurner à gauche
    dbc = 0xC0, //Début boucle
    fbc = 0xC1, //Fin boucle
    fin = 0xFF  //fin du programme
};

void starting()
{
    led.colorRed();
    speaker.introSong();
    led.colorGreen();
    motor.moveStraight(100);
    _delay_ms(500);
    motor.stop();
    _delay_ms(200);
    motor.moveBack(100);
    _delay_ms(500);
    led.noColor();
    motor.stop();
    _delay_ms(3000);
}

void doInstructions(uint8_t valueInstruction)
{
    switch (valueInstruction)
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
            operand = 0;
            led.noColor();
            break;

        case sgo:
            
            speaker.playSound(operand);
            break;

        case sar:
            speaker.stopSound();
            break;

        case mar:
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
        {
            address = PC;
            localCounter = operand;
            localCounter--;
        }
         break;
        case fbc:{

        
            if (localCounter > 0)
            {
                PC = address;
                localCounter--;
            }
           
        }
         break;


        case fin:
            isBegin = false;
            speaker.outroSong();
            break;

        default:
            break;
    }
}

int main()
{
    uint8_t valueInstruction;

    while (true)
    {
        memory.lecture(PC, &valueInstruction);
        PC++;
        memory.lecture(PC, &operand);
        PC++;

        if (valueInstruction == instruction::dbt)
        {
            isBegin = true;
            starting();
            
            while (isBegin)
            {
                memory.lecture(PC, &valueInstruction);
                PC++;
                memory.lecture(PC, &operand);
                PC++; 
                doInstructions(valueInstruction);
            }
        }
    }
}