#include "gsk_all_loaded.h"

GSK_PWM::GSK_PWM() {
  setup();
}

void GSK_PWM::setup() {
  ledcSetup(pwmChannl, pwmFrequency, pwmResolution);
  ledcAttachPin(PIN_PWM, pwmChannl);
  switchOff();
}

void GSK_PWM::setState (float newState) {
  if (newState>=0 && newState<=1) {
    state = newState;
    ledcWrite(pwmChannl, getDutyCycle(newState));
  }
}

int GSK_PWM::getDutyCycle(float newState) {
  return ((maxDutyCycle)*(newState));
}

float GSK_PWM::getState() {
  return state;
}

void GSK_PWM::switchOff() {
  setState(0);
}