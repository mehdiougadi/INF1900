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
#include "CapteurLigne.h"
#include "CapteurPoteau.h"
#include <math.h>

int main()
{
    CapteurPoteau capteur;
    CapteurLigne capteur2;
    while(true)
    {
        capteur2.suivreLigne(); 
    }
    capteur.distance();
}