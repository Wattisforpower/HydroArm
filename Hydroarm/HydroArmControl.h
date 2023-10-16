#ifndef HydroArmControl_H
#define HydroArmControl_H

#include <Arduino.h>


/*
 * Servo Numbers:
 * 1 - Shoulder Rotation
 * 2 - Shoulder
 * 3 - Elbow
 * 4 - Wrist
 * 5 - Wrist Rotation 
 */

class HydroArmControl{
  private:
    // Arm Variables
    struct {
      int Shoulder_Rot = 0;
      int Shoulder = 0;
      int Elbow = 0;
      int Wrist = 0;
      int Wrist_Rot = 0;
    } ServoPos;
    struct {
      int Shoulder_Rot = 0;
      int Shoulder = 0;
      int Elbow = 0;
      int Wrist = 0;
      int Wrist_Rot = 0;
    } Offsets;

    int ZPos = 0;
    int YPos = 0;

    static short ArmLength = 150; //15cm in mm

    // End Effector Variables
    bool EndEffectorActive = false;
    string EndEffectorSelection = "";

  public:
    // Main Arm System
    HydroArmControl(int ShoulderRotPin, int ShoulderPin, int ElbowPin, int WristPin, int WristRotPin);
    void SetOffsets(int ShoulderRotOffset, int ShoulderOffset, int ElbowOffset, int WristOffset, int WristRotOffset);
    void SetToZero();
    void MoveAllServos(int ShoulderRotPosition, int ShoulderPosition, int ElbowPosition, int WristPosition, int WristRotPosition);
    void MoveSingleServo(int Servo, int Position);

    void CurrentZYPos();

    void MoveForwards_H(int distance);
    void MoveBackwards_H(int distance);
    void MoveUp_V(int distance);
    void MoveDown_V(int distance);

    // End Effector
    void ActivateEndEffector(bool Active, string Selection);

    // EndEffector - Pickers
    void OpenPicker();
    void ClosePicker();    
    void PickFruit();

    // EndEffector - Planter
    void Plant();   

};

#endif