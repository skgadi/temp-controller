#include "gsk_all_loaded.h"


GSK_STATE *gsk_state;


void setup() {
  Serial.begin(115200);


  gsk_state = new GSK_STATE();

  //pinMode(32, OUTPUT);
  //pinMode(33, OUTPUT);
  //pinMode(25, OUTPUT);
  //pinMode(26, OUTPUT);
  //digitalWrite(32, HIGH);
  //digitalWrite(33, HIGH);
  //digitalWrite(25, HIGH);
  //digitalWrite(26, HIGH);
}

void loop () {
  gsk_state->loop();
  delay(1);
}

void IRAM_ATTR readEncoderISR() {
  gsk_state->isr(); // call the isr function in the state class
}
