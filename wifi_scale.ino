

#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include "HX711.h"
#include <U8g2lib.h>
#include "SSD1306Wire.h"
#include <WidgetRTC.h>
#include "globals.h"

//create terminal widget instance and attach it to the pin
WidgetTerminal terminal(terminaldisplay);

//create timer instance
BlynkTimer timer;

// Initialize our HX711 interface
HX711 scale;

//Create the real time clock instance
WidgetRTC rtc;

// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, 2, 14);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // these two call get the data from the SPIFFS file and use the data to provision  blynk and wifi
  restoreparameters();
  startmywifi();

  Blynk.config(blynk_token);          // config Blynk

  setupdisplay();
  setupscale();

  // Timed Lambda code
  timer.setInterval(700L, [] () { // Run every .7 seconds
    // START timer Function    <--- put code lines here that you want to run repetedly in sync
    if (!calibrating)
      displayweight(readscale());
  });  // END Timer Function

}

void loop() {
  // in most cases you should not put code here
  if (Blynk.connected()) {
    Blynk.run();
  } else Blynk.connect(1000l);                // timeout 1 seconds
  timer.run();
}
