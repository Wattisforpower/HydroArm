#ifndef ControlSystem_H
#define ControlSystem_H

#include "HydroArmControl.h"
#include <Arduino.h>


/*
 * Servo Numbers:
 * 1 - Shoulder Rotation 3
 * 2 - Shoulder 5
 * 3 - Elbow 6
 * 4 - Wrist 10
 * 5 - Wrist Rotation 11
 */

class ControlSystem{
  private:
    HydroArmControl Arm(3, 5, 6, 10, 11);
    int Sig_En = 1;
    int Sig_1 = 2;
    int Sig_2 = 4;
    int Sig_3 = 7;
    int Sig_4 = 8;

    char Buffer[64];

  public:
    ControlSystem();
    void Decode();
    void SendCommands();

};


#endif
