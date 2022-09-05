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
  nlohmann::json outObj;

  while (Serial.available() > 0) {
    try {
      u_int64_t start = millis();
      std::vector<std::uint8_t> cborArray = {};
      while (Serial.available()) {
        cborArray.push_back(Serial.read());
      }
      nlohmann::json inObj = nlohmann::json::from_cbor(cborArray);

      //write uC
      if (inObj.contains("W")) {
        if (inObj["W"].contains("R")){
          state->setSetPoint(inObj["W"]["R"]);
        }
        if (inObj["W"].contains("S0")){
          state->setRelayState(0,inObj["W"]["S0"]);
        }
        if (inObj["W"].contains("S1")){
          state->setRelayState(1,inObj["W"]["S1"]);
        }
        if (inObj["W"].contains("S2")){
          state->setRelayState(2,inObj["W"]["S2"]);
        }
        if (inObj["W"].contains("S3")){
          state->setRelayState(3,inObj["W"]["S3"]);
        }
      }




      //Read uC values and send
      outObj["R"] = inObj["R"];
      if (outObj["R"].contains("R")){
        outObj["R"]["R"] = state->getSetPoint();
      }
      if (outObj["R"].contains("T")){
        outObj["R"]["T"] = state->getTemperature();
      }
      if (outObj["R"].contains("S0")){
        outObj["R"]["S0"] = state->getRelayState(0);
      }
      if (outObj["R"].contains("S1")){
        outObj["R"]["S1"] = state->getRelayState(1);
      }
      if (outObj["R"].contains("S2")){
        outObj["R"]["S2"] = state->getRelayState(2);
      }
      if (outObj["R"].contains("S3")){
        outObj["R"]["S3"] = state->getRelayState(3);
      }


      /*if(key == test) {
        outObj["R"][i]["v"] = state->getSetPoint();
      }*/
      /*for(int i=0; i<inObj["R"].size(); i++) {
      }*/

      /*state->stopEditMode();
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
      }*/
    } catch(...) {
      outObj["error"] = true;
    }
    std::vector <std::uint8_t> outBinArray = nlohmann::json::to_cbor(outObj);
    Serial.write(outBinArray.data(), outBinArray.size());
  }
}
