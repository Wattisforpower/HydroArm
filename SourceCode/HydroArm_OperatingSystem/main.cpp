#include "mbed.h"
#include "GantryControl.h"
#include "Arm.h"
#include "Controller.h"
#include <cstdio>
#include "iostream"

GantryControl XControl(D9, D10, D8, D7, D6, 600); // 600 = 60cm in mm
Arm RASH(D3, D5, D6, D9, D10);

// main() runs in its own thread in the OS
int main()
{

    while (true) {
        //RASH.ManualMove(0, 0);
        RASH.Demonstration_One();
    }
}

