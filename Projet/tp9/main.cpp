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


int main()
{

    switch(instruction)
    {
        case dbt:
            break;

        case att:
            break;

        case dal:
            break;

        case det:
            break;

        case sgo:
            break;

        case sar:
            break;

        case mar0:
            break;

        case mar1:
            break;

        case mav:
            break;

        case mre:
            break;

        case trd:
            break;

        case trg:
            break;

        case dbc:
            break;

        case fbc:
            break;

        case fin:
            break;
    }
}