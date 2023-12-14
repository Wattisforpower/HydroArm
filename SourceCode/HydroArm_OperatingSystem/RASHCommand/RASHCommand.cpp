#include "RASHCommand.h"

RASHCommand::RASHCommand(PinName _ShoulderRot, PinName _Shoulder, PinName _Elbow, PinName _Wrist, PinName _End, PinName _Step, PinName _Direction, PinName _Limit, PinName _Trigger, PinName _Move, float Max_Distance): RashArm(_ShoulderRot, _Shoulder, _Elbow, _Wrist, _End), XControl(_Step, _Directions, _Limit, _ Trigger, _Move, Max_Distance){
    
}

void RASHCommand::Run(){
    // Move to first position
    
}
