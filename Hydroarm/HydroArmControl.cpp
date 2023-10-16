#include "HydroArmControl.h"

#include <Servo.h>

Servo Shoulder_Rot_Servo;
Servo Shoulder_Servo;
Servo Elbow_Servo;
Servo Wrist_Servo;
Servo Wrist_Rot_Servo;

HydroArmControl::HydroArmControl(int ShoulderRotPin, int ShoulderPin, int ElbowPin, int WristPin, int WristRotPin){
  Shoulder_Rot_Servo.attach(ShoulderRotPin);
  Shoulder_Servo.attach(ShoulderPin);
  Elbow_Servo.attach(ElbowPin);
  Wrist_Servo.attach(WristPin);
  Wrist_Rot_Servo.attach(WristRotPin);
}

HydroArmControl::SetOffsets(int ShoulderRotOffset, int ShoulderOffset, int ElbowOffset, int WristOffset, int WristRotOffset){
  this->Offsets.Shoulder_Rot = ShoulderRotOffset;
  this->Offsets.Shoulder = ShoulderOffset;
  this->Offsets.Elbow = ElbowOffset;
  this->Offsets.Wrist = WristOffset;
  this->Offsets.Wrist_Rot = WristRotOffset;
}

HydroArmControl::SetToZero(){
  Shoulder_Rot_Servo.write(0 + this->Offsets.Shoulder_Rot);
  Shoulder_Servo.write(0 + this->Offsets.Shoulder);
  Elbow_Servo.write(0 + this->Offsets.Elbow);
  Wrist_Servo.write(0 + this->Offsets.Wrist);
  Wrist_Rot_Servo.write(0 + this->Offsets.Wrist_Rot);

  this->ServoPos.Shoulder_Rot = 0;
  this->ServoPos.Shoulder = 0;
  this->ServoPos.Elbow = 0;
  this->ServoPos.Wrist = 0;
  this->ServoPos.Wrist_Rot = 0;
}

HydroArmControl::MoveAllServos(int ShoulderRotPosition, int ShoulderPosition, int ElbowPosition, int WristPosition, int WristRotPosition){
  
  // Check all are valid movements
  if ((0 < ShoulderRotPosition < 180) && (0 < ShoulderPosition < 180) && (0 < ElbowPosition < 180) && (0 < WristPosition< 180) && (0 < WristRotPosition < 180)){
    // Run Code
    Shoulder_Rot_Servo.write(ShoulderRotPosition);
    Shoulder_Servo.write(ShoulderPosition);
    Elbow_Servo.write(ElbowPosition);
    Wrist_Servo.write(WristPosition);
    Wrist_Rot_Servo.write(WristRotPosition);

    this->ServoPos.Shoulder_Rot = ShoulderRotPosition;
    this->ServoPos.Shoulder = ShoulderPosition;
    this->ServoPos.Elbow = ElbowPosition;
    this->ServoPos.Wrist = WristPosition;
    this->ServoPos.Wrist_Rot = WristRotPosition;

    delay(15); // wait for servos to move
  }
}

HydroArmControl::MoveSingleServo(int Servo, int Position){
  /*
  * Servo Numbers:
  * 1 - Shoulder Rotation
  * 2 - Shoulder
  * 3 - Elbow
  * 4 - Wrist
  * 5 - Wrist Rotation 
  */
  switch (Servo){
    case 1:
      if (0 < Position < 180){
        Shoulder_Rot_Servo.write(Position);

        this->ServoPos.Shoulder_Rot = ShoulderRotPosition;
      }
      break;
    case 2:
      if (0 < Position < 180){
        Shoulder_Servo.write(Position);

        this->ServoPos.Shoulder = ShoulderPosition;

      }
      break;
    case 3:
      if (0 < Position < 180){
        Elbow_Servo.write(Position);
        this->ServoPos.Elbow = ElbowPosition;
      }
      break;
    case 4:
      if (0 < Position < 180){
        Wrist_Servo.write(Position);
        
        this->ServoPos.Wrist = WristPosition;
    
      }
      break;
    case 5:
      if (0 < Position < 180){
        Wrist_Rot_Servo.write(Position);
        this->ServoPos.Wrist_Rot = WristRotPosition;
      }
      break;
    default:
      break;
  }
}

HydroArmControl::CurrentZYPos(){
  // Shoulder, Elbow
  this->YPos = this->ArmLength * cos(this->ServoPos.Shoulder + this->ServoPos.Elbow) + this->ArmLength * cos(this->ServoPos.Shoulder);
  this->ZPos = this->ArmLength * sin(this->ServoPos.Shoulder + this->ServoPos.Elbow) + this->ArmLength * sin(this->ServoPos.Shoulder);
}

HydroArmControl::MoveForwards_H(int distance_mm){
  this->CurrentZYPos();


  int TargetPositionY = this->YPos + distance_mm;

  // work out Shoulder Angle
  this->ServoPos.Elbow = acos(((this->ZPos * this->ZPos) + (TargetPositionY * TargetPositionY) - (this->ArmLength * this->ArmLength) - (this->ArmLength * this->ArmLength)) / 2 * (this->ArmLength * this->ArmLength));
  this->ServoPos.Shoulder = atan((this->ZPos) / (TargetPositionY)) - (atan((this->ArmLength * sin(this->ServoPos.Elbow)) / (this->ArmLength + (this->ArmLength * cos(this->ServoPos.Elbow)))));


}

// EndEffector Code

HydroArmControl::ActivateEndEffector(bool Active, string Selection){
  this->EndEffectorActive = Active;
  this->EndEffectorSelection = Selection;
}


