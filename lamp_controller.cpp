#include <Arduino.h>

#include "lamp_controller.h"

LampController::LampController(int switch_in, int lamp_out) :
        switch_in(switch_in), lamp_out(lamp_out) {}

void LampController::begin() {
  pinMode(lamp_out, OUTPUT);
  digitalWrite(lamp_out, HIGH);
  lampState = HIGH;
  pinMode(switch_in, INPUT_PULLUP);
  switchLastState = digitalRead(switch_in);
}

void LampController::update() {
  int newSwitchState = digitalRead(switch_in);
  if (switchLastState != newSwitchState && lastSwitchChange + 500 < millis()) {
    lastSwitchChange = millis();
    toggleLamp();
    switchLastState = newSwitchState;
  }
  if (lampState == HIGH && antiNoise && lastPulse + 4000 < millis()) {
    digitalWrite(lamp_out, LOW);
    delay(pulseLen);
    digitalWrite(lamp_out, HIGH);
    lastPulse = millis();
  }
}

void LampController::setState(bool newState) {
  if (newState) {
    digitalWrite(lamp_out, HIGH);  // relay OFF
    lampState = HIGH;
  } else {
    digitalWrite(lamp_out, LOW);  // relay ON
    lampState = LOW;
  }
}

void LampController::toggleLamp() {
  setState(!getState());
}

void LampController::setAntiNoise(bool newState) {
  antiNoise = newState;
}

void LampController::setAntiNoisePulseLen(int pulseLen) {
  this->pulseLen = pulseLen;
}
