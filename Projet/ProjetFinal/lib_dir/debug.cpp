// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        31 ocotbre 2022

#ifndef DEBUG_H

#include "debug.h"
#include "usart.h"

#ifdef ERROR_PRINT

#define ERROR_PRINT(x,y) messageUSBtoRS232.transmissionUART(x,y)
#endif

void sendError ( const char message[] , uint8_t messageLength )
{
	Usart messageUSBtoRS32;

	#ifdef ERROR_PRINT
		ERROR_PRINT(message, messageLength);
	#endif
}

#endif