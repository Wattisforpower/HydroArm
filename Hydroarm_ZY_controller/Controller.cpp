#include "Controller.h"

Controller::Controller(float XSteps, float YSteps){
  this->XStepsperRev = XSteps;
  this->YStepsperRev = YSteps;
}

void Controller::MoveDown(float dist){
  int totalSteps = this->StepsPermm.Z * dist;

}