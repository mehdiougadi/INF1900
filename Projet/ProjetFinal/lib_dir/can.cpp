// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        31 octobre 2022

#include "can.h"

Can::Can()
{
   // ADC mux : reference analogique externe
   ADMUX  = ( 0 << REFS1 ) | ( 0 << REFS0 ) | ( 0 << ADLAR ) | ( 0 << MUX4 ) |
            ( 0 << MUX3 ) | ( 0 << MUX2 ) | ( 0 << MUX1) | ( 0 << MUX0 ) ;

   // ADC Status and Control Register A
   ADCSRA = ( 1 << ADEN ) | ( 0 << ADSC )  | ( 0 << ADATE ) | ( 0 << ADIF ) |
            ( 0 << ADIE ) | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 0 << ADPS0 ) ;
}

Can::~Can()
{
   ADCSRA = 0 << ADEN ;
}

//Conversion pour avoir resultat sur 16 bits avec seulement 10 premiers significatifs.
uint16_t Can::lecture( uint8_t pos)
{
   uint16_t adcVal;

   ADMUX  &=  ~(( 1 << MUX4 ) | ( 1 << MUX3 ) | 
                ( 1 << MUX2 ) | ( 1 << MUX1)  | ( 1 << MUX0 ));

   //Entree voulue
   ADMUX |= ((pos & 0x07) << MUX0) ;

   //Demarrer conversion
   ADCSRA |= ( 1 << ADSC );

   //Attendre fin conversion
   while( ! (ADCSRA & ( 1 << ADIF ) ) );

   //Remettre bit d'indication de fin de cycle a zero 
   ADCSRA |= (1 << ADIF);

   //Aller chercher resultat sur 16 bits
   adcVal =   ADCL ;
   adcVal +=  ADCH << 8;

   return adcVal;
}