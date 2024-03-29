#ifndef GSK_PID_H
#define GSK_PID_H

#include "gsk_global.h"
#include "QuickPID.h"


class GSK_PID {
  QuickPID pid;
  float r, y, u;
  float Kp = 0.02, Ki = 0.05, Kd = 0.01;
  void setup();
  void readParameters();
  public:
  GSK_PID();
  void loop();
  void setR(float);
  void setY(float);
  float getU();
  float getR();
  float getY();
  float getComputedKp();
  float getComputedKi();
  float getComputedKd();
  void setKp(float);
  void setKi(float);
  void setKd(float);
};

#endif