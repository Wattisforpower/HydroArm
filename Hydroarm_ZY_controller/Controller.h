#include <stdint.h>
#ifndef Controller_H
#define Controller_H

#include "Arduino.h"
#include <Stepper.h>



class Controller{
  private:
    struct {
      float XPos = 0.0;
      float ZPos = 0.0;
    } XZPosition;

    int XStepsperRev = 200;
    int YStepsperRev = 200;

    struct {
      int XSteps = 0;
      int YSteps = 0;
    } StepsTaken;

    struct {
      float X = 93.0;
      float Z = 93.0;
    } StepsPermm;

    Stepper X_Stepper(XStepsperRev, 8, 9, 10, 11);
    Stepper Y_Stepper(YStepsperRev, 12, 13, 14, 15);

  public:
    Controller(int XSteps, int YSteps);
    void MoveUp(float dist);
    void MoveDown(float dist);
    void MoveLeft(float dist);
    void MoveRight(float dist);
    void Home();

};

#endif