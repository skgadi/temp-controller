#include "gsk_all_loaded.h"

GSK_STATE::GSK_STATE() {
  setup();
}

void GSK_STATE::setup() {
  relays = new GSK_RELAYS();
  pwm = new GSK_PWM();
  sensor = new GSK_SENSOR();
  encoder = new GSK_ENCODER();
  pid = new GSK_PID();
  lcd = new GSK_LCD();
  editMode = false;
  cursorPosition = 0;
  pid->setY(sensor->readTemperature());
  float initialSetPoint = 15.0;
  pid->setR(initialSetPoint);
  encoder->setValue(initialSetPoint*10.0);
}

void GSK_STATE::loop() {
  float t = (millis()/1000.0);
  if ((t-lastLcdTemplate)>=UPDATE_LCD_TEMPLATE_EVERY_x_SEC) {
    lastLcdTemplate = t;
    lcd->putTemplate();
  }
  if (((t-lastLcdData)*1000.0)>=UPDATE_LCD_DATA_EVERY_x_M_SEC) {
    lastLcdData = t;
    lcd->putValues(this);
  }
  if (encoder->readNResetBtn()) {
    if (editMode) {
      cursorPosition++;
      if (cursorPosition>0 && cursorPosition<=4) {
        encoder->setBoundaries(0, 1);
        encoder->setValue(relays->getStateFor(cursorPosition-1));
        #ifdef ENABLE_DEBUG_PRINT
          DEBUG_PRINTLN("Boundaries: (0, 1)");
          DEBUG_PRINTLN("Value: " + String(relays->getStateFor(cursorPosition-1)));
        #endif
        } else {
        cursorPosition = 0;
        encoder->setBoundaries(0, 5000);
        encoder->setValue(round(pid->getR()*10.0));
        editMode = false;
        #ifdef ENABLE_DEBUG_PRINT
          DEBUG_PRINTLN("Boundaries: (0, 5000)");
          DEBUG_PRINTLN("Value: " + String(round(pid->getR()*10.0)));
        #endif
      }
    } else {
      editMode = true;
    }


  }
  if (editMode) {
    if (cursorPosition==0) {
      pid->setR(encoder->getValue()/10.0);
        #ifdef ENABLE_DEBUG_PRINT
          //DEBUG_PRINTLN("Updated set point to: " + String(encoder->getValue()/10.0));
        #endif
    } else {
      relays->setStateFor(cursorPosition-1, encoder->getValue());
    }
  }

  pid->setY(sensor->readTemperature());
  pid->loop();
  encoder->loop();
  pwm->setState(pid->getU());
  #ifdef ENABLE_DEBUG_PRINT
    //DEBUG_PRINTLN("pid->getU(): " + String(pid->getU()));
  #endif
}

void GSK_STATE::isr() {
  encoder->isr();
}

float GSK_STATE::getTemperature() {
  return sensor->readTemperature();
}

float GSK_STATE::getSetPoint() {
  return pid->getR();
}

bool GSK_STATE::getRelayState(int i) {
  return relays->getStateFor(i);
}

int GSK_STATE::getCursorPosition() {
  return cursorPosition;
}

bool GSK_STATE::getEditMode() {
  return editMode;
}