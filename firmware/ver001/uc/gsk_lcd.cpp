#include "gsk_all_loaded.h"



GSK_LCD::GSK_LCD() : lcd(0x27, LCD_COLS, LCD_ROWS) {
  setup();
}

void GSK_LCD::setup () {
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  resetDispaly();
  lcd.blink();
}

void GSK_LCD::resetDispaly() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void GSK_LCD::putTemplate () {
  lcd.setCursor(0,0);
  lcd.print("Set point:         C");
  lcd.setCursor(0,1);
  lcd.print("Temperature:       C");
  lcd.setCursor(0,2);
  lcd.print("Relay No: 1  2  3  4");
  lcd.setCursor(0,3);
  lcd.print("Position:           ");
  lcd.setCursor(18,0);
  lcd.print((char)223);
  lcd.setCursor(18,1);
  lcd.print((char)223);
}

void GSK_LCD::putValues (void* st) {
  GSK_STATE* state = (GSK_STATE*)st;
  lcd.setCursor(12,0);
  lcd.print(state->getSetPoint(),1);
  lcd.setCursor(12,1);
  lcd.print(state->getTemperature(),1);
  lcd.setCursor(9,3);
  lcd.print(state->getRelayState(0));
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
    lcd.cursor_on();
  } else {
    lcd.cursor_off();
  }
}