#include "lamp_api.h"

#include <ESP8266WebServer.h>

void LampAPI::setup(ESP8266WebServer *server, LampController *controller) {
  this->server = server;
  this->controller = controller;
  server->on("/setLamp", [&]() {
    handleLamp();
  });
  server->on("/getState", [&]() {
    handleGetState();
  });
}

void LampAPI::handleLamp() {
  String t_state = server->arg("lampState");
  Serial.println(t_state);
  if (t_state == "ON")
    controller->setState(true);
  else if (t_state == "OFF")
    controller->setState(false);
  else if (t_state == "TOGGLE")
    controller->toggleLamp();

  handleGetState();
}

void LampAPI::handleGetState() {
  String response = "{";

  if (controller->getState()) {
    response += "\"lamp\": \"ON\"";
  } else {
    response += "\"lamp\": \"OFF\"";
  }

  if (controller->getSwitchState()) {
    response += ", \"switch\": \"ON\"";
  } else {
    response += ", \"switch\": \"OFF\"";
  }

  response += ", \"switchLastChange\": ";
  response += controller->getSwitchLastChange();
  
  response += ", \"systemTime\": ";
  response += millis();

  response += "}";
  server->send(200, "application/json", response);
}
