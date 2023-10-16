#include "Arduino.h"
#include "ControlSystem.h"

ControlSystem::ControlSystem(){
  // Initialise the system
  this->Arm.SetToZero();

  pinMode(this->Sig_En, INPUT);
  pinMode(this->Sig_1, INPUT);
  pinMode(this->Sig_2, INPUT);
  pinMode(this->Sig_3, INPUT);
  pinMode(this->Sig_4, INPUT);

  Serial1.begin(9600);
}


void ControlSystem::Decode(){
  int idx = 0;
  while (Serial1.available() > 0){
    char bit = Serial1.read();

    this->Buffer[idx] = bit;

    idx++;
  }

  Serial.println(Buffer);
}

void ControlSystem::SendCommands(){
  if (this->Buffer[0:8] == "Forwards"){
    int distance = strtok(this->Buffer, ",")[1].toInt()

    Arm.MoveForwards_H(distance);
  }
}

