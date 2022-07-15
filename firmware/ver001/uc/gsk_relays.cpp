#include "gsk_all_loaded.h"

GSK_RELAYS::GSK_RELAYS() {
  setup();
}

void GSK_RELAYS::setup () {
  pins[0] = PIN_RELAY_0;
  pins[1] = PIN_RELAY_1;
  pins[2] = PIN_RELAY_2;
  pins[3] = PIN_RELAY_3;

  for (int i=0 ; i<NO_OF_RELAYS; i++) {
    pinMode(pins[i], OUTPUT);
  }
  resetAllRelays();
}

void GSK_RELAYS::setStateFor(int relayNo, bool val) {
  digitalWrite(pins[relayNo], val);
  states[relayNo] = val;
}

void GSK_RELAYS::setAllRelays (bool val) {
  for (size_t i = 0; i < NO_OF_RELAYS; i++) {
    setStateFor(i, val);
  }
}

bool GSK_RELAYS::getStateFor (int relayNo) {
  return states[relayNo];
}

void GSK_RELAYS::resetAllRelays() {
  setAllRelays(0);
}