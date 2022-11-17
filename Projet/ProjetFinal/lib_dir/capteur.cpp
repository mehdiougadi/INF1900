#include "capteur.h"



Capteur::Capteur()
{
    DDRA = 0x00;
    can IR;
    can DM;
}

uint8_t Capteur::getIRvalue()
{
    return IR.lecture(position)>>2;
}

uint8_t Capteur::getDMvalue()
{
    return DM.lecture(position)>>2;
}