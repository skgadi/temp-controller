#ifndef GSK_SENSOR_H
#define GSK_SENSOR_H

#include "gsk_global.h"
#include "max6675.h"

class GSK_SENSOR {
  void setup();
  MAX6675 thermocouple;
  float tempInCelsius;
  public:
  GSK_SENSOR();
  void measureTemperature();
  float measureNReadTemperature();
  float getTempInCelsius();
};



#endif