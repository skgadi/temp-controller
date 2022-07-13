#include "gsk_encoder.h"

GSK_ENCODER::GSK_ENCODER() {
  setup();
}

void GSK_ENCODER::setup() {
  pinMode(PIN_ENC_SW, INPUT_PULLUP);
  rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  setBoundraies(0,4,true);
  rotaryEncoder.setBoundaries(0, 800, true);
  rotaryEncoder.setAcceleration(250);
  reset();
  readNResetBtn();

}

void GSK_ENCODER::readEncoderISRLocal() {
	rotaryEncoder.readEncoder_ISR();
}


void GSK_ENCODER::reset() {
  setValue(0);
}

void GSK_ENCODER::setValue (int val) {
  rotaryEncoder.setEncoderValue(val);
}

int GSK_ENCODER::getValue() {
  return rotaryEncoder.readEncoder();
}

void GSK_ENCODER::setBoundraies(int min, int max, bool cycle) {
  rotaryEncoder.setBoundaries(min, max, cycle);
}

void GSK_ENCODER::writeBtn(bool val) {
  btnState = val;
}

bool GSK_ENCODER::readBtn() {
  return btnState;
}

bool GSK_ENCODER::readNResetBtn() {
  bool tempState = btnState;
  btnState = false;
  return tempState;
}

void GSK_ENCODER::loop() {
  if (readPressed) {
    if (((millis() - lastPressed) > 100) && digitalRead(PIN_ENC_SW)) {
      readPressed = false;
      btnState = true;
    }
  } else {
    readPressed = !digitalRead(PIN_ENC_SW);
  }
}

