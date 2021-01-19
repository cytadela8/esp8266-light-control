#ifndef LAMPSWITCHAPP_SERVE_SPIFFS_FILE_H
#define LAMPSWITCHAPP_SERVE_SPIFFS_FILE_H

#include <Arduino.h>
#include <ESP8266WebServer.h>

void serveSPIFFSFile(ESP8266WebServer &server, String path);

#endif //LAMPSWITCHAPP_SERVE_SPIFFS_FILE_H
