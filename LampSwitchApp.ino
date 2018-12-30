#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "config.h"
#include "lamp_controller.h"
#include "lamp_api.h"
#include "HTTP_update_server.h"
#include "flash_config_check.h"
#include "serve_spiffs_file.h"

const char *host = "zarowka";
const char *update_username = UPDATE_USERNAME;
const char *update_password = UPDATE_PASSWORD;
const char *wifi_ssid = WIFI_SSID;
const char *wifi_password = WIFI_PSK;

ESP8266WebServer server(80);

HTTPUpdateServer httpUpdater;
LampController lampController(SWITCH_IN, LAMP_OUT);
LampAPI lampAPI;

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  lampController.begin();

  SPIFFS.begin();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
    WiFi.begin(wifi_ssid, wifi_password);
    Serial.println("WiFi failed, retrying.");
  }

  MDNS.begin(host);

  httpUpdater.setup(&server, update_username, update_password);
  lampAPI.setup(&server, &lampController);

  server.on("/checkConfig", []() {
    server.send(200, "text/plain", flashChipConfigCheck());
  });

  server.onNotFound([]() {
    serveSPIFFSFile(server, server.uri());
  });

  server.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.printf(
          "HTTPUpdateServer ready! Open http://%s/update in your browser and login with username '%s' and password '%s'\n",
          WiFi.localIP().toString().c_str(), update_username, update_password);
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  lampController.update();
}
