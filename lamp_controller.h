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
    return switchLastState == LOW;
  }

  inline unsigned int getSwitchLastChange() const {
    return lastSwitchChange;
  }

  void toggleLamp();

private:

  int switch_in;
  int lamp_out;

  int lampState = HIGH;
  int switchLastState = LOW;
  unsigned int lastSwitchChange = 0;
};

#endif
