#include "Arduino.h"
#include "CustomStepper.h"

CustomStepper::CustomStepper(int motorPin1, int motorPin2, int motorPin3, int motorPin4)
{
  this->motorPin1 = motorPin1;
  this->motorPin2 = motorPin2;
  this->motorPin3 = motorPin3;
  this->motorPin4 = motorPin4;

  pinMode(this->motorPin1, OUTPUT);
  pinMode(this->motorPin2, OUTPUT);
  pinMode(this->motorPin3, OUTPUT);
  pinMode(this->motorPin4, OUTPUT);

  this->direction = 1;
  this->lastStep = 0;
  this->lastStepTime = 0;
  this->steps = 0;
}


void CustomStepper::setDirection(int direction)
{
  this->direction = direction > 0 ? 1 : -1;
}


void CustomStepper::rotate(int stepsDelay)
{
  unsigned long now = millis();

  if (now - this->lastStepTime >= abs(stepsDelay)) {
    stepMotor();

    this->lastStepTime = now;
    this->lastStep++;

    if (this->lastStep > 3) {
      this->lastStep = 0;
      this->steps++;
    }
  }
}


void CustomStepper::rotateWithReverse(int forwardSteps, int reverseSteps, int stepsDelay)
{
  int stepsLimit = this->direction > 0 ? forwardSteps : reverseSteps;

  if (this->steps >= stepsLimit) {
    this->steps = 0;
    this->direction *= -1;
  }

  Serial.println(this->lastStep);

  rotate(stepsDelay);
}


void CustomStepper::stepMotor()
{
  int pinToMove1 = this->direction > 0 ? this->motorPin1 : this->motorPin4;
  int pinToMove2 = this->direction > 0 ? this->motorPin2 : this->motorPin3;
  int pinToMove3 = this->direction > 0 ? this->motorPin3 : this->motorPin2;
  int pinToMove4 = this->direction > 0 ? this->motorPin4 : this->motorPin1;

  switch (this->lastStep) {
    case 0:
      digitalWrite(pinToMove1, HIGH); 
      digitalWrite(pinToMove2, LOW); 
      digitalWrite(pinToMove3, LOW); 
      digitalWrite(pinToMove4, HIGH);
    break;
    case 1:
      digitalWrite(pinToMove1, HIGH); 
      digitalWrite(pinToMove2, HIGH); 
      digitalWrite(pinToMove3, LOW); 
      digitalWrite(pinToMove4, LOW);
    break;
    case 2:
      digitalWrite(pinToMove1, LOW); 
      digitalWrite(pinToMove2, HIGH); 
      digitalWrite(pinToMove3, HIGH); 
      digitalWrite(pinToMove4, LOW);
    break;
    case 3:
      digitalWrite(pinToMove1, LOW); 
      digitalWrite(pinToMove2, LOW); 
      digitalWrite(pinToMove3, HIGH); 
      digitalWrite(pinToMove4, HIGH);
    break;
  }
}