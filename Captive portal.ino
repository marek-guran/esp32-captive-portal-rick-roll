#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <WiFi.h>

DNSServer dnsServer;
AsyncWebServer server(80);

String user_name;
String proficiency;
bool name_received = false;
bool proficiency_received = false;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8" />
  <title>Prihlásenie sa do siete</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  
</head>
<body>
  <div>
      <p>
<br>⠀⠀⠀⠀⠀⠀⠀⢀⣶⣿⣿⣿⣿⣿⣄
<br>⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⠿⠟⠛⠻⣿⠆
<br>⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣆⣀⣀⠀⣿⠂
<br>⠀⠀⠀⠀⠀⠀⢸⠻⣿⣿⣿⠅⠛⠋⠈
<br>⠀⠀⠀⠀⠀⠀⠘⢼⣿⣿⣿⣃⠠
<br>⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣟⡿⠃
<br>⠀⠀⠀⠀⠀⠀⠀⠀⣛⣛⣫⡄⠀⢸⣦⣀
<br>⠀⠀⢀⣠⣴⣾⡆⠸⣿⣿⣿⡷⠂⠨⣿⣿⣿⣿⣶⣦⣤⣀
<br>⣤⣾⣿⣿⣿⣿⡇⢀⣿⡿⠋⠁⢀⡶⠪⣉⢸⣿⣿⣿⣿⣿⣇
<br>⢀⣿⣿⣿⣿⣿⣿⣿⣿⡏⢸⣿⣷⣿⣿⣷⣦⡙⣿⣿⣿⣿⣿⡏
<br>⠈⣿⣿⣿⣿⣿⣿⣿⣿⣇⢸⣿⣿⣿⣿⣿⣷⣦⣿⣿⣿⣿⣿⡇
<br>⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
<br>⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄
<br>⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
<br>⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿
<br>⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃
<br>⢹⣿⣵⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡁
      </p>  

      <p><center>
      We’re no strangers to love,
      <br>You know the rules and so do I.
      <br>A full commitment’s what I’m thinking of,
      <br>You wouldnt get this from any other guy.

      <br>I just wanna tell you how I’m feeling,
      <br>Gotta make you understand…

      <br>Never gonna give you up,
      <br>Never gonna let you down,
      <br>Never gonna run around and desert you.
      <br>Never gonna make you cry,
      <br>Never gonna say goodbye,
      <br>Never gonna tell a lie and hurt you.

      <br>We’ve known each other for so long
      <br>Your heart’s been aching
      <br>But you’re too shy to say it.
      <br>Inside we both know what’s been going on,
      <br>We know the game and we’re gonna play it.

      <br>Annnnnd if you ask me how I’m feeling,
      <br>Don’t tell me you’re too blind to see…

      <br>Never gonna give you up,
      <br>Never gonna let you down,
      <br>Never gonna run around and desert you.
      <br>Never gonna make you cry,
      <br>Never gonna say goodbye,
      <br>Never gonna tell a lie and hurt you.

      <br>Never gonna give you up,
      <br>Never gonna let you down,
      <br>Never gonna run around and desert you.
      <br>Never gonna make you cry,
      <br>Never gonna say goodbye,
      <br>Never gonna tell a lie and hurt you.

      <br>Give you up. give you up.
      <br>Give you up, give you up.
      <br>Never gonna give
      <br>Never gonna give, give you up.
      <br>Never gonna give
      <br>Never gonna give, give you up.

      <br>We’ve known each other for so long
      <br>Your heart’s been aching
      <br>But you’re too shy to say it.
      <br>Inside we both know what’s been going on,
      <br>We know the game and we’re gonna play it.

      <br>I just wanna tell you how I’m feeling,
      <br>Gotta make you understand…

      <br>Never gonna give you up,
      <br>Never gonna let you down,
      <br>Never gonna run around and desert you.
      <br>Never gonna make you cry,
      <br>Never gonna say goodbye,
      <br>Never gonna tell a lie and hurt you.

      <br>Never gonna give you up, 
      <br>Never gonna let you down,
      <br>Never gonna run around and desert you.
      <br>Never gonna make you cry,
      <br>Never gonna say goodbye,
      <br>Never gonna tell a lie and hurt you.

      <br>Never gonna give you up,
      <br>Never gonna let you down,
      <br>Never gonna run around and desert you.
      <br>Never gonna make you cry,
      <br>Never gonna say goodbye,
      <br>Never gonna tell a lie and hurt you.
      </center></p>
  </div>
</body>
</html></html>)rawliteral";

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request) {
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  }
};

void setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
    Serial.println("Client Connected");
  });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;

    if (request->hasParam("name")) {
      inputMessage = request->getParam("name")->value();
      inputParam = "name";
      user_name = inputMessage;
      Serial.println(inputMessage);
      name_received = true;
    }

    if (request->hasParam("proficiency")) {
      inputMessage = request->getParam("proficiency")->value();
      inputParam = "proficiency";
      proficiency = inputMessage;
      Serial.println(inputMessage);
      proficiency_received = true;
    }
    request->send(200, "text/html", "The values entered by you have been successfully sent to the device <br><a href=\"/\">Return to Home Page</a>");
  });
}


void setup() {
  //your other setup stuff...
  Serial.begin(115200);
  Serial.println();
  Serial.println("Setting up AP Mode");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP32 Free Wi-Fi");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Setting up Async WebServer");
  setupServer();
  Serial.println("Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);  //only when requested from AP
  //more handlers...
  server.begin();
  Serial.println("All Done!");
}

void loop() {
  dnsServer.processNextRequest();
}