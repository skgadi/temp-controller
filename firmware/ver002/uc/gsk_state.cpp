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
  serial = new GSK_SERIAL();
  editMode = false;
  //cursorPosition = 0;
  pid->setY(sensor->measureNReadTemperature());
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
        } else {
        editMode = false;
      }
    } else {
      cursorPosition = 0;
      encoder->setBoundaries(0, 5000);
      encoder->setValue(round(pid->getR()*10.0));
      editMode = true;
    }


  }
  if (editMode) {
    if (cursorPosition==0) {
      pid->setR(encoder->getValue()/10.0);
    } else {
      relays->setStateFor(cursorPosition-1, encoder->getValue());
    }
  }

  if ((t-lastTemperatureRead)*1000.0>=READ_TEMPERATURE_EVERY_x_M_SEC) {
    lastTemperatureRead = t;
    pid->setY(sensor->measureNReadTemperature());
  }
  pid->loop();
  encoder->loop();
  pwm->setState(pid->getU());

  serial->loop(this);
}

void GSK_STATE::isr() {
  encoder->isr();
}


float GSK_STATE::getComputedKp() {
  return pid->getComputedKd();
}

float GSK_STATE::getComputedKi() {
  return pid->getComputedKi();
}

float GSK_STATE::getComputedKd() {
  return pid->getComputedKd();
}

void GSK_STATE::stopEditMode() {
  editMode = false;
}

void GSK_STATE::setRelayState(int relay, bool state) {
  relays->setStateFor(relay, state);
}

float GSK_STATE::getTemperature() {
  return pid->getY();
}

float GSK_STATE::getSetPoint() {
  return pid->getR();
}

void GSK_STATE::setSetPoint(float setPoint) {
  pid->setR(setPoint);
}

void GSK_STATE::setTemperature(float temperature) {
  pid->setY(temperature);
}

void GSK_STATE::setKp(float newKp) {
  pid->setKp(newKp);
}

void GSK_STATE::setKi(float newKi) {
  pid->setKi(newKi);
}

void GSK_STATE::setKd(float newKd) {
  pid->setKd(newKd);
}

int GSK_STATE::getCursorPosition() {
  return cursorPosition;
}

bool GSK_STATE::getEditMode() {
  return editMode;
}

bool GSK_STATE::getRelayState(int relay) {
  return relays->getStateFor(relay);
}