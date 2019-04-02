 
 
 //callback notifying us of the need to save config
void saveConfigCallback () {
  shouldSaveConfig = true;
}
 
 void restoreparameters(){

  if (SPIFFS.begin()) {
    if (SPIFFS.exists("/config.json")) {
//file exists, reading and loading
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        size_t size = configFile.size();
// Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
//        json.printTo(Serial);
        if (json.success()) {
// json will parse the file for the variable name and load it into the supplied variable
          strcpy(mqtt_server, json["mqtt_server"]);     //get the mqtt_server <== you need one of these for each param
          strcpy(mqtt_port, json["mqtt_port"]);         //get the mqtt port
          strcpy(blynk_token, json["blynk_token"]);     //get the blynk token

        }
        configFile.close();
      }
    }
  } 
  //end read
 }



void startmywifi(){
  //Local intialization. Once its done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // The extra parameters to be configured (can be either global or just here)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
  WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 32);
  
//set static ip if you want
//  wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  
//  <============== add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_blynk_token);

  //reset settings - for testing
//    wifiManager.resetSettings();    // <========= once you have this working you can comment out this line

  //set minimu quality of signal so it ignores AP's under that quality
  //defaults to 8%
  //wifiManager.setMinimumSignalQuality();
  
  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  //wifiManager.setTimeout(120);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("AutoConnectAP", "password")) {
    ESP.reset();    //reset and try again
  }

  //if you get here you have connected to the WiFi

  //get the custom parameters here
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(blynk_token, custom_blynk_token.getValue());

  //check the flag to see if we save the custom parameters to FS
  if (shouldSaveConfig) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

 //set the custom parameters here
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["blynk_token"] = blynk_token;

    File configFile = SPIFFS.open("/config.json", "w");
    if (configFile) {
//      json.printTo(Serial);       // dump the data to the serial
      json.printTo(configFile);   //write the custom parameters here
      configFile.close();
    } else Serial.println("failed to open config file for writing");
    //end save
  }
}
