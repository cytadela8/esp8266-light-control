#ifndef LAMP_CONTROLLER_H
#define LAMP_CONTROLLER_H

#include <Arduino.h>

class LampController {
public:
  LampController(int switch_in, int lamp_out);

  void begin();

  void update();

  inline bool getState() const {
    return lampState == HIGH;
  }

  void setState(bool newState);

  inline bool getSwitchState() const {
    return switchLastState == HIGH;
  }

  inline int getSwitchLastChange() const {
    return lastSwitchChange;
  }

private:
  void handleSwitchToggled();

  int switch_in;
  int lamp_out;

  int lampState = HIGH;
  int switchLastState = LOW;
  int lastSwitchChange = 0;
};

#endif
