// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        31 octobre 2022

#ifndef F_CPU

# define F_CPU 8000000UL
#endif

#include "memory.h"

uint8_t Memory::m_adresse_peripherique = 0xA0;

Memory::Memory() : PAGE_SIZE(128)
{
   init();
}

Memory::~Memory() {}

void Memory::init()
{
   choisir_banc(0);
   TWSR = 0;
   TWBR =  (F_CPU / 100000UL - 16) / 2;
}

uint8_t Memory::choisir_banc(const uint8_t banc)
{
   uint8_t temp = banc & 0x03;
   uint8_t rv = 255;
   if(banc == temp)
   {
      Memory::m_adresse_peripherique = (0xA0 | ( banc << 1 ));
      rv = Memory::m_adresse_peripherique;
   }
   return rv;
}

uint8_t Memory::lecture(const uint16_t adresse, uint8_t *donnee)
{
  uint8_t rv = 0;

  //Attente de la fin d'un cycle d'ecriture
  for (;;)
  {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) == 0);

    TWDR = m_adresse_peripherique;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) == 0);
    
    if (TWSR==0x18)
       break;
   }

  //Transmission de la condition de depart
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du code de controle
  TWDR = m_adresse_peripherique;      
  TWCR = _BV(TWINT) | _BV(TWEN);      
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du poids fort de l'adresse
  TWDR =  ( adresse >> 8 );
  TWCR = _BV(TWINT) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du poids faible de l'adresse
  TWDR = adresse;                     
  TWCR = _BV(TWINT) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission de la condition de depart
  //  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du code de controle
  TWDR =  m_adresse_peripherique + 1;   
  TWCR = _BV(TWINT) | _BV(TWEN);        
  while ((TWCR & _BV(TWINT)) == 0);

  //Lecture de l'eeprom
  TWCR = _BV(TWINT) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);
  *donnee = TWDR;

  //Transmission de la condition d'arret
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
  return rv;
}

uint8_t Memory::lecture(const uint16_t adresse, uint8_t *donnee, uint8_t longueur)
{
  uint8_t twcr;

  //Attente de la fin d'un cycle d'ecriture
  for (;;)
  {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);   
    while ((TWCR & _BV(TWINT)) == 0) ;   

    TWDR = m_adresse_peripherique;       
    TWCR = _BV(TWINT) | _BV(TWEN);      
    while ((TWCR & _BV(TWINT)) == 0);
    
    if (TWSR==0x18)                  
       break;
  }

  //Transmission de la condition de depart
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du code de controle
  TWDR = m_adresse_peripherique;       
  TWCR = _BV(TWINT) | _BV(TWEN);        
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du poids fort de l'adresse
  TWDR = adresse >> 8;                  
  TWCR = _BV(TWINT) | _BV(TWEN);        
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du poids faible de l'adresse
  TWDR = adresse;                    
  TWCR = _BV(TWINT) | _BV(TWEN);       
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission de la condition de depart
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du code de controle
  TWDR =  m_adresse_peripherique + 1; 
  TWCR = _BV(TWINT) | _BV(TWEN);      
  while ((TWCR & _BV(TWINT)) == 0);

  // Lecture de l'eeprom
  for (twcr = _BV(TWINT) | _BV(TWEN) | _BV(TWEA) ; longueur > 0; longueur--)
  {
      if (longueur == 1)
         twcr = _BV(TWINT) | _BV(TWEN);
      TWCR = twcr;                       
      while ((TWCR & _BV(TWINT)) == 0);
      *donnee++ = TWDR;               
  }

  //Transmission de la condition d'arret
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);

  return 0;
}

uint8_t Memory::ecriture(const uint16_t adresse, const uint8_t donnee)
{
  //Attente de la fin d'un cycle d'ecriture
  for ( ; ; )
  {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) == 0);

    TWDR = m_adresse_peripherique;       
    TWCR = _BV(TWINT) | _BV(TWEN);       
    while ((TWCR & _BV(TWINT)) == 0);
      

    if (TWSR==0x18)
       break;               
  }

  //Transmission de la condition de depart 
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);  
  while ((TWCR & _BV(TWINT)) == 0);
     

  //Transmission du code de controle
  TWDR = m_adresse_peripherique;        
  TWCR = _BV(TWINT) | _BV(TWEN);       
  while ((TWCR & _BV(TWINT)) == 0); 
     

  //Transmission du poids fort de l'adresse
  TWDR = adresse >> 8;                 
  TWCR = _BV(TWINT) | _BV(TWEN);        
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du poids faible de l'adresse
  TWDR = adresse;                 
  TWCR = _BV(TWINT) | _BV(TWEN);        
  while ((TWCR & _BV(TWINT)) == 0);     

  //Transmission de la donnee
  TWDR = donnee;
  TWCR = _BV(TWINT) | _BV(TWEN);        
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission de la condition d'arret
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);

  return 0;
}


uint8_t Memory::ecriture(const uint16_t adresse, uint8_t *donnee, const uint8_t longueur)
{
  uint8_t rv;
  uint16_t copieAdresse = adresse;
  uint8_t copieLongueur = longueur;
  do
  {
      rv = ecrire_page(copieAdresse, donnee, copieLongueur);
      copieAdresse += rv;      
      copieLongueur -= rv;     
      donnee += rv;          
  }
  while (copieLongueur > 0);

  return 0;
}


uint8_t Memory::ecrire_page(const uint16_t adresse, uint8_t *donnee, const uint8_t longueur)
{
  uint16_t addr_fin;
  uint8_t rv = 0;
  uint8_t copieLongueur = longueur;

  if (adresse + longueur < (adresse | (PAGE_SIZE - 1)))
    addr_fin = adresse + longueur;
  else
    addr_fin = (adresse | (PAGE_SIZE - 1)) + 1;
  copieLongueur = addr_fin - adresse;


  //Attente de la fin d'un cycle d'ecriture
  for ( ; ; )
  {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);    
    while ((TWCR & _BV(TWINT)) == 0) ;   
    TWDR = m_adresse_peripherique;   
    TWCR = _BV(TWINT) | _BV(TWEN);    
    while ((TWCR & _BV(TWINT)) == 0);

    if (TWSR==0x18)
       break;               
  }

  //Transmission de la condition de depart
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); 
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du code de controle 
  TWDR = m_adresse_peripherique;        
  TWCR = _BV(TWINT) | _BV(TWEN);       
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du poids fort de l'adresse
  TWDR = adresse >> 8;                  
  TWCR = _BV(TWINT) | _BV(TWEN);      
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission du poids faible de l'adresse
  TWDR = adresse;                       
  TWCR = _BV(TWINT) | _BV(TWEN);       
  while ((TWCR & _BV(TWINT)) == 0);

  //Transmission de la page
  for ( ; copieLongueur > 0; copieLongueur--)
  {
     TWDR = *donnee++;
     TWCR = _BV(TWINT) | _BV(TWEN);     
     while ((TWCR & _BV(TWINT)) == 0);
     rv++;                             
  }

  //Transmission de la condition d'arrret 
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);

  return rv;
}