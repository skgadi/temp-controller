#include "gsk_lcd.h"



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

void GSK_LCD::showWelcome () {
  lcd.setCursor(3,1);
  lcd.print("WELCOME");
}