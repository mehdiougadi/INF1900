//Fait par : Isidore Lauzier - 9 juillet 2005                                
//Modifications par : Jerome Collin

//Petites modifications par : THOELEN Nathan
//                            OUGADI Mehdi
//                            ALLAIRE Mederic
//                            WACRENIER Paul

#ifndef MEMORY_H
#define MEMORY_H

#include <avr/io.h>
#include <util/twi.h>

class MEMORY
{
public:

   MEMORY();
   ~MEMORY();

   void init(); //appeler par le constructeur
   
   //La procedure init() initialize a zero le "memory bank". 
   static uint8_t choisir_banc(const uint8_t banc);
   
   //Fonctions de lecture
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee);
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee, const uint8_t longueur);

   //Fonctions pour ecriture
   uint8_t ecriture(const uint16_t adresse, const uint8_t donnee);
   uint8_t ecriture(const uint16_t adresse, uint8_t *donnee, const uint8_t longueur);

private:
   uint8_t ecrire_page(const uint16_t adresse, uint8_t *donnee, const uint8_t longueur);

private:
   static uint8_t m_adresse_peripherique;
   const uint8_t PAGE_SIZE;
};

#endif