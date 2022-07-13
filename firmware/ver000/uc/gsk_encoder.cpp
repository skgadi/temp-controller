#include "gsk_encoder.h"

GSK_ENCODER::GSK_ENCODER() {
  setup();
}

void GSK_ENCODER::setup() {
  rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  setBoundraies(0,4,true);
  rotaryEncoder.setBoundaries(0, 800, true);
  rotaryEncoder.setAcceleration(250);
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
  return rotaryEncoder.getAcceleration();
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
    if (((millis() - lastPressed) > 100) && !rotaryEncoder.isEncoderButtonClicked()) {
      readPressed = false;
      btnState = true;
    }
  } else {
    readPressed = rotaryEncoder.isEncoderButtonClicked();
  }
}

void rotary_onButtonClick() {
	static unsigned long lastTimePressed = 0;
	//ignore multiple press in that time milliseconds
	if (millis() - lastTimePressed < 500) {
		return;
	}
	lastTimePressed = millis();
	Serial.print("button pressed ");
	Serial.print(millis());
	Serial.println(" milliseconds after restart");
}