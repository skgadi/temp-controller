#include "gsk_all_loaded.h"


GSK_STATE *gsk_state;


void setup() {
  Serial.begin(115200);


  gsk_state = new GSK_STATE();

}

void loop () {
  gsk_state->loop();
}

void IRAM_ATTR readEncoderISR() {
  gsk_state->isr(); // call the isr function in the state class
}
