// Auteurs : Nathan THOELEN 2065331, Mehdi OUGADI 2051559, Younes LAZZALI 2025718.
// Vendredi 16 septembre 2022.
// Description du code : Code qui allume la LED de differentes couleurs en fonction du nombres de fois que le boutton est appuye.

//             Machine à État
// Etat present	  A	    Etat suivant   Sortie
//   Init	      0	        Init	   Rouge
//   Init         1	        E1	       Rouge
//   E1	          0	        E1	       Ambré 
//   E1           1	        E2         Ambré
//   E2	          0         E2	       Vert   
//   E2	          1	        E3	       Vert   
//   E3	          0	        E3	       Rouge  
//   E3	          1	        E4         Rouge 
//   E4           0	        E4	       Éteint   
//   E4	          1	        E5         Éteint
//   E5           0	        E5	       Vert   
//   E5	          1	        Init       Vert 




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
enum etat{INIT,E1,E2,E3,E4,E5};

//Algorithme pour probleme 2
void problem2()
{
    //État initial
    etat state=INIT;

    while(true)
    {

        //Changement d'état
        switch (state)
            {
                case INIT:
                    //Couleur rouge dans INIT
                    setDelColor(color::red);

                    //Si Button est appuyé, change d'état
                    if(buttonPressed())
                    {
                      state=E1;
                    }
                    break;

                case E1:
                    //Couleur ambré dans E1
                    setDelColor(color::amber);

                    //Si le button est relaché, change d'état
                    if (!buttonPressed())
                    {
                        state = E2;
                    }
                    break;

                case E2:
                    //Couleur vert dans E2
                    setDelColor(color::green);

                    //Si le button est appuyé, change d'état
                    if (buttonPressed())
                    {
                        state = E3;
                    }
                    break;

                case E3:
                    //Couleur rouge dans E3
                    setDelColor(color::red);

                    //Si le button est relaché, change d'état
                    if (!buttonPressed())
                    {
                        state = E4;
                    }
                    break;

                case E4:
                    //Le LED est fermé dans E4
                    setDelColor(color::closed);

                    //Si le button est appuyé, change d'état
                    if (buttonPressed())
                    {
                        state = E5;
                    }
                    break;

                case E5:
                    //Couleur vert dans E5
                    setDelColor(color::green);
                    //si le button est relaché, change d'état
                    if (!buttonPressed())
                    {
                        state = INIT;
                    }
                    break;

            } 
        }
}

int main()
{
    //Initialisation
    setIOPorts();

    //Problème 2
    problem2();

}