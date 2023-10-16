#include "HydroArmControl.h"



HydroArmControl::HydroArmControl(int ShoulderRotPin, int ShoulderPin, int ElbowPin, int WristPin, int WristRotPin){
  this->Shoulder_Rot_Servo.attach(ShoulderRotPin);
  this->Shoulder_Servo.attach(ShoulderPin);
  this->Elbow_Servo.attach(ElbowPin);
  this->Wrist_Servo.attach(WristPin);
  this->Wrist_Rot_Servo.attach(WristRotPin);
}

void HydroArmControl::SetOffsets(int ShoulderRotOffset, int ShoulderOffset, int ElbowOffset, int WristOffset, int WristRotOffset){
  this->Offsets.Shoulder_Rot = ShoulderRotOffset;
  this->Offsets.Shoulder = ShoulderOffset;
  this->Offsets.Elbow = ElbowOffset;
  this->Offsets.Wrist = WristOffset;
  this->Offsets.Wrist_Rot = WristRotOffset;
}

void HydroArmControl::SetToZero(){
  this->Shoulder_Rot_Servo.write(0 + this->Offsets.Shoulder_Rot);
  this->Shoulder_Servo.write(0 + this->Offsets.Shoulder);
  this->Elbow_Servo.write(0 + this->Offsets.Elbow);
  this->Wrist_Servo.write(0 + this->Offsets.Wrist);
  this->Wrist_Rot_Servo.write(0 + this->Offsets.Wrist_Rot);

  this->ServoPos.Shoulder_Rot = 0;
  this->ServoPos.Shoulder = 0;
  this->ServoPos.Elbow = 0;
  this->ServoPos.Wrist = 0;
  this->ServoPos.Wrist_Rot = 0;
}

void HydroArmControl::MoveAllServos(int ShoulderRotPosition, int ShoulderPosition, int ElbowPosition, int WristPosition, int WristRotPosition){

  // Run Code
  this->Shoulder_Rot_Servo.write(ShoulderRotPosition);
  this->Shoulder_Servo.write(ShoulderPosition);
  this->Elbow_Servo.write(ElbowPosition);
  this->Wrist_Servo.write(WristPosition);
  this->Wrist_Rot_Servo.write(WristRotPosition);

  this->ServoPos.Shoulder_Rot = ShoulderRotPosition;
  this->ServoPos.Shoulder = ShoulderPosition;
  this->ServoPos.Elbow = ElbowPosition;
  this->ServoPos.Wrist = WristPosition;
  this->ServoPos.Wrist_Rot = WristRotPosition;
}

void HydroArmControl::MoveSingleServo(int Servo, int Position){
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
      this->Shoulder_Rot_Servo.write(Position);
      this->ServoPos.Shoulder_Rot = Position;

      break;
    case 2:
      this->Shoulder_Servo.write(Position);
      this->ServoPos.Shoulder = Position;
      break;
    case 3:
      this->Elbow_Servo.write(Position);
      this->ServoPos.Elbow = Position;

      break;
    case 4:
      this->Wrist_Servo.write(Position); 
      this->ServoPos.Wrist = Position;
      break;
    case 5:
      this->Wrist_Rot_Servo.write(Position);
      this->ServoPos.Wrist_Rot = Position;
      break;
    default:
      break;
  }
}

void HydroArmControl::CurrentZYPos(){
  // Shoulder, Elbow
  this->YPos = this->ArmLength * cos(this->ServoPos.Shoulder + this->ServoPos.Elbow) + this->ArmLength * cos(this->ServoPos.Shoulder);
  this->ZPos = this->ArmLength * sin(this->ServoPos.Shoulder + this->ServoPos.Elbow) + this->ArmLength * sin(this->ServoPos.Shoulder);
}

int HydroArmControl::Alpha1(int Z, int Y){
  return atan((Z) / (Y)) - (atan((this->ArmLength * sin(this->Alpha2(int Z, int Y)) / (this->ArmLength + (this->ArmLength * cos(this->Alpha2(int Z, int Y))))));
}

int HydroArmControl::Alpha2(int Z, int Y){
  return acos(((Z * Z) + (Y * Y) - (this->ArmLength * this->ArmLength) - (this->ArmLength * this->ArmLength)) / 2 * (this->ArmLength * this->ArmLength));
}

void HydroArmControl::MoveForwards_H(int distance_mm){
  this->CurrentZYPos();


  int TargetPositionY = this->YPos + distance_mm;

  // work out Shoulder Angle
  //this->ServoPos.Elbow = acos(((this->ZPos * this->ZPos) + (TargetPositionY * TargetPositionY) - (this->ArmLength * this->ArmLength) - (this->ArmLength * this->ArmLength)) / 2 * (this->ArmLength * this->ArmLength));
  //this->ServoPos.Shoulder = atan((this->ZPos) / (TargetPositionY)) - (atan((this->ArmLength * sin(this->ServoPos.Elbow)) / (this->ArmLength + (this->ArmLength * cos(this->ServoPos.Elbow)))));

  this->ServoPos.Elbow = this->Alpha1(this->ZPos, TargetPositionY);
  this->ServoPos.Shoulder = this->Alpha2(this->ZPos, TargetPositionY);

  // Position the arm accordingly

  this->MoveSingleServo(2, this->ServoPos.Shoulder);
  this->MoveSingleServo(3, this->ServoPos.Elbow);

  delay(15); // Wait for the servos to move
}

void HydroArmControl::MoveBackwards_H(int distance){
  this->CurrentZYPos();

  int TargetPositionY = this->YPos - distance;

  //this->ServoPos.Elbow = acos(((this->ZPos * this->ZPos) + (TargetPositionY * TargetPositionY) - (this->ArmLength * this->ArmLength) - (this->ArmLength * this->ArmLength)) / 2 * (this->ArmLength * this->ArmLength));
  //this->ServoPos.Shoulder = atan((this->ZPos) / (TargetPositionY)) - (atan((this->ArmLength * sin(this->ServoPos.Elbow)) / (this->ArmLength + (this->ArmLength * cos(this->ServoPos.Elbow)))));

  this->ServoPos.Elbow = this->Alpha1(this->ZPos, TargetPositionY);
  this->ServoPos.Shoulder = this->Alpha2(this->ZPos, TargetPositionY);

  // Position the arm accordingly

  this->MoveSingleServo(2, this->ServoPos.Shoulder);
  this->MoveSingleServo(3, this->ServoPos.Elbow);
}

void HydroArmControl::MoveUp_V(int distance){
  this->CurrentZYPos();

  int TargetPositionZ = this->ZPos + distance;

  this->ServoPos.Elbow = this->Alpha1(TargetPositionZ, this->YPos);
  this->ServoPos.Shoulder = this->Alpha2(TargetPositionZ, this->YPos);

  this->MoveSingleServo(2, this->ServoPos.Shoulder);
  this->MoveSingleServo(3, this->ServoPos.Elbow);
}

void HydroArmControl::MoveDown_V(int distance){
  this->CurrentZYPos();

  int TargetPositionZ = this->ZPos - distance;

  this->ServoPos.Elbow = this->Alpha1(TargetPositionZ, this->YPos);
  this->ServoPos.Shoulder = this->Alpha2(TargetPositionZ, this->YPos);

  this->MoveSingleServo(2, this->ServoPos.Shoulder);
  this->MoveSingleServo(3, this->ServoPos.Elbow);
}

void HydroArmControl::MoveAngled(int Dist_Horizontal, int Dist_Vertical){
  this->CurrentZYPos();

  int TargetY = this->YPos + Dist_Horizontal;
  int TargetZ = this->ZPos + Dist_Vertical;

  this->ServoPos.Elbow = this->Alpha1(TargetZ, TargetY);
  this->ServoPos.Shoulder = this->Alpha2(TargetZ, TargetY);

  this->MoveSingleServo(2, this->ServoPos.Shoulder);
  this->MoveSingleServo(3, this->ServoPos.Elbow);
}

void HydroArmControl::MoveToPosition(int Z, int Y){
  this->ServoPos.Elbow = this->Alpha1(Z, Y);
  this->ServoPos.Shoulder = this->Alpha2(Z, Y);

  this->MoveSingleServo(2, this->ServoPos.Shoulder);
  this->MoveSingleServo(3, this->ServoPos.Elbow);
}

void HydroArmControl::LiftArm(){
  this->MoveSingleServo(3, this->ServoPos.Elbow);
}

void HydroArmControl::RotateBase(int angle){
  this->MoveSingleServo(1, angle);
}

void HydroArmControl::RotateWrist(int angle){
  this->MoveSingleServo(5, angle);
}

void HydroArmControl::FindXYfromAngles(){
  this->YPos = this->ArmLength * cos(this->ServoPos.Shoulder + this->ServoPos.Elbow) + this->ArmLength * cos(this->ServoPos.Shoulder);
  this->ZPos = this->ArmLength * sin(this->ServoPos.Shoulder + this->ServoPos.Elbow) + this->ArmLength * sin(this->ServoPos.Shoulder);
}

// EndEffector Code
void HydroArmControl::EndEffectorReset(){
  this->MoveSingleServo(4, 0);
  this->MoveSingleServo(5, 0);
}

void HydroArmControl::LiftEndEffector(int angle){
  this->MoveSingleServo(5, angle)
}

void HydroArmControl::Init_Picker(int Pin, int offset){
  this->EndEffector_Picker.attach(Pin);
  this->EndEffector_Picker.write(0 + offset);
}

void HydroArmControl::OpenPicker(){
  this->EndEffector_Picker.write(90);
}

void HydroArmControl::ClosePicker(){
  // Slowly close the gripper until tacktile feeback
}
