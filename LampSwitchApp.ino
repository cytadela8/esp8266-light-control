/*
  To upload through terminal you can use: curl -u admin:admin -F "image=@firmware.bin" esp8266-webupdate.local/firmware
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#include "config.h"
#include "index.h"

const char* host = "zarowka";
const char* update_path = "/update";
const char* update_username = UPDATE_USERNAME;
const char* update_password = UPDATE_PASSWORD;
const char* wifi_ssid = WIFI_SSID;
const char* wifi_password = WIFI_PSK;

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

void handleMainPage() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

void handleManifest() {
  String s = MANIFEST_json; //Read HTML contents
  server.send(200, "text/json", s); //Send web page
}

int lampState = HIGH;
int switchLastState = LOW;
int lastSwitchChange = 0;

void handleLamp() {
  String t_state = server.arg("lampState");
  Serial.println(t_state);
  if (t_state == "ON")
  {
    digitalWrite(LAMP_OUT, LOW); //LED ON
    lampState = LOW;
  }
  else if (t_state == "OFF")
  {
    digitalWrite(LAMP_OUT, HIGH); //LED OFF
    lampState = HIGH;
  }

  handleGetState();
}

void handleGetState() {
  String response = "{";
  
  if (lampState == LOW) {
    response += "\"lamp\": \"ON\"";
  } else {
    response += "\"lamp\": \"OFF\"";
  }

  if (switchLastState == LOW) {
    response += ", \"switch\": \"ON\"";
  } else {
    response += ", \"switch\": \"OFF\"";
  }

  response += ", \"lastSwitchChange\": ";
  response += lastSwitchChange; 
  
  response += "}";
  server.send(200, "text/json", response);
}

void handleSwitchToggled() {
  if (lampState == LOW) {
    digitalWrite(LAMP_OUT, HIGH);
    lampState = HIGH;
  } else {
    digitalWrite(LAMP_OUT, LOW);
    lampState = LOW;
  }
}

void setup(void) {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch... (2)");
  pinMode(LAMP_OUT, OUTPUT);
  digitalWrite(LAMP_OUT, HIGH);
  lampState = HIGH;
  pinMode(SWITCH_IN, INPUT_PULLUP);
  switchLastState = digitalRead(SWITCH_IN);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
    WiFi.begin(wifi_ssid, wifi_password);
    Serial.println("WiFi failed, retrying.");
  }

  MDNS.begin(host);

  httpUpdater.setup(&server, update_path, update_username, update_password);
  server.begin();

  server.on("/", handleMainPage);
  server.on("/manifest.json", handleManifest);
  server.on("/setLamp", handleLamp);
  server.on("/getState", handleGetState);

  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s%s in your browser and login with username '%s' and password '%s'\n", WiFi.localIP().toString().c_str(), update_path, update_username, update_password);
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  int newSwitchState = digitalRead(SWITCH_IN);
  if (switchLastState != newSwitchState && lastSwitchChange + 500 < millis()) {
    lastSwitchChange = millis();
    handleSwitchToggled();
    switchLastState = newSwitchState;
  }
}
