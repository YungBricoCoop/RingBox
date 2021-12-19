//---------------------------------------------------
//---------------------SERVER------------------------
//---------------------------------------------------

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

const char *ssid = "***********";
const char *pass = "***********";

const int BUZZER1 = 16;
const int BUZZER2 = 5;

WiFiClient client;
ESP8266WebServer server(80);


void handleCall();

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //Setting input and output
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

  //Webserver configuration
  Serial.println("Starting web server");
  server.on("/call", handleCall);
  server.begin();
}


void handleCall() {
  server.send(200, "text/html", "📞Call Received📞"); 
  Serial.println("📞Call Received📞");
  
  //BIPS
  for (int i = 0; i < 10; i++) {
    digitalWrite(BUZZER1, HIGH);
    delay(50);
    digitalWrite(BUZZER2, HIGH);
    delay(200);
    digitalWrite(BUZZER1, LOW);
    delay(50);
    digitalWrite(BUZZER2, LOW);
    delay(200);
  }
}

void loop(){
   server.handleClient();
}

