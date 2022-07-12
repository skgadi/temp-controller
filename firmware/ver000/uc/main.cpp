#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

byte i =0;

void loop () {
  Serial.print("Hello: ");
  Serial.println(i++);
  delay(5000);
}