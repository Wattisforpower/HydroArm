#include "Controller.h"

void Controller::ErrorCalc(float current, float desired){
    previouserror = error;
    error = current - desired;
}

void Controller::giveError(float Error){
    previouserror = error;
    error = Error;
}

void Controller::Timeperiod(){
    float currenttime = us_ticker_read();
    Time_Period = currenttime - PreviousTime;
    PreviousTime = currenttime;
}

float Controller::PDContoller(){
    Timeperiod();

    return -(Kp * error) - (Kd * (error - previouserror) / Time_Period);
}
