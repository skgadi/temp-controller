#ifndef GSK_ENCODER_H
#define GSK_ENCODER_H

#include "gsk_global.h"
#include "AiEsp32RotaryEncoder.h"



#define ROTARY_ENCODER_A_PIN PIN_ENC_CLK
#define ROTARY_ENCODER_B_PIN PIN_ENC_DT
#define ROTARY_ENCODER_BUTTON_PIN PIN_ENC_SW
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4



class GSK_ENCODER {
  void setup();
  AiEsp32RotaryEncoder rotaryEncoder;
  unsigned long lastPressed = 0;
  bool btnState;
  bool readPressed;
  public:
  GSK_ENCODER();
  void reset();
  void setValue(int);
  int getValue();
  void setBoundaries(int, int, bool = false);
  void loop();
  bool readNResetBtn();
  bool readBtn();
  void writeBtn(bool);
  void isr();
};

#endif