/*
 * Product: Hydroarm
 * Author: Ethan Barrett and Daniel Charles
 * Version: 0.0.1
 * Stage: Alpha
 * Product Description:
 * The code that runs the Hydroarm system
 */

#include "HydroArmControl.h"

HydroArmControl Arm(3, 5, 6, 10, 11);

void setup() {
  Serial.begin(9600);

  Arm.SetToZero();

}

void loop() {
  Arm.MoveAllServos(20, 30, 40, 50, 60);

  delay(1000);

  while (true) {}
}
