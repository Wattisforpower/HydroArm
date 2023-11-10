#include "Controller.h"

void Controller::ErrorCalc(float current, float desired){
    this->previouserror = this->error;
    this->error = current - desired;
}

void Controller::giveError(float error){
    this->previouserror = this->error;
    this->error = error;
}

void Controller::Timeperiod(){
    float currenttime = us_ticker_read();
    this->Time_Period = currenttime - this->PreviousTime;
    this->PreviousTime = currenttime;
}

float Controller::PDContoller(){
    this->Timeperiod();

    return -(this->Kp * this->error) - (this->Kd * (this->error - this->previouserror) / this->Time_Period);
}
