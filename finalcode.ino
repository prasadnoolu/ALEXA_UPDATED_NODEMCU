
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
// define the GPIO connected with Relays
#define RelayPin1 16  //D1
#define RelayPin2 5  //D2
#define RelayPin3 4 //D7
#define RelayPin4 0 //D5
#define RelayPin5 2 //D6
#define RelayPin6 14 //D7
#define RelayPin7 12 //D5
#define RelayPin8 13//D6


// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

void fifthLightChanged(uint8_t brightness);
void sixthLightChanged(uint8_t brightness);
void seventhLightChanged(uint8_t brightness);
void eighthLightChanged(uint8_t brightness);

// WiFi Credentials
const char* ssid = "sandeep";
const char* password = "22122012";

// device names
String Device_1_Name = "frontlight";
String Device_2_Name = "backlight";
String Device_3_Name = "centrelight";
String Device_5_Name = "fan1";
String Device_6_Name = "fan2";
String Device_7_Name = "fan3";
String Device_8_Name = "fan4";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(RelayPin5, OUTPUT);
  pinMode(RelayPin6, OUTPUT);
  pinMode(RelayPin7, OUTPUT);
  pinMode(RelayPin8, OUTPUT);
  
  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged);
    espalexa.addDevice(Device_3_Name, thirdLightChanged);

    espalexa.addDevice(Device_5_Name, fifthLightChanged);
    espalexa.addDevice(Device_6_Name, sixthLightChanged);
    espalexa.addDevice(Device_7_Name, seventhLightChanged);
    espalexa.addDevice(Device_8_Name, eighthLightChanged);
    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(RelayPin1, HIGH);
      digitalWrite(RelayPin2, HIGH);
      Serial.println("Device1 ON");
    }
  else
  {
    digitalWrite(RelayPin1, LOW);
    digitalWrite(RelayPin2, LOW);
    Serial.println("Device1 OFF");
  }
}

void secondLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin3, HIGH);
      Serial.println("Device2 ON");
    }
  else
  {
    digitalWrite(RelayPin3, LOW);
    Serial.println("Device2 OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(RelayPin4, HIGH);
      Serial.println("Device3 ON");
    }
  else
  {
    digitalWrite(RelayPin4, LOW);
    Serial.println("Device3 OFF");
  }
}



void fifthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin5, HIGH);
      Serial.println("Device5 ON");
    }
  else
  {
    digitalWrite(RelayPin5, LOW);
    Serial.println("Device5 OFF");
  }
}

void sixthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin6, HIGH);
      Serial.println("Device6 ON");
    }
  else
  {
    digitalWrite(RelayPin6, LOW);
    Serial.println("Device6 OFF");
  }
}

void seventhLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin7, HIGH);
      Serial.println("Device7 ON");
    }
  else
  {
    digitalWrite(RelayPin7, LOW);
    Serial.println("Device7 OFF");
  }
}


void eighthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin8, HIGH);
      Serial.println("Device8 ON");
    }
  else
  {
    digitalWrite(RelayPin8, LOW);
    Serial.println("Device8 OFF");
  }
}



// connect to wifi  returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
