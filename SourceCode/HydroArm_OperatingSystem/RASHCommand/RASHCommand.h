#ifndef RASHCommand_H
#define RASHCommand_H

#include "Arm.h"
#include "GantryControl.h"
#include "mbed.h"

class RASHCommand{
    private:
        Arm RASHArm;
        GantryControl XControl;
    public:
        RASHCommand(PinName _ShoulderRot, PinName _Shoulder, PinName _Elbow, PinName _Wrist, PinName _End, PinName _Step, PinName _Direction, PinName _Limit, PinName _Trigger, PinName _Move, float Max_Distance);
        void Run();

};

#endif