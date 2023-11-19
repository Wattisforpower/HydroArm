#include "Arm.h"
#include <cmath>

Arm::Arm(PinName _Shoulder, PinName _Elbow, PinName _Wrist_Rot, PinName _Wrist, PinName _EndEffector): Shoulder(_Shoulder), Elbow(_Elbow), Wrist_Rot(_Wrist_Rot), Wrist(_Wrist), EndEffector(_EndEffector){
    // Home the Arm
    // Set all values to Zero

    Shoulder.calibrate(0.0005, 180);
    Elbow.calibrate(0.0005, 180);
}

void Arm::TargetIntegrate(float x, float y){
    Target.x = x;
    Target.y = y;
}

void Arm::CalculateInverseKinematics(){
    // Calculate Q2 (Positive)
    float Numerator = ((Target.x)*(Target.x)) + ((Target.y)*(Target.y)) - ((Arm_Lengths.A1)*(Arm_Lengths.A1)) - ((Arm_Lengths.A2)*(Arm_Lengths.A2));
    float Denominator = 2 * Arm_Lengths.A1 * Arm_Lengths.A2;
    float Q2 = acos(Numerator / Denominator);
    Q2 = Q2 * (180 / PI);

    // Calculate Q1 (Positive)
    float Q1 = atan2(Target.y, Target.x) - atan2((Arm_Lengths.A2 * sin(Q2)), (Arm_Lengths.A1 + Arm_Lengths.A2 * cos(Q2)));
    Q1 = Q1 * (180 / PI);

    // Alternative solutions to be added
    // -Q2
    // atan(x/y) + atan(a2*sinq2 / a1 + a2 * cosq2) 

    // Integrate desired Angles into system
    Current_Angles.q1 = Angles.q1;
    Current_Angles.q2 = Angles.q2;

    
    Angles.q1 = Q1;
    Angles.q2 = Q2;
}

float Arm::returnQ1(){
    return Angles.q1;
}

float Arm::returnQ2(){
    return Angles.q2;
}

void Arm::MoveArmToPos(){
    // Q1 - Shoulder
    // Q2 - Elbow

    Shoulder.position(Angles.q1);
    Elbow.position(Angles.q2);
}

void Arm::ManualMove(float Q1, float Q2){
    Shoulder.position(Q1);
    Elbow.position(Q2);

    //Shoulder = -Q1/180;
    //Elbow = -Q2/180;

    Angles.q1 = Q1;
    Angles.q2 = Q2;
}