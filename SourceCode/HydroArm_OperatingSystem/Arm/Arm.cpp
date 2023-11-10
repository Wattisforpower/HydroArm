#include "Arm.h"
#include <cmath>

void Arm::TargetIntergrate(float x, float y){
    this->Target.x = x;
    this->Target.y = y;
}

void Arm::CalculateInverseKinematics(){
    // Calculate Q2
    float Numerator = ((this->Target.x)*(this->Target.x)) + ((this->Target.y)*(this->Target.y)) - ((this->Arm_Lengths.A1)*(this->Arm_Lengths.A1)) - ((this->Arm_Lengths.A2)*(this->Arm_Lengths.A2));
    float Denominator = 2 * this->Arm_Lengths.A1 * this->Arm_Lengths.A2;
    float Q2 = acos(Numerator / Denominator);

    // Calculate Q1
    float Q1 = atan2(this->Target.y, this->Target.x) - atan2((this->Arm_Lengths.A2 * sin(Q2)), (this->Arm_Lengths.A1 + this->Arm_Lengths.A2 * cos(Q2)));

    // Integrate desired Angles into system
    this->Current_Angles.q1 = this->Angles.q1;
    this->Current_Angles.q2 = this->Angles.q2;

    this->Angles.q1 = Q1;
    this->Angles.q2 = Q2;
}

float Arm::returnQ1(){
    return this->Angles.q1;
}

float Arm::returnQ2(){
    return this->Angles.q2;
}