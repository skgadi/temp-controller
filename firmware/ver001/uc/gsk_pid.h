#ifndef GSK_PID_H
#define GSK_PID_H

#include "gsk_global.h"
#include "QuickPID.h"


class GSK_PID {
  QuickPID pid;
  float r, y, u;
  //Define the aggressive and conservative and POn Tuning Parameters
  float aggKp = 4, aggKi = 0.2, aggKd = 1;
  float consKp = 1, consKi = 0.05, consKd = 0.25;
  void setup();
  public:
  GSK_PID();
  void loop();
  void updateR(float);
  void updateY(float);
  float getU();
};

#endif