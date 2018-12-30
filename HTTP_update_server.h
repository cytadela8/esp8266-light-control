#ifndef HTTP_UPDATE_SERVER_H
#define HTTP_UPDATE_SERVER_H

class ESP8266WebServer;

class HTTPUpdateServer {
public:
  HTTPUpdateServer(bool serial_debug = false);

  void setup(ESP8266WebServer *server) {
    setup(server, emptyString, emptyString);
  }

  void setup(ESP8266WebServer *server, const String &username, const String &password);

  void updateCredentials(const String &username, const String &password) {
    _username = username;
    _password = password;
  }

protected:
  void _setUpdaterError();

private:
  void handlePOSTData(int target);

  void handlePOSTFinish(int target);

  bool _serial_output;
  ESP8266WebServer *_server;
  String _username;
  String _password;
  bool _authenticated;
  String _updaterError;
};


#endif
