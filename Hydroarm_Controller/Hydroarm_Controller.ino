class PIDControllerSystem{
  private:
    float current_error = 0.0;
    float prev_error = 0.0;
    float Kp = 1.0;
    float Ki = 0.01;
    float Kd = 0.1;
    float Timestep = 0.0;
    float Date = millis();

  public:
    void ErrorCalc(current, desired);
    void TimePeriod();
    float PD_Controller();

    void TuneVals();
};

class ServoControl{
  private:
    struct {
      bool Homed = false;

      float Home_Servo_Shoulder = 0.0;
      float Home_Servo_Elbow = 0.0;
      float Home_Servo_Wrist_One = 0.0;
      float Home_Servo_Wrist_Two = 0.0;

      float Shoulder_Offset = 0.0;
      float Elbow_Offset = 0.0;
      float Wrist_One_Offset = 0.0;
      float Wrist_Two_Offset = 0.0;

      float Current_Shoulder_Pos = 0.0;
      float Current_Elbow_Pos = 0.0;
      float Current_Wrist_One_Pos = 0.0;
      float Current_Wrist_Two_Pos = 0.0;
    } Servos;
};

PIDControllerSystem PID_Servo_One;
PIDControllerSystem PID_Servo_Two;

void setup(){
  // Wait for the Button to be pressed to setup homing

}


void loop(){

}

void PIDControllerSystem::ErrorCalc(current, desired){
  this->prev_error = this->current_error;
  this->current_error = current - desired;
}

void PIDControllerSystem::TimePeriod(){
  self->Timestep = millis() - Date;
}

float PIDControllerSystem::PD_Controller(){
  this->TimePeriod();
  this->Date = millis();
  return -this->Kp * this->current_error - this->Kd * (this->current_error - this->prev_error) / this->Timestep;
}