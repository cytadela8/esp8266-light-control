#ifndef LAMP_API_H
#define LAMP_API_H

#include <ESP8266WebServer.h>
#include "lamp_controller.h"

class LampAPI {
public:
  void setup(ESP8266WebServer *server, LampController *controller);

private:
  void handleLamp();

  void handleGetState();

  ESP8266WebServer *server;
  LampController *controller;
};

#endif
