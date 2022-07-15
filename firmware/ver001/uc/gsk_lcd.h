#ifndef GSK_LCD_H
#define GSK_LCD_H

#include "gsk_global.h"
#include <LiquidCrystal_I2C.h>


class GSK_LCD {
  LiquidCrystal_I2C lcd;
  void setup();
  void resetDispaly();
  public:
  GSK_LCD();
  void putTemplate();
  void putValues(void*);
};

#endif