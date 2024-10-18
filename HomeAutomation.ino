#define BLYNK_PRINT Serial            
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>  // For OTA with ESP8266
#include <WiFiUdp.h>  // For OTA
#include <ArduinoOTA.h>  // For OTA


BlynkTimer timer;

void checkPhysicalButton();

int relay1State = LOW;
int pushButton1State = HIGH;


#define AUTH "---------------------------"  // You should get Auth Token in the Blynk App.  
#define WIFI_SSID "----------"                   //Enter Wifi Name
#define WIFI_PASS "----------"                   //Enter wifi Password

#define SERVER "blynk-cloud.com "             // Comment-out if use Blynk hosted cloud service
#define PORT 8442

#define RELAY_PIN_1       D2   //D2 Relay
#define PUSH_BUTTON_1     D1   //D1 Button
#define led               D5   //D6 Green LED
#define VPIN_BUTTON_1    V12 

#define OTA_HOSTNAME "Home_Automation"


BLYNK_CONNECTED() {

  // Request the latest state from the server

  Blynk.syncVirtual(VPIN_BUTTON_1);

  // Alternatively, you could override server state using:
 // Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);


}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
  digitalWrite(led, relay1State);
}


void checkPhysicalButton()
{
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW) {

      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);
      digitalWrite(led, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }
}

void setup()
{

  Serial.begin(115200);
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS,"blynk-cloud.com", 8442);
  ArduinoOTA.setHostname(OTA_HOSTNAME);  // For OTA - Use your own device identifying name
  ArduinoOTA.begin();  // For OTA

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);
  digitalWrite(led, relay1State);


  // Setup a function to be called every 100 ms
  timer.setInterval(500L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  ArduinoOTA.handle();  // For OTA
  timer.run();
}
