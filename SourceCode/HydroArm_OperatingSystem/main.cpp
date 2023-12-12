#include "mbed.h"
#include "Arm.h"
#include "Controller.h"
#include <cstdio>
#include "iostream"
#include "GantryControl.h"


Arm RASH(D3, D5, D6, D9); // s e w ee d10
GantryControl XControl(D7, D8, D4, D10, D11, 100); // step dir limit d11 d12

// main() runs in its own thread in the OS
int main()
{
    //RASH.ManualMove(90, 0);
    //RASH.CalculateInverseKinematics(0.477027, 0.0102865);
    //RASH.MoveArmToPos();

    //float q1 = RASH.returnQ1();
    //float q2 = RASH.returnQ2();

    //printf("Angle 1: %.3f | Angle 2: %.3f \n", q1, q2);

    //wait_us(5000000);

    //XControl.Home();

    while (true) {
        //RASH.ManualMove(0, 0);
        RASH.Demonstration_One();

        //XControl.XMove(50, true);
        
        //wait_us(1000000);

        //XControl.XMove(50, false);

        //wait_us(1000000);
    }
}
