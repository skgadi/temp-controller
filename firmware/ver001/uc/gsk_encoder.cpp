#include "gsk_all_loaded.h"

GSK_ENCODER::GSK_ENCODER() {
  setup();
}

void GSK_ENCODER::setup() {
  pinMode(PIN_ENC_SW, INPUT_PULLUP);
  rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  setBoundaries(0, 5000, false);
  rotaryEncoder.setAcceleration(250);
  reset();
  readNResetBtn();
}

void GSK_ENCODER::isr() {
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

void GSK_ENCODER::setBoundaries(int min, int max, bool cycle) {
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
    if (((millis() - lastPressed) > 1000) && digitalRead(PIN_ENC_SW)) {
      lastPressed = millis();
      readPressed = false;
      btnState = true;
      #ifdef ENABLE_DEBUG_PRINT
      //DEBUG_PRINT("Value: ");
        DEBUG_PRINTLN("Button pressed");
      //DEBUG_PRINT("Digits: ");
      //DEBUG_PRINTLN(out);
      #endif

    }
  } else {
    readPressed = !digitalRead(PIN_ENC_SW);
  }
}

