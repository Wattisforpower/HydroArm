#ifndef Arm_H
#define Arm_H

// https://robotacademy.net.au/lesson/inverse-kinematics-for-a-2-joint-robot-arm-using-geometry/
#include "mbed.h"
#include "Servo.h"

class Arm{
    private:
        struct{
            float x = 0.0;
            float y = 0.0;
        } Target;

        struct{
            float q1 = 0.0;
            float q2 = 0.0;
        }Angles;

        struct{
            float q1 = 0.0;
            float q2 = 0.0;
        }Current_Angles;

        struct{
            float q1 = 0.0;
            float q2 = 0.0;
        }Offsets;

        struct{
            float A1 = 0.225;
            float A2 = 0.255;
        }Arm_Lengths;
        
        Servo Shoulder;
        Servo Elbow;
        Servo Wrist_Rot;
        Servo Wrist;
        Servo EndEffector;

        float PI = 3.14159;

    public:
        Arm(PinName _Shoulder, PinName _Elbow, PinName _Wrist_Rot, PinName _Wrist, PinName _EndEffector);
        void TargetIntegrate(float x, float y);
        void CalculateInverseKinematics(float x, float y);
        float returnQ1();
        float returnQ2();

        // Arm Movement
        void MoveArmToPos();
        void ManualMove(float Q1, float Q2);
        void Home();

        // Demonstrations
        void Demonstration_One();
        
};

#endif
