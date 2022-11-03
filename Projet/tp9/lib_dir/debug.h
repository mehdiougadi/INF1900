
// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022
#ifndef DEBUG_H
#define DEBUG_H
//Clock
#ifndef F_CPU
#define F_CPU 8000000
#endif //F_CPU
//Library usart
#include "usart.h"
//Debug function
#define ERROR
//Usart function to send error message
void sendError(const char message[], uint8_t messageLengthh);
#endif //DEBUG_H