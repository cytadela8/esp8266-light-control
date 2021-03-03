#include "lamp_api.h"

#include <ESP8266WebServer.h>

void LampAPI::setup(ESP8266WebServer *server, LampController *controller) {
  this->server = server;
  this->controller = controller;
  server->on("/setLamp", [&]() {
    handleLamp();
  });
  server->on("/setAntiNoise", [&]() {
    handleAntiNoise();
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

void LampAPI::handleAntiNoise() {
  String q = server->arg("q");
  if (q == "ON")
    controller->setAntiNoise(true);
  else if (q == "OFF")
    controller->setAntiNoise(false);
  else if (q == "PULSE") {
    String len = server->arg("len");
    controller->setAntiNoisePulseLen(atoi(len.c_str()));
  }
  
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

  if (controller->getAntiNoise()) {
    response += ", \"antiNoise\": \"ON\"";
  } else {
    response += ", \"antiNoise\": \"OFF\"";
  }

  response += ", \"antiNoisePulseLen\":";
  response += controller->getAntiNoisePulseLen();

  response += ", \"switchLastChange\": ";
  response += controller->getSwitchLastChange();
  
  response += ", \"systemTime\": ";
  response += millis();

  response += "}";
  server->send(200, "application/json", response);
}
