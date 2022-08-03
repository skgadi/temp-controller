#include "gsk_all_loaded.h"

GSK_SENSOR::GSK_SENSOR(): thermocouple(PIN_SPI_SCK, PIN_SPI_CS, PIN_SPI_MISO) {
  setup();
}

void GSK_SENSOR::setup () {
}

float GSK_SENSOR::getTempInCelsius() {
  return tempInCelsius;
}

void GSK_SENSOR::measureTemperature() {
  tempInCelsius = thermocouple.readCelsius();
}

float GSK_SENSOR::measureNReadTemperature() {
  measureTemperature();
  return getTempInCelsius();
}




