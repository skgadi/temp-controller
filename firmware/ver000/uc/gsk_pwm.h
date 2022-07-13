#ifndef GSK_PWM_H
#define GSK_PWM_H

#include "gsk_global.h"



class GSK_PWM {
  void setup();
  float state;
  int pwmResolution = 14;
  int maxDutyCycle = (int)(pow(2, pwmResolution) - 1);
  int pwmChannl = 0;
  int pwmFrequency = 1000;
  public:
  GSK_PWM();
  void switchOff();
  float getState();
  void setState(float);
  int getDutyCycle(float);
};

#endif