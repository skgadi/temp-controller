#include "gsk_all_loaded.h"

GSK_PID::GSK_PID() : pid(&y, &u, &r) {
  setup();
}

void GSK_PID::setup() {
  r=0;
  pid.SetSampleTimeUs(500000);
  pid.SetOutputLimits(0, 1);
  pid.SetTunings(Kp, Ki, Kd);
  pid.SetMode(pid.Control::automatic);
}

void GSK_PID::loop() {
  pid.Compute();
}

float GSK_PID::getU() {
  return u;
}

void GSK_PID::setR(float r) {
  this->r = r;
}

void GSK_PID::setY(float y) {
  this->y = y;
}

float GSK_PID::getR() {
  return r;
}

float GSK_PID::getY() {
  return y;
}

float GSK_PID::getComputerKp() {
  return pid.GetKp();
}

float GSK_PID::getComputerKi() {
  return pid.GetKi();
}

float GSK_PID::getComputerKd() {
  return pid.GetKd();
}