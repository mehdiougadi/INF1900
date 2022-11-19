#include "CapteurLigne.h"



CapteurLigne::CapteurLigne()
{
    DDRA &= ~(1<<PA0)
         &  ~(1<<PA1)
         &  ~(1<<PA2)
         &  ~(1<<PA3)
         &  ~(1<<PA4);
}

void CapteurLigne::suivreLigne()
{
    switch(valueIR)
    
    {
        case valueLSS05::forward:
            motorCapteur.moveStraight(50);
            break;

        case valueLSS05::smallAdjustLeft:
            motorCapteur.turn(40,50);
            break;

        case valueLSS05::bigAdjustLeft:
            motorCapteur.turn(40,60);
            break;

        case valueLSS05::smallAdjustRight:
            motorCapteur.turn(50,40);
            break;

        case valueLSS05::bigAdjustRight:
            motorCapteur.turn(60,40);
            break;

        case valueLSS05::turnLeft:
            break;

        case valueLSS05::turnRight:
            /*
            motorCapteur.turn();
            while(PINA2 == 0x01)
            {
                motorCapteur.turn();
            }
            if (PINA3=0x01)
            {
                valueIR = valueLSS05::smallAdjustLeft;
                break;
            }
            else if(PINA3=0x01)
            {
                valueIR = valueLSS05::smallAdjustLeft;
                break;
            }
            else if(PINA4=0x01)
            {
                valueIR = valueLSS05::bigAdjustLeft;
                break;            
            }
            else if(PINA0=0x01)
            {
                valueIR = valueLSS05::bigAdjustRight;
                break;          
            }
            else if(PINA1=0x01)
            {
                valueIR = valueLSS05::smallAdjustRight;
                break;       
            }
            */
            break;

        case valueLSS05::changeMode:
            motorCapteur.stop();
            break;

    }
}
