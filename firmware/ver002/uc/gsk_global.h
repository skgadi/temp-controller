#ifndef GSK_GLOBAL_H
#define GSK_GLOBAL_H

#include <Arduino.h>
#include "json.hpp"

//#define ENABLE_DEBUG_PRINT
//
//#ifdef ENABLE_DEBUG_PRINT
//  #define DEBUG_PRINT(x) Serial.print(x)
//  #define DEBUG_PRINTLN(x) Serial.println(x)
//#else
//  #define DEBUG_PRINT(x)
//  #define DEBUG_PRINTLN(x)
//#endif


#define LCD_COLS 20
#define LCD_ROWS 4

#define NO_OF_RELAYS 4


#define PIN_I2C_SDA 21
#define PIN_I2C_SCL 22

#define PIN_RELAY_0 32
#define PIN_RELAY_1 33
#define PIN_RELAY_2 25
#define PIN_RELAY_3 26


#define PIN_SPI_MISO 19
#define PIN_SPI_CS 5
#define PIN_SPI_SCK 18

#define PIN_PWM 13

#define PIN_ENC_SW 27
#define PIN_ENC_CLK 14
#define PIN_ENC_DT 23




void IRAM_ATTR readEncoderISR();

#endif