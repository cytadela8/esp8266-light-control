#ifndef LAMP_API_H
#define LAMP_API_H

#include "lamp_controller.h"

class ESP8266WebServer;

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
