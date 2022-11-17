#include "capteur.h"



CAPTEUR::CAPTEUR()
{
    DDRA = 0x00;
    can IR;
    can DM;
}

uint8_t CAPTEUR::getIRvalue()
{
    return IR.lecture(position)>>2;
}

uint8_t CAPTEUR::getDMvalue()
{
    return DM.lecture(position)>>2;
}