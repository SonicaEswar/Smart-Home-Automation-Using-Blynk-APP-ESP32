//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"
#define BLYNK_TEMPLATE_ID "TMPL3cdiBdV6U"
#define BLYNK_TEMPLATE_NAME "project"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"
int relay=2;
BLYNK_WRITE(V0)
{
  int relay1State = param.asInt(); // Get the relay1State of the virtual button
  
  digitalWrite(relay, relay1State);
   
  if(relay1State == 0)
  {
    digitalWrite(relay, 1); // Turn the LED on
  }
  else
  {
    digitalWrite(relay, 0); // Turn the LED off
  }

}

void setup()
{
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
