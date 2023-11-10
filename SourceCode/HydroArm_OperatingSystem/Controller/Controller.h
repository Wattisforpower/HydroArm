#ifndef Controller_H
#define Controller_H

#include "mbed.h"

class Controller{
    private:
        float Kp = 1.0;
        float Kd = 0.1;
        float error = 0.0;
        float previouserror = 0.0;
        float PreviousTime = 0.0;
        float Time_Period;
    
    public:
        void ErrorCalc(float current, float desired);
        void giveError(float error);
        void Timeperiod();
        float PDContoller();

};

#endif