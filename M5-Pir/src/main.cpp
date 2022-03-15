#include <Arduino.h>
#include "M5Atom.h"

#define PIR_PIN 25

uint8_t ledBuf[3];

int state;


void ledState(int s)
{
  if (s == LOW) M5.dis.fillpix({255, 0, 0});
  else M5.dis.fillpix({0, 255, 0});
}

void setup() 
{
  M5.begin(true, false, true); 
  delay(100);
  pinMode(PIR_PIN, INPUT);

  Serial.println("pir READY");
  
  state = LOW;
  ledState(state);
  Serial.println("pir OFF");
}

void loop() 
{
  M5.update();
  
  // BTN forced trigger
  if (M5.Btn.wasPressed()) {
    Serial.println("pir ON");
    state = HIGH;
    ledState(state);
    delay(1000);
  }

  // PIR trigger
  int s = digitalRead(PIR_PIN);
  if (s != state) {
    if (s == LOW) Serial.println("pir OFF");
    else          Serial.println("pir ON");
    state = s;
    ledState(state);
  }
  else delay(1);

}