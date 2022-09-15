// Auteurs : Nathan THOELEN 2065331, Mehdi OUGADI 2051559, Younes LAZZALI 2025718.
// Vendredi 16 septembre 2022.
// Description du code : Code qui allume la LED en vert quand l'utilisateur appuie 3 fois sur l'interrupteur.

//             Machine à État
// Etat present	  A	    Etat suivant   Sortie
//   Init	      0	        Init	   Éteint
//   Init         1	        E1	       Éteint
//   E1	          0	        E1	       Éteint 
//   E1           1	        E2         Éteint
//   E2	          0         E2	       Éteint   
//   E2	          1	        E3	       Éteint   
//   E3	          0	        E3	       Éteint  
//   E3	          1	        E4         Éteint 
//   E4           0	        E4	       Vert   
//   E4	          1	        Init       Vert   

#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

//Constante de Delay
const uint8_t delay= 5;

//Initialisation des entrées et sorties
void setIOPorts()
{
    //Mode input
    DDRD &= ~( 1<< PD2);

    //Mode output
    DDRA |= ((1<< PA1) | (1<< PA0));

}

//Le button a été appuyé
bool buttonPressed()
{
    if (PIND & 0x04)
    {
        _delay_ms(delay);
        return (PIND & 0x04);
    }
    return false;
}

//Liaison entre le port et les couleurs
enum class color{red, green, amber, closed};

void setDelColor(color color)
{
    switch (color)
    {
        case color::green:
            PORTA |= (1<<PA0);
            PORTA &= ~(1<<PA1);
            break;

        case color::red:
            PORTA |= (1<<PA1);
            PORTA &= ~(1<<PA0);
            break;

        case color::amber:

            setDelColor(color::green);
            _delay_ms(delay*2);
            setDelColor(color::red);
            _delay_ms(delay-4);

            break;

        case color::closed:
            PORTA &= ~((1<<PA0) | (1<<PA1));
            break;
    }
}

//Énumération des États
enum etat{INIT,E1,E2,E3};

//Algorithme pour le problème 1
void problem1()
{
    etat state=INIT;

    while(true)
    {
        switch (state)
            {
                case INIT:
                    setDelColor(color::closed);
                    if(buttonPressed())
                    {
                        state=E1;
                        while(buttonPressed()){}
                
                    }
                    break;
                case E1:
                    setDelColor(color::closed);
                    if(buttonPressed())
                    {
                        state=E2;
                        while(buttonPressed()){}
                
                    }
                    break;
                case E2:
                    setDelColor(color::closed);
                    if(buttonPressed())
                    {
                        state=E3;
                        while(buttonPressed()){}
                
                    }
                    break;
                case E3:
                    //Couleur verte pendant 2 secondes
                    setDelColor(color::green);
                    _delay_ms(2000);
                    state=INIT;
                    break;
            } 
        }
}

int main()
{
    //Initialisation
    setIOPorts();

    //Problème 1
    problem1();
}

