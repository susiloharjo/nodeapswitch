
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "iotmkn";
const char *password = "user.100";
int stateLED = LOW;

ESP8266WebServer server(80);

void handleRoot() {
    response();
}

void handleLedOn() {
  stateLED = LOW;
  digitalWrite(D4, stateLED);
  response();
}

void handleLedOff() {
  stateLED = HIGH;
  digitalWrite(D4, stateLED);
  response();
}

const String HtmlHtml = "<html><head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>IOT - SMART SWITCH</h1><br/>\n";
const String HtmlLedStateLow = "<big>LED is now <b>ON</b></big><br/>\n";
const String HtmlLedStateHigh = "<big>LED is now <b>OFF</b></big><br/>\n";
const String HtmlButtons =
    "<a href=\"LEDOn\"><button style=\"display: block; width: 100%; background-color: blue; color : white ;\">ON</button></a><br/>"
    "<a href=\"LEDOff\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>";

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  if(stateLED == LOW){
    htmlRes += HtmlLedStateLow;
  }else{
    htmlRes += HtmlLedStateHigh;
  }

  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {
    delay(1000);
    Serial.begin(9600);
    Serial.println();

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/LEDOn", handleLedOn);
    server.on("/LEDOff", handleLedOff);
    server.begin();
    Serial.println("HTTP server beginned");
    pinMode(D4, OUTPUT);
    digitalWrite(D4, stateLED);
}

void loop() {
    server.handleClient();
}
