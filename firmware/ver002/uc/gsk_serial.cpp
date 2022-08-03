#include "gsk_serial.h"
#include "gsk_state.h"


GSK_SERIAL::GSK_SERIAL() {
  setup();
}

void GSK_SERIAL::setup() {
  Serial.begin(115200);
}


void GSK_SERIAL::loop(void *param) {
  GSK_STATE *state = (GSK_STATE *)param;
  while (Serial.available() > 0) {
    try {
      state->stopEditMode();
      String activity = Serial.readStringUntil(':');
      if (activity.equals("R")) {
        String measure = Serial.readStringUntil('\n');
        if (measure.equals("KP")) {
          Serial.println(state->getComputedKp());
        } else if (measure.equals("KI")) {
          Serial.println(state->getComputedKi());
        } else if (measure.equals("KD")) {
          Serial.println(state->getComputedKd());
        } else if (measure.equals("T")) {
          Serial.println(state->getTemperature());
        } else if (measure.equals("R")) {
          Serial.println(state->getSetPoint());
        } else if (measure.equals("S0")) {
          Serial.println(state->getRelayState(0));
        } else if (measure.equals("S1")) {
          Serial.println(state->getRelayState(1));
        } else if (measure.equals("S2")) {
          Serial.println(state->getRelayState(2));
        } else if (measure.equals("S3")) {
          Serial.println(state->getRelayState(3));
        } else {
          Serial.println(-1);
        }
      } else if (activity.equals("W")) {
        String measure = Serial.readStringUntil('=');
        float value = Serial.readStringUntil('\n').toFloat();
        if (measure.equals("KP")) {
          state->setKp(value);
        } else if (measure.equals("KI")) {
          state->setKi(value);
          Serial.println("0");
        } else if (measure.equals("KD")) {
          state->setKd(value);
          Serial.println("0");
        } else if (measure.equals("R")) {
          state->setSetPoint(value);
          Serial.println("0");
        } else if (measure.equals("S0")) {
          state->setRelayState(0, value);
          Serial.println("0");
        } else if (measure.equals("S1")) {
          state->setRelayState(1, value);
          Serial.println("0");
        } else if (measure.equals("S2")) {
          state->setRelayState(2, value);
          Serial.println("0");
        } else if (measure.equals("S3")) {
          state->setRelayState(3, value);
          Serial.println("0");
        } else {
          Serial.println("-1");
        }
      } else {
        Serial.println("-1");
      }
    } catch(...) {
      Serial.println("-2");
    }
  }
}
