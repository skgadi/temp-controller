#include "gsk_all_loaded.h"

GSK_PID::GSK_PID() : pid(&y, &u, &r) {
  setup();
}

void GSK_PID::setup() {
  pid.SetSampleTimeUs(100000);
}

void GSK_PID::loop() {
  pid.Compute();
}

float GSK_PID::getU() {
  return u;
}

void GSK_PID::updateR(float r) {
  this->r = r;
}

void GSK_PID::updateY(float y) {
  this->y = y;
}

