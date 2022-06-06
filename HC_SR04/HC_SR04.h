#include "mbed.h"

#ifndef _HC_SR04_H_
#define _HC_SR04_H_

class HC_SR04 {

public :
    HC_SR04 (PinName echo, PinName pulse, PinName S0, PinName S1);

    float getFrontDistance (void);
    float getLeftDistance (void);
    float getRearDistance (void);
    float getRightDistance (void);

    int getAllDistances (float* distanceTable);

protected :
    void starting (void);
    void measure (void);
    void pulseGenerator (void);
    
private :
    InterruptIn *_echo;
    DigitalOut *_pulse;
    BusOut *_selecter;
    Timer _tempo;

    float _USSensors[4];
    int _canal;

    Thread pulseGeneratorThread;

};

#endif