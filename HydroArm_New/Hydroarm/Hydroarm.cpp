#include "Arduino.h"
#include "Hydroarm.h"

Hydroarm::Hydroarm(){}

void Hydroarm::HydroarmInit(int ShoulderPin, int ElbowPin, int WristPin, int WristRotPin){
  this->Shoulder_Servo.attach(ShoulderPin);
  this->Elbow_Servo.attach(ElbowPin);
  this->Wrist_Servo.attach(WristPin);
  this->Wrist_Rot_Servo.attach(WristRotPin);
}

void Hydroarm::SetOffsets(int ShoulderOffset, int ElbowOffset, int WristOffset, int WristRotOffset){
  this->Offsets.Shoulder = ShoulderOffset;
  this->Offsets.Elbow = ElbowOffset;
  this->Offsets.Wrist = WristOffset;
  this->Offsets.Wrist_Rot = WristRotOffset;
}

void Hydroarm::SetToZero(){
  this->Shoulder_Servo.write(0 + this->Offsets.Shoulder);
  this->Elbow_Servo.write(0 + this->Offsets.Elbow);
  this->Wrist_Servo.write(0 + this->Offsets.Wrist);
  this->Wrist_Rot_Servo.write(0 + this->Offsets.Wrist_Rot);

  this->ServoPos.Shoulder = 0;
  this->ServoPos.Elbow = 0;
  this->ServoPos.Wrist = 0;
  this->ServoPos.Wrist_Rot = 0;
}

void Hydroarm::MoveAllServos(int ShoulderPosition, int ElbowPosition, int WristPosition, int WristRotPosition){
  this->Elbow_Servo.write(ElbowPosition);
  this->Wrist_Servo.write(WristPosition);
  this->Wrist_Rot_Servo.write(WristRotPosition);

  this->ServoPos.Shoulder = ShoulderPosition;
  this->ServoPos.Elbow = ElbowPosition;
  this->ServoPos.Wrist = WristPosition;
  this->ServoPos.Wrist_Rot = WristRotPosition;
}

void Hydroarm::MoveSingleServo(int Servo, int Position){
  /*
  * Servo Numbers:
  * 1 - Shoulder
  * 2 - Elbow
  * 3 - Wrist
  * 4 - Wrist Rotation 
  */
  switch (Servo){
    case 1:
      this->Shoulder_Servo.write(Position);
      this->ServoPos.Shoulder = Position;
      break;
    case 2:
      this->Elbow_Servo.write(Position);
      this->ServoPos.Elbow = Position;

      break;
    case 3:
      this->Wrist_Servo.write(Position); 
      this->ServoPos.Wrist = Position;
      break;
    case 4:
      this->Wrist_Rot_Servo.write(Position);
      this->ServoPos.Wrist_Rot = Position;
      break;
    default:
      break;
  }
}

void Hydroarm::CurrentPosition(){
  // find a
  // a^2 = b^2 + c^2 - 2 *b * c * cos(A)
  float A = 180 - this->ServoPos.Elbow;

  float a = sqrt(sq(this->ArmLength_Outer) + sq(this->ArmLength_Inner) - (2 * this->ArmLength_Outer * this->ArmLength_Inner * cos(A)));

  // find B
  // B = asin(b * sin(A) / a)
  float B = asin((this->ArmLength_Outer * sin(A))/ a);

  // find X
  // X = 90 - ServoPos.Shoulder - B
  float X = 90.0 - this->ServoPos.Shoulder - B;

  // find x and y Positions
  // x = asinX
  // y = acosX

  this->XPos = a * sin(X);
  this->YPos = a * cos(X);
}

void Hydroarm::Move_To_Position(int X, int Y){
  // find X
  float XAngle = atan(X / Y);

  // find A
  float aLength = sqrt(sq(this->ArmLength_Outer) + sq(this->ArmLength_Inner));

  // find n
  this->ServoPos.Elbow = 180 - acos(sq(this->ArmLength_Outer) + sq(this->ArmLength_Inner) - sq(aLength));

  // find m
  float B = asin((this->ArmLength_Outer * sin(this->ServoPos.Elbow)) / aLength);

  this->ServoPos.Shoulder = 90 - XAngle - B;

  this->MoveSingleServo(1, this->ServoPos.Shoulder);
  this->MoveSingleServo(2, this->ServoPos.Elbow);
}
