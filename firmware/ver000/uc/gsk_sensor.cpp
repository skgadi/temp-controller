#include "gsk_sensor.h"

GSK_SENSOR::GSK_SENSOR(): thermocouple(PIN_SPI_SCK, PIN_SPI_CS, PIN_SPI_MISO) {
  setup();
}

void GSK_SENSOR::setup () {
}

float GSK_SENSOR::readTemperature() {
  return thermocouple.readCelsius();
}