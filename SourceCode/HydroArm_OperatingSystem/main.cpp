#include "mbed.h"
#include "Arm.h"
#include "Controller.h"
#include <cstdio>
#include "iostream"
#include "GantryControl.h"


Arm RASH(D11, D3, D5, D6, D9); // s e w ee d10
GantryControl XControl(D7, D8, D4, D10, D11, 100); // step dir limit d11 d12

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        //RASHARM.Run();
        //RASH.Demonstration_Two();
        RASH.Demonstration_One();
    }
}
