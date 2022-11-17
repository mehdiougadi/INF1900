// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        31 octobre 2022

#ifndef TIMER_H
#define TIMER_H

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>

enum class WAVEFORM { normalMode, ctc };
enum class COMPARE { toggle, setLow, setHigh, off};

class TIMER {

public:
    TIMER(WAVEFORM mode1, COMPARE mode2);
    void waveformMode();
    void compareMode();

private:
    void timeTraduction (uint8_t time, uint16_t prescaler);
    
    uint16_t prescalerCTC = 1024;
    uint16_t prescalerNormalMode = 8;
    WAVEFORM currentMode1;
    COMPARE currentMode2;
};

#endif