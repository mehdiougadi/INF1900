// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        31 octobre 2022

#ifndef DEBUG_H
#define DEBUG_H

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include "usart.h"

#define ERROR

void sendError(const char message[], uint8_t messageLengthh);

#endif