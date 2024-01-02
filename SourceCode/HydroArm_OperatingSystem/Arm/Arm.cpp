#include "Arm.h"
#include <cmath>

Arm::Arm(PinName _ShoulderRot, PinName _Shoulder, PinName _Elbow, PinName _Wrist, PinName _EndEffector): ShoulderRot(_ShoulderRot), Shoulder(_Shoulder), Elbow(_Elbow), Wrist(_Wrist), EndEffector(_EndEffector){
    // Home the Arm
    // Set all values to Zero

    ShoulderRot.calibrate(0.002, 180);
    Shoulder.calibrate(0.002, 180); // 0.002 for SG90
    Elbow.calibrate(0.002, 180); // 0.002 for SG90
    Wrist.calibrate(0.002, 180);
    EndEffector.calibrate(0.002, 180);
}

void Arm::TargetIntegrate(float y, float x){
    Target.x = x;
    Target.y = y;
}

void Arm::CalculateInverseKinematics(float y, float x){
    // Take in the Targets
    TargetIntegrate(x, y);

    // Calculate Q2 (Positive)
    float Numerator = ((Target.x)*(Target.x)) + ((Target.y)*(Target.y)) - ((Arm_Lengths.A1)*(Arm_Lengths.A1)) - ((Arm_Lengths.A2)*(Arm_Lengths.A2));
    float Denominator = 2 * Arm_Lengths.A1 * Arm_Lengths.A2;
    float Q2 = acos(Numerator / Denominator);

    // Calculate Q1 (Positive)
    float Q1 = atan2(Target.y, Target.x) - atan2((Arm_Lengths.A2 * sin(Q2)) / (Arm_Lengths.A1 + Arm_Lengths.A2 * cos(Q2)));
    Q1 = Q1 * (180 / PI);
    Q2 = Q2 * (180 / PI);

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

    ShoulderRot.position(Shoulder.read());
    Wrist.position(Angles.q1);
}

void Arm::ManualMove(float Q1, float Q2){
    Shoulder.position(Q1);
    Elbow.position(Q2);

    //Shoulder = -Q1/180;
    //Elbow = -Q2/180;

    Angles.q1 = Q1;
    Angles.q2 = Q2;
}

void Arm::CalcOffsets(){
    Offsets.q1 = Shoulder.read();
    Offsets.q2 = Shoulder.read();
}

void Arm::Demonstration_One(){
    //CalcOffsets();

    //wait_us(2000000);

    CalculateInverseKinematics(0.31691, 0.149744);
    MoveArmToPos();

    float q1 = returnQ1();
    float q2 = returnQ2();

    printf("P1: Angle 1: %.3f | Angle 2: %.3f \n", q1, q2);

    wait_us(2000000);

    CalculateInverseKinematics(0.116017, 0.147761);
    MoveArmToPos();

    q1 = returnQ1();    
    q2 = returnQ2();

    printf("P2: Angle 1: %.3f | Angle 2: %.3f \n", q1, q2);

    wait_us(2000000);

    CalculateInverseKinematics(0.117893, 0.278706);
    MoveArmToPos();

    q1 = returnQ1();    
    q2 = returnQ2();

    printf("P3: Angle 1: %.3f | Angle 2: %.3f \n", q1, q2);

    wait_us(2000000);

    CalculateInverseKinematics(0.316273, 0.282034);
    MoveArmToPos();


    q1 = returnQ1();    
    q2 = returnQ2();

    printf("P4: Angle 1: %.3f | Angle 2: %.3f \n", q1, q2);
    wait_us(2000000);
}

void Arm::MoveWithPID(float TargetQ1, float TargetQ2){
    // Find current Positions
    float currentQ1 = Shoulder.read();
    float currentQ2 = Elbow.read();
    PIDQ1.Timeperiod();
    PIDQ2.Timeperiod();

    PIDQ1.ErrorCalc(currentQ1, TargetQ1);
    PIDQ2.ErrorCalc(currentQ2, TargetQ2);

    while ((TargetQ1 - currentQ1 > 0.1) && (TargetQ2 - currentQ2 > 0.1)){
        // run the PD controller
        float Q1Movement = PIDQ1.PDContoller();
        float Q2Movement = PIDQ2.PDContoller();

        // Calculate New Positions
        float Q1New = currentQ1 + Q1Movement;
        float Q2New = currentQ2 + Q2Movement;

        // Move to Positions
        ManualMove(Q1New, Q2New);

        // Temporary code - Print positions
        printf("Q1 angle: %0.3f | Q2 angle: %0.3f  \n", Q1New, Q2New);
        
        // Wait for movement to occur
        wait_us(1000000); //1s

        // check positions and save updated
        currentQ1 = Shoulder.read();
        currentQ2 = Elbow.read();

        // Calculate new error

        PIDQ1.ErrorCalc(currentQ1, TargetQ1);
        PIDQ2.ErrorCalc(currentQ2, TargetQ2);
        // repeat until 0 error on both
    }

}

void Arm::Demonstration_Two(){
    // Move to 1st Position
    CalculateInverseKinematics(0.31691, 0.149744);
    printf("Target Positions: %0.3f, %0.3f", Angles.q1, Angles.q2);
    MoveWithPID(Angles.q1, Angles.q2);

    // Move to 2nd Position
    CalculateInverseKinematics(0.117893, 0.278706);

    MoveWithPID(Angles.q1, Angles.q2);
}

void Arm::MoveArmUp(){
    ShoulderRot.position((ShoulderRot.read() + 45));
}

void Arm::MoveArmDown(){
    ShoulderRot.position((ShoulderRot.read() - 45));
}
