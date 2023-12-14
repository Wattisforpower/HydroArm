#include "RASHCommand.h"

RASHCommand::RASHCommand(PinName _ShoulderRot, PinName _Shoulder, PinName _Elbow, PinName _Wrist, PinName _End, PinName _Step, PinName _Direction, PinName _Limit, PinName _Trigger, PinName _Move, float Max_Distance): RASHArm(_ShoulderRot, _Shoulder, _Elbow, _Wrist, _End), XControl(_Step, _Direction, _Limit, _Trigger, _Move, Max_Distance){}

void RASHCommand::Run(){
    // Move to first position
    XControl.XMove(100, true);
    RASHArm.CalculateInverseKinematics(0.31691, 0.149744);
    RASHArm.MoveArmToPos();
    //RASHArm.MoveWithPID(RASHArm.returnQ1() , RASHArm.returnQ2());

    //send code
    XControl.Trigger = 1;

    wait_us(100000); //100ms

    XControl.Trigger = 0;

    //while(XControl.Limit_X != 1){}

    // Move arm to second position
    RASHArm.CalculateInverseKinematics(0.116017, 0.147761);
    RASHArm.MoveArmToPos();
    //RASHArm.MoveWithPID(RASHArm.returnQ1() , RASHArm.returnQ2());

    //send code
    XControl.Trigger = 1;

    wait_us(100000); //100ms

    XControl.Trigger = 0;

    //while(XControl.Limit_X != 1){}

    // reset Arm
    // Move arm to position
    //RASHArm.CalculateInverseKinematics(0.1, 0.1);
    //RASHArm.MoveArmToPos();
    //RASHArm.MoveWithPID(RASHArm.returnQ1() , RASHArm.returnQ2());

    // NEXT SET

    // Move to first position
    XControl.XMove(100, false);
    RASHArm.CalculateInverseKinematics(0.31691, 0.149744);
    RASHArm.MoveArmToPos();
    //RASHArm.MoveWithPID(RASHArm.returnQ1() , RASHArm.returnQ2());

    //send code
    XControl.Trigger = 1;

    wait_us(100000); //100ms

    XControl.Trigger = 0;

    //while(XControl.Limit_X != 1){}

    // Move arm to second position
    RASHArm.CalculateInverseKinematics(0.116017, 0.147761);
    RASHArm.MoveArmToPos();
    //RASHArm.MoveWithPID(RASHArm.returnQ1() , RASHArm.returnQ2());

    //send code
    XControl.Trigger = 1;

    wait_us(100000); //100ms

    XControl.Trigger = 0;

    //while(XControl.Limit_X != 1){}

    // reset Arm
    // Move arm to position
    //RASHArm.CalculateInverseKinematics(0.1, 0.1);
    //RASHArm.MoveArmToPos();
    //RASHArm.MoveWithPID(RASHArm.returnQ1() , RASHArm.returnQ2());

    // reset x position
    //XControl.XMove(200, false);
}
