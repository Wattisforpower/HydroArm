#include "mbed.h"
#include "GantryControl.h"
#include "Arm.h"
#include "Controller.h"
#include <cstdio>
#include "iostream"

GantryControl XControl(D9, D10, D8, D7, D6, 600); // 600 = 60cm in mm
Arm RASH(D3, D5, D6, D9); // s e w ee

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

    while (true) {
        //RASH.ManualMove(0, 0);
        RASH.Demonstration_One();
    }
}
