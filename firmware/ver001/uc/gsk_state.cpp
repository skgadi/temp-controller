#include "gsk_all_loaded.h"

GSK_STATE::GSK_STATE() {
  setup();
}

void GSK_STATE::setup() {
  relays = new GSK_RELAYS();
  pwm = new GSK_PWM();
  sensor = new GSK_SENSOR();
  encoder = new GSK_ENCODER();
  pid = new GSK_PID();
  lcd = new GSK_LCD();
}

void GSK_STATE::loop() {
  
}


void GSK_STATE::isr() {
  encoder->isr();
}