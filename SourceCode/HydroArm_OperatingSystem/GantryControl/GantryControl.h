#ifndef GantryControl_H
#define GantryControl_H

#include "mbed.h"

class GantryControl{
    private:
        float StepsPermm = 93.0; // needs to be changed
        DigitalOut stepPin;
        DigitalOut dirPin;
        DigitalOut Trigger;
        DigitalIn Limit_X;
        DigitalIn Move;

        float X_Max = 0.0;
        float position_mm;
        float Maximum_Positon;
    public:
        GantryControl(PinName _Step, PinName _Dir, PinName _Limit, PinName Trigger, PinName _Move,  float Max_Dist);
        void Assign_StepsPermm(float StepsPermmVal);
        float Converttosteps(float Distance_m);
        float Converttosteps_mm(float Distance_mm);
        void XMove(float Distance, bool direction);
        void Home();

        void AutomaticControl(float IntervalDist_mm);
};

#endif