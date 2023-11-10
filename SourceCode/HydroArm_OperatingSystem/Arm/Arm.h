#ifndef Arm_H
#define Arm_H

// https://robotacademy.net.au/lesson/inverse-kinematics-for-a-2-joint-robot-arm-using-geometry/
#include "mbed.h"

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
            float A1 = 10.0;
            float A2 = 10.0;
        }Arm_Lengths;

    public:
        void TargetIntergrate(float x, float y); // must be done before calculate IK
        void CalculateInverseKinematics();
        float returnQ1();
        float returnQ2();

};

#endif