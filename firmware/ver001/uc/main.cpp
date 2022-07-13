#include "gsk_global.h"
#include "gsk_lcd.h"
#include "gsk_relays.h"
#include "gsk_sensor.h"
#include "gsk_pwm.h"
#include "gsk_encoder.h"
#include "gsk_pid.h"



GSK_LCD *gsk_display;
GSK_RELAYS *gsk_valves;
GSK_SENSOR *gsk_sensor;
GSK_PWM *gsk_pwm;
GSK_ENCODER *gsk_encoder;


void setup() {
  Serial.begin(115200);


  gsk_display = new GSK_LCD();
  gsk_valves = new GSK_RELAYS();
  gsk_sensor = new GSK_SENSOR();
  gsk_pwm = new GSK_PWM();
  gsk_encoder = new GSK_ENCODER();


  gsk_display->showWelcome();
}

byte i =0;

void loop () {

  if (Serial.available()>0) {
    float rec = Serial.parseFloat();
    if (rec>=0 && rec<=1) {
      /*for (int i=0; i<100; i++) {
        gsk_pwm->setState(i/99.0);
        delay(10);
      }
      for (int i=0; i<100; i++) {
        gsk_pwm->setState((99.0-i)/99.0);
        delay(10);
      }*/
      Serial.println("");
      //Serial.println("PWM cycled");
      gsk_pwm->setState(rec);
      Serial.print("PWM dutycycle: ");
      Serial.println(gsk_pwm->getDutyCycle(rec));
      Serial.print("PWM set to: ");
      Serial.println(gsk_pwm->getState());
    } else {
      gsk_valves->resetAllRelays();
      gsk_valves->setStateFor(i%4, true);

      Serial.print("Hello: ");
      Serial.println(i++);
      Serial.print("Temperature in degree C: ");
      Serial.println(gsk_sensor->readTemperature());

      Serial.print("Button action: ");
      Serial.println(gsk_encoder->readNResetBtn());
      Serial.print("Encoder value: ");
      Serial.println(gsk_encoder->getValue());
    }
  }
  gsk_encoder->loop();
}

void IRAM_ATTR readEncoderISR() {
  gsk_encoder->readEncoderISRLocal();
}
