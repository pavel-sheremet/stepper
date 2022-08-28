#ifndef CustomStepper_h
#define CustomStepper_h

#include "Arduino.h"

class CustomStepper
{
  public:
    CustomStepper(int motorPin1, int motorPin2, int motorPin3, int motorPin4);

    void setDirection(int direction);
    void rotate(int stepsDelay);
    void rotateWithReverse(int forwardSteps, int reverseSteps, int stepsDelay);

  private:
    int direction;
    int motorPin1;
    int motorPin2;
    int motorPin3;
    int motorPin4;
    int lastStep;
    int steps;
    unsigned long lastStepTime;

    void stepMotor();
};

#endif