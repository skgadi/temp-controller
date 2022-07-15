#ifndef GSK_STATE_H
#define GSK_STATE_H

#include "gsk_global.h"
#include "gsk_lcd.h"
#include "gsk_relays.h"
#include "gsk_sensor.h"
#include "gsk_pwm.h"
#include "gsk_encoder.h"
#include "gsk_pid.h"


class GSK_STATE {
  bool editMode;
  float temperature;
  float setPoint;
  bool relayState[4];
  int cursorPosition;
  void setup();
  float r, y, u;
  GSK_SENSOR* sensor;
  GSK_PID* pid;
  GSK_ENCODER* encoder;
  GSK_RELAYS* relays;
  GSK_LCD* lcd;
  GSK_PWM* pwm;
  public:
  GSK_STATE();
  void loop();
  float* getR();
  float* getY();
  float* getU();
  bool getEditMode();
  float getTemperature();
  float getSetPoint();
  bool getRelayState(int);
  int getCursorPosition();
  void isr();
};



#endif