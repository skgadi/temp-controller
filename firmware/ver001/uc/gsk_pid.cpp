#include "gsk_pid.h"

GSK_PID::GSK_PID() : pid(&y, &u, &r) {
  setup();
}

void GSK_PID::setup() {
  pid.SetSampleTimeUs(100000);
}


void GSK_PID::loop() {
  pid.Compute();
}