//Par : Matthew Khouzam et Jerome Collin (2005-2006)
//Petites modifications par : THOELEN Nathan
//                            OUGADI Mehdi
//                            ALLAIRE Mederic
//                            WACRENIER Paul
// Date:        31 octobre 2022

#ifndef CAN_H
#define CAN_H

#include <avr/io.h> 

class CAN
{
public:

   CAN();
   ~CAN();

   uint16_t lecture(uint8_t pos);

private:
   //aucune donne membre

};

#endif