#ifndef GSK_STATE_H
#define GSK_STATE_H

#include "gsk_global.h"
#include "gsk_lcd.h"
#include "gsk_relays.h"
#include "gsk_sensor.h"
#include "gsk_pwm.h"
#include "gsk_encoder.h"
#include "gsk_pid.h"
#include "gsk_serial.h"

#define UPDATE_LCD_TEMPLATE_EVERY_x_SEC (10*60)
#define UPDATE_LCD_DATA_EVERY_x_M_SEC 100
#define READ_TEMPERATURE_EVERY_x_M_SEC (300)


class GSK_STATE {
  bool editMode;
  int cursorPosition;
  float lastLcdTemplate = -UPDATE_LCD_TEMPLATE_EVERY_x_SEC;
  float lastLcdData = -UPDATE_LCD_DATA_EVERY_x_M_SEC/1000.0;
  float lastTemperatureRead = -READ_TEMPERATURE_EVERY_x_M_SEC/1000.0;

  void setup();
  GSK_SENSOR* sensor;
  GSK_PID* pid;
  GSK_ENCODER* encoder;
  GSK_RELAYS* relays;
  GSK_LCD* lcd;
  GSK_PWM* pwm;
  GSK_SERIAL* serial;
  public:
  void isr();
  GSK_STATE();
  void loop();

  float getComputedKp();
  float getComputedKi();
  float getComputedKd();
  void stopEditMode();
  void setRelayState(int, bool);
  bool getRelayState(int);
  float getTemperature();
  float getSetPoint();
  void setSetPoint(float);
  void setTemperature(float);
  void setKp(float);
  void setKi(float);
  void setKd(float);
  int getCursorPosition();
  bool getEditMode();
};



#endif