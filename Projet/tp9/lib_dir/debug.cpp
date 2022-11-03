// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022
#ifndef DEBUG
//Libraries
#include "debug.h"
#include "usart.h"
//Debug function definition
#ifdef ERROR_PRINT
	
	//Function to print ERROR
	#define ERROR_PRINT(x,y) messageUSBtoRS232.transmissionUART(x,y)
#endif // ERROR_PRINT
//Remake of sendMessage from usart class
void sendError ( const char message[] , uint8_t messageLength )
{
	usart messageUSBtoRS32;
	#ifdef ERROR_PRINT
		ERROR_PRINT(message, messageLength);
	#endif // ERROR_PRINT
}
#endif // !DEBUG