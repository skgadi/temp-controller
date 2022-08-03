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
  pid.SetAntiWindupMode(pid.iAwMode::iAwCondition);
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

float GSK_PID::getComputedKp() {
  return pid.GetKp();
}

float GSK_PID::getComputedKi() {
  return pid.GetKi();
}

float GSK_PID::getComputedKd() {
  return pid.GetKd();
}

void GSK_PID::readParameters() {
  Kp = getComputedKp();
  Ki = getComputedKi();
  Kd = getComputedKd();
}

void GSK_PID::setKp(float newKp) {
  readParameters();
  pid.SetTunings(newKp, Ki, Kd);
}

void GSK_PID::setKi(float newKi) {
  readParameters();
  pid.SetTunings(Kp, newKi, Kd);
}

void GSK_PID::setKd(float newKd) {
  readParameters();
  pid.SetTunings(Kp, Ki, newKd);
}

