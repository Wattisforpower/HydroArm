#include "GantryControl.h"


GantryControl::GantryControl(PinName _Step, PinName _Dir): stepPin(_Step), dirPin(_Dir){
    /*
     * Assign Pins
     * @Param: _Step, _Dir
     */
}

void GantryControl::Home(){
    /*
     * Home the System
     * @Param: None
     */
}

void GantryControl::XMove(float Distance){
    // convert distance to steps
    float Steps = this->StepsPermm * Distance;

    this->dirPin = 1;

    for (int i = 0; i < Steps; i++){
        this->stepPin = 1;
        wait_us(500000);
        this->stepPin = 0;
        wait_us(500000);
    }
}
