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
    handleSwitchToggled();
    switchLastState = newSwitchState;
  }
}


void LampController::setState(bool newState) {
  if (newState) {
    digitalWrite(lamp_out, HIGH); //relay OFF
    lampState = HIGH;
  } else {
    digitalWrite(lamp_out, LOW); //relay ON
    lampState = LOW;
  }
}

void LampController::handleSwitchToggled() {
  setState(!getState());
}
