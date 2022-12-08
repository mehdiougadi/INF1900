// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        03 novembre 2022

#include "robot.h"

volatile uint8_t pendingMode=0x00;
volatile uint8_t currentMode=0x00;
volatile bool confirmed = false;

ISR(INT0_vect)
{
    confirmed = true;
}

ISR(INT1_vect)
{
    Led led;
    confirmed = false;
    if(pendingMode==2){pendingMode = 0;}
    else{pendingMode++;}
}

void confirm()
{
    cli(); //Est une routine qui bloque toutes les interruptions
    DDRD &= ~( 1<< PD2);
    EICRA|=(1<<ISC00) | (1<<ISC01); //Rising edge Clock
    EIMSK|=(1<<INT0); //Ajuste le registre EIMSK de l'ATmega324PA pour permettre les interruptions externes
    sei(); //Permet de recevoir à nouveau des interruptions
}

void pending()
{
    cli(); //Est une routine qui bloque toutes les interruptions
    DDRD &= ~( 1<< PD3);
    EICRA|=(1<<ISC10) | (1<<ISC11); //Rising edge Clock
    EIMSK|=(1<<INT1); //Ajuste le registre EIMSK de l'ATmega324PA pour permettre les interruptions externes
    sei(); //Permet de recevoir à nouveau des interruptions
}

int main()
{
    Robot Sonic;
    Memory mem;
    pending();
    confirm();
    
    while(true)
    {
        switch(pendingMode)
        {
            case 0x00:
                Sonic.led.colorGreen();
                if (confirmed){Sonic.modeA();}
                break;

            case 0x01:
                Sonic.led.colorRed();
                if (confirmed){Sonic.modeB();}
                break;

            case 0x02:
                Sonic.led.colorAmber();
                if (confirmed){Sonic.modeS();}
                break;
        }
    }
}
