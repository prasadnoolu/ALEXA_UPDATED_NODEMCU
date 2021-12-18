#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();

//on/off callbacks 
bool officeLightsOn();
bool officeLightsOff();
bool kitchenLightsOn();
bool kitchenLightsOff();

// Change this before you flash
const char* ssid = "Technicalhub5g";
const char* password = "Technicalhub.io@1";

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *office = NULL;
Switch *kitchen = NULL;

bool isOfficeLightsOn = false;
bool isKitchenLightstsOn = false;

void setup()
{
  Serial.begin(9600);
   pinMode(16,OUTPUT);
   pinMode(5,OUTPUT);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    upnpBroadcastResponder.beginUdpMulticast();
    
    // Define your switches here. Max 10
    // Format: Alexa invocation name, local port no, on callback, off callback
    office = new Switch("office lights", 80, officeLightsOn, officeLightsOff);
    kitchen = new Switch("kitchen lights", 81, kitchenLightsOn, kitchenLightsOff);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*office);
    upnpBroadcastResponder.addDevice(*kitchen);
  }
}
 
void loop()
{
	 if(wifiConnected){
      upnpBroadcastResponder.serverLoop();
      
      kitchen->serverLoop();
      office->serverLoop();
	 }
}

bool officeLightsOn() {
    Serial.println("Switch 1 turn on ...");
    digitalWrite(16,1);
    isOfficeLightsOn = true;    
    return isOfficeLightsOn;
}

bool officeLightsOff() {
    Serial.println("Switch 1 turn off ...");
    digitalWrite(16,0);
    isOfficeLightsOn = false;
    return isOfficeLightsOn;
}

bool kitchenLightsOn() {
    Serial.println("Switch 2 turn on ...");
    digitalWrite(5,1);
    isKitchenLightstsOn = true;
    return isKitchenLightstsOn;
}

bool kitchenLightsOff() {
  Serial.println("Switch 2 turn off ...");
  digitalWrite(5,0);
  isKitchenLightstsOn = false;
  return isKitchenLightstsOn;
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }
  
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}
