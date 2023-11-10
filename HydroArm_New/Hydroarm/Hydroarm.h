#ifndef Hydroarm_H
#define Hydroarm_H

// dependencies
#include <Servo.h>
#include <Arduino.h>

class Hydroarm{
  private:
    Servo Shoulder_Servo;
    Servo Elbow_Servo;
    Servo Wrist_Servo;
    Servo Wrist_Rot_Servo;

    struct {
      float Shoulder = 0;
      float Elbow = 0;
      float Wrist = 0;
      float Wrist_Rot = 0;
    } ServoPos;

    struct {
      float Shoulder = 0;
      float Elbow = 0;
      float Wrist = 0;
      float Wrist_Rot = 0;
    } Offsets;

    float XPos = 0.0;
    float YPos = 0.0;

    static const short ArmLength_Inner = 200;
    static const short ArmLength_Outer = 150;

    bool EndEffector_Active = false;

  public:
    Hydroarm();
    void HydroarmInit(int ShoulderPin, int ElbowPin, int WristPin, int WristRotPin);
    void SetOffsets(int ShoulderOffset, int ElbowOffset, int WristOffset, int WristRotOffset);
    void SetToZero();
    void MoveAllServos(int ShoulderPosition, int ElbowPosition, int WristPosition, int WristRotPosition);
    void MoveSingleServo(int Servo, int Position);

    void MoveForwards_H(int distance);
    void MoveBackwards_H(int distance);

    void CurrentPosition();

    void Move_To_Position(int X, int Y);

    void Calc_DesiredAngles(int X, int Y);

    void Home();
};

#endif
