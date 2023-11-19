#include "mbed.h"
#include "GantryControl.h"
#include "Arm.h"
#include "Controller.h"
#include <cstdio>
#include "iostream"

GantryControl XControl(D9, D10);
Arm RASH(D3, D5, D6, D9, D10);

// main() runs in its own thread in the OS
int main()
{

    while (true) {
        RASH.ManualMove(0, 0);

        float q1 = RASH.returnQ1();
        float q2 = RASH.returnQ2();

        printf("Angle 1: %.3f | Angle 2: %.3f \n", q1, q2);
        //std::cout << "Angle 1: " << q1 << " Angle 2: " << q2 << std::endl; 

        //RASH.TargetIntegrate(0, 0.5); // x y
        //RASH.CalculateInverseKinematics();
        ThisThread::sleep_for(5s);

        RASH.ManualMove(90, 90);

        q1 = RASH.returnQ1();
        q2 = RASH.returnQ2();

        printf("Angle 1: %.3f | Angle 2: %.3f \n", q1, q2);
        //std::cout << "Angle 1: " << q1 << " Angle 2: " << q2 << std::endl; 

        ThisThread::sleep_for(5s);
    }
}

