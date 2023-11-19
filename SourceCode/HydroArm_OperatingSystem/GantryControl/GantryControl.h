#ifndef GantryControl_H
#define GantryControl_H

#include "mbed.h"

class GantryControl{
    private:
        float StepsPermm = 93.0; // needs to be changed
        DigitalOut stepPin;
        DigitalOut dirPin;
        float X_Max = 0.0;
    public:
        GantryControl(PinName _Step, PinName _Dir);

        void XMove(float Distance);
        void Home();
};

#endif