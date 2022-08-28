#include "CustomStepper.h"

CustomStepper stepper(8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  stepper.rotateWithReverse(15, 8, 2);
}