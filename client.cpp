//---------------------------------------------------
//---------------------CLIENT------------------------
//---------------------------------------------------

#include <Arduino.h>
#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>

const char *ssid = "************";
const char *pass = "************";

WiFiClient client;
HTTPClient http;

String serverName = "http://ip:80/call";

void setup()
{
  //Setting input and output
  pinMode(15, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);

  Serial.println("");
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //Connecting to WIFI
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  String info = "Received IP : " + WiFi.localIP().toString() + ", Gateway : " + WiFi.gatewayIP().toString();
  Serial.println("");
  Serial.println(info);
}


void loop(){
  //digital read
  int val = digitalRead(15);
  if (val == 1)
  {
    digitalWrite(LED_BUILTIN, LOW);
    http.begin(client, serverName);
    Serial.println(http.GET());
    Serial.println(http.getString());
    http.end();
    delay(3000);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

