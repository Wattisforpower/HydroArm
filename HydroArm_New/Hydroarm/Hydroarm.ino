/*
 * Product: Hydroarm
 * Author: Ethan Barrett and Daniel Charles
 * Version: 0.0.2
 * Stage: Alpha
 * Product Description:
 * The code that runs the Hydroarm system
 */

#include <Servo.h>

Servo Shoulder_Servo;
Servo Elbow_Servo;
Servo Wrist_Servo;
Servo Wrist_Rot_Servo;

struct {
  float Shoulder = 0.0;
  float Elbow = 0.0;
  float Wrist = 0.0;
  float Wrist_Rot = 0.0;
} ServoPos;

struct {
  float Shoulder = 0.0;
  float Elbow = 0.0;
  float Wrist = 0.0;
  float Wrist_Rot = 0.0;
} Offsets;

float XPos = 0.0;
float YPos = 0.0;

static const short ArmLength_Inner = 200.0;
static const short ArmLength_Outer = 150.0;

bool EndEffector_Active = false;

void setup(){
  Shoulder_Servo.attach(2);
  Elbow_Servo.attach(3);
  Wrist_Servo.attach(4);
  Wrist_Rot_Servo.attach(5);
}



void SetOffsets(int ShoulderOffset, int ElbowOffset, int WristOffset, int WristRotOffset){
  Offsets.Shoulder = ShoulderOffset;
  Offsets.Elbow = ElbowOffset;
  Offsets.Wrist = WristOffset;
  Offsets.Wrist_Rot = WristRotOffset;
}

void SetToZero(){
  Shoulder_Servo.write(0 + Offsets.Shoulder);
  Elbow_Servo.write(0 + Offsets.Elbow);
  Wrist_Servo.write(0 + Offsets.Wrist);
  Wrist_Rot_Servo.write(0 + Offsets.Wrist_Rot);

  ServoPos.Shoulder = 0;
  ServoPos.Elbow = 0;
  ServoPos.Wrist = 0;
  ServoPos.Wrist_Rot = 0;
}

void MoveAllServos(int ShoulderPosition, int ElbowPosition, int WristPosition, int WristRotPosition){
  Elbow_Servo.write(ElbowPosition);
  Wrist_Servo.write(WristPosition);
  Wrist_Rot_Servo.write(WristRotPosition);

  ServoPos.Shoulder = ShoulderPosition;
  ServoPos.Elbow = ElbowPosition;
  ServoPos.Wrist = WristPosition;
  ServoPos.Wrist_Rot = WristRotPosition;
}

void MoveSingleServo(int Servo, int Position){
  /*
  * Servo Numbers:
  * 1 - Shoulder
  * 2 - Elbow
  * 3 - Wrist
  * 4 - Wrist Rotation 
  */
  switch (Servo){
    case 1:
      Shoulder_Servo.write(Position);
      ServoPos.Shoulder = Position;
      break;
    case 2:
      Elbow_Servo.write(Position);
      ServoPos.Elbow = Position;

      break;
    case 3:
      Wrist_Servo.write(Position); 
      ServoPos.Wrist = Position;
      break;
    case 4:
      Wrist_Rot_Servo.write(Position);
      ServoPos.Wrist_Rot = Position;
      break;
    default:
      break;
  }
}

void CurrentPosition(){
  // find a
  // a^2 = b^2 + c^2 - 2 *b * c * cos(A)
  float A = 180 - ServoPos.Elbow;

  float a = sqrt(sq(ArmLength_Outer) + sq(ArmLength_Inner) - (2 * ArmLength_Outer * ArmLength_Inner * cos(A)));

  // find B
  // B = asin(b * sin(A) / a)
  float B = asin((ArmLength_Outer * sin(A))/ a);

  // find X
  // X = 90 - ServoPos.Shoulder - B
  float X = 90.0 - ServoPos.Shoulder - B;

  // find x and y Positions
  // x = asinX
  // y = acosX

  XPos = a * sin(X);
  YPos = a * cos(X);
}

void Move_To_Position(int X, int Y){
  // find X
  float XAngle = atan(X / Y);

  // find A
  float aLength = 250.0;

  // find n
  ServoPos.Elbow = 180 - acos(sq(ArmLength_Outer) + sq(ArmLength_Inner) - sq(aLength));

  // find m
  float B = asin((ArmLength_Outer * sin(ServoPos.Elbow)) / aLength);

  ServoPos.Shoulder = 90 - XAngle - B;

  MoveSingleServo(1, ServoPos.Shoulder);
  MoveSingleServo(2, ServoPos.Elbow);
}

int angle = 10;

void loop(){
  for(angle = 10; angle < 180; angle++)  
  {                                  
    Shoulder_Servo.write(angle);
    Elbow_Servo.write(angle);
    delay(15);                
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    Shoulder_Servo.write(angle);
    Elbow_Servo.write(angle);
    delay(15);  
  } 
}
