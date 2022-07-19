#include "gsk_all_loaded.h"

GSK_SENSOR::GSK_SENSOR(): thermocouple(PIN_SPI_SCK, PIN_SPI_CS, PIN_SPI_MISO) {
  setup();
}

void GSK_SENSOR::setup () {
}

float GSK_SENSOR::readTemperature() {
    #ifdef ENABLE_DEBUG_PRINT
    DEBUG_PRINTLN("thermocouple.readCelsius(): " + String(thermocouple.readCelsius()));
  #endif

  return thermocouple.readCelsius();
}