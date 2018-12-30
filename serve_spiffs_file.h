#ifndef LAMPSWITCHAPP_SERVE_SPIFFS_FILE_H
#define LAMPSWITCHAPP_SERVE_SPIFFS_FILE_H

#include <Arduino.h>

class ESP8266WebServer;

void serveSPIFFSFile(ESP8266WebServer &server, String path);

#endif //LAMPSWITCHAPP_SERVE_SPIFFS_FILE_H
