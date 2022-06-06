#include "mbed.h"
#include "HC_SR04.h"

HC_SR04::HC_SR04 (PinName echo, PinName pulse, PinName S0, PinName S1){

    _echo = new InterruptIn(echo);
    _pulse = new DigitalOut (pulse);
    _selecter = new BusOut (S0, S1);

    _echo->rise(callback(this, &HC_SR04::starting));
    _echo->fall(callback(this, &HC_SR04::measure));

    _tempo.start();
    pulseGeneratorThread.start (callback(this,&HC_SR04::pulseGenerator));
}

float HC_SR04::getFrontDistance (void){
    return _USSensors[0];
}

float HC_SR04::getLeftDistance (void){
    return _USSensors[1];
}

float HC_SR04::getRearDistance (void){
    return _USSensors[2];
}

float HC_SR04::getRightDistance (void){
    return _USSensors[3];
}

int HC_SR04::getAllDistances (float* distanceTable){
    if (distanceTable==nullptr) return -1;
    for (int i=0; i<4; i++) {
        *(distanceTable+i)=_USSensors[i];
    }
    return 0;
}

void HC_SR04::starting (void){
    _tempo.reset();
}

void HC_SR04::measure (void){
    long long stoptime = std::chrono::duration_cast<std::chrono::microseconds>(_tempo.elapsed_time()).count();
    _USSensors[_canal] = (float) stoptime / 58.0f;
}

void HC_SR04::pulseGenerator (void){
    while (true) {
        
        for (_canal=0;_canal<4;_canal++){
            _selecter->write((int)_canal%4);
            wait_us (1);
            _pulse->write(1);
            wait_us (10);
            _pulse->write(0);
            ThisThread::sleep_for(60ms);
        }
    }
}
