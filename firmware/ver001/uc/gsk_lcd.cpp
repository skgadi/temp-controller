#include "gsk_all_loaded.h"



GSK_LCD::GSK_LCD() : lcd(0x27, LCD_COLS, LCD_ROWS) {
  setup();
}

void GSK_LCD::setup () {
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  resetDispaly();
}

void GSK_LCD::resetDispaly() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  prevSetPoint = 0;
  prevTemperature = 0;
}

void GSK_LCD::putTemplate () {
  resetDispaly();
  lcd.setCursor(0,0);
  lcd.print("Set point:          ");
  lcd.setCursor(0,1);
  lcd.print("Temperature:        ");
  lcd.setCursor(0,2);
  lcd.print("Relay No: 1  2  3  4");
  lcd.setCursor(0,3);
  lcd.print("Position:           ");
}

void GSK_LCD::putValues (void* st) {
  if (st == NULL) return;
  GSK_STATE* state = (GSK_STATE*)st;
  if (state->getSetPoint() != prevSetPoint) {
    lcd.setCursor(10,0);
    lcd.print("       ");
    lcd.setCursor(getOffsetPosition(state->getSetPoint()),0);
    lcd.print(String(state->getSetPoint(),1) + String((char)223) + "C");
    prevSetPoint = state->getSetPoint();
  }
  if (state->getTemperature() != prevTemperature) {
    lcd.setCursor(12,1);
    lcd.print("       ");
    lcd.setCursor(getOffsetPosition(state->getTemperature()),1);
    lcd.print(String(state->getTemperature(),1) + String((char)223) + "C");
    prevTemperature = state->getTemperature();
  }
  //lcd.print(state->getTemperature(),1);
  lcd.setCursor(10,3);
  lcd.print(state->getRelayState(0));
  lcd.setCursor(13,3);
  lcd.print(state->getRelayState(1));
  lcd.setCursor(16,3);
  lcd.print(state->getRelayState(2));
  lcd.setCursor(19,3);
  lcd.print(state->getRelayState(3));
  switch (state->getCursorPosition()) {
  case 0:
    lcd.setCursor(17,0);
    break;
  case 1:
    lcd.setCursor(10,3);
    break;
  case 2:
    lcd.setCursor(13,3);
    break;
  case 3:
    lcd.setCursor(16,3);
    break;
  case 4:
    lcd.setCursor(19,3);
    break;
  default:
    lcd.setCursor(0,0);
    break;
  }
  if (state->getEditMode()) {
    //lcd.cursor_on();
    //lcd.blink_on();
    lcd.blink();
  } else {
    lcd.noBlink();
    //lcd.blink_off();
    //lcd.cursor_off();
  }
}

int GSK_LCD::getOffsetPosition (float value) {
  int out =15;
  if (value>0) {
    out -= (int)(log10(value));
  }
  #ifdef ENABLE_DEBUG_PRINT
    //DEBUG_PRINTLN(value);
    //DEBUG_PRINT("Value: ");
    //DEBUG_PRINT("Digits: ");
    //DEBUG_PRINTLN(out);
  #endif
  return out;
}