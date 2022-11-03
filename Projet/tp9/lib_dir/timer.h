// Cours:       INF1900 - Projet initial de syst?me embarqu?
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
//              LAZZALI Younes
// Date:        31 octobre 2022

#ifndef TIMER_H
#define TIMER_H

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>

//Les timers possibles
enum class waveform { normalMode, ctc };
enum class compare { toggle, setLow, setHigh, off};

class TIMER {
public:
    TIMER(waveform mode1, compare mode2);
    void waveformMode();
    void compareMode();
private:
    //time in seconds
    void timeTraduction (uint8_t time, uint16_t prescaler);
    
    //Attributs
    uint16_t prescalerCTC = 1024;
    uint16_t prescalerNormalMode = 8;
    waveform currentMode1;
    compare currentMode2;
};

#endif