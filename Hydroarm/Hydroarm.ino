/*
 * Product: Hydroarm
 * Author: Ethan Barrett and Daniel Charles
 * Version: 0.0.1
 * Stage: Alpha
 * Product Description:
 * The code that runs the Hydroarm system
 */

 #include "HydroArmControl.h"
 
 HydroArmControl Arm(3, 5, 9, 10, 11);

void setup() {
  Serial.begin(9600);

  // Setup Arm
  Arm.SetOffsets(0, 0, 0, 0, 0);
  Arm.SetToZero();
}

void loop() {
  Arm.MoveAllServos(20, 30, 40, 50, 60)

  while(true){}
}
