#include "GantryControl.h"


GantryControl::GantryControl(PinName _Step, PinName _Dir, PinName _Limit, PinName _Trigger, PinName _Move, float Max_Dist): stepPin(_Step), dirPin(_Dir), Trigger(_Trigger), Limit_X(_Limit), Move(_Move){
    /*
     * Assign Pins
     * @Param: _Step, _Dir, _Limit, _Trigger, Max_Dist
     */

    Maximum_Positon = Max_Dist;
}

void GantryControl::Home(){
    /*
     * Home the System
     * @Param: None
     */
    
    // move the X position until it hit the limit switch

    while (Limit_X == 0){
        XMove(10, false); // 10mm anticlockwise -> check if correct direction
    }

    XMove(10, true);

    while (Limit_X == 0){
        XMove(1.0, false); // home to correct point
    }

    XMove(1.0, true); // move to position x = 1.0mm

    position_mm = 1.0; // assign the position to the system
}

void GantryControl::Assign_StepsPermm(float StepsPermmVal){
    StepsPermm = StepsPermmVal;
}

float GantryControl::Converttosteps(float Distance_m){
    return Distance_m * StepsPermm * 1000;
}

float GantryControl::Converttosteps_mm(float Distance_mm){
    return Distance_mm * StepsPermm;
}

void GantryControl::XMove(float Distance, bool direction){
    /*
     * Home the System
     * @Param: Distance in mm and direction, true is clockwise, false is anti-clockwise
     */


    // convert distance to steps
    float Steps = Converttosteps_mm(Distance);

    // Direction Control
    if (direction){
        dirPin = 1; // clockwise
    }
    else{
        dirPin = 0; // anti-clockwise
    }

    // Run system
    for (int i = 0; i < Steps; i++){
        stepPin = 1;
        wait_us(2000);
        stepPin = 0;
        wait_us(2000);
    }
}

void GantryControl::Test(){
    dirPin = 1;
    
    for (int i = 0; i < 200; i++){
        stepPin = 1;
        wait_us(2000);
        stepPin = 0;
        wait_us(2000);
    }
}



void GantryControl::AutomaticControl(float IntervalDist_mm){
    // Home the systems
    Home();

    // Move the arm
    float NextPosition = position_mm + IntervalDist_mm;

    while (true){
        // move left and right forever
        while (NextPosition < Maximum_Positon){
            XMove(IntervalDist_mm, true);
            
            NextPosition = NextPosition + IntervalDist_mm;

            Trigger = 1;

            // Wait till Safe to move again
            while (Move == 0){
                ThisThread::sleep_for(1ms); // sleep system
            }

            Trigger = 0;
        }

        NextPosition = position_mm - IntervalDist_mm;

        while (NextPosition > 1.0){
            XMove(IntervalDist_mm, false);
            
            NextPosition = NextPosition - IntervalDist_mm;

            Trigger = 1;

            // Wait till Safe to move again
            while (Move == 0){
                ThisThread::sleep_for(1ms); // sleep system
            }

            Trigger = 0;
        }
    }
}
