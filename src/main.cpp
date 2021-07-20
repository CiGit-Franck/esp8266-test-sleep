/*
 * 
 * DHT11 - <-->   G ESP
 * DHT11   <--> 3.3 ESP
 * DHT11 S <-->  D5 ESP GPIO14
 * 
 * IMPORTANT: Connect the DO pin to the RST pin only after uploading
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>     // wifi board
#include <Adafruit_Sensor.h> // https://github.com/adafruit/Adafruit_Sensor
#include <DHT.h>             // https://github.com/adafruit/DHT-sensor-library
#include <DHT_U.h>
#include "Credential.h"      // Credentials of my home wifi

#define DHTTYPE DHT11
#define DHTPin D5

// WiFiClient espClient;
DHT dht(DHTPin, DHTTYPE);

void connectWifi()
{
  // wifi
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    Serial.println("...");
    WiFi.begin(ssid, password);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      ;
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("WiFi connected.");
  }
  delay(100);
}

void disconnetWifi()
{
  if (WiFi.disconnect() != WL_DISCONNECTED)
    ;
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("Wifi disconnect.");
  delay(100);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  Serial.println("=== Begin setup ===");
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < 50; i++)
  {
    yield(); // bypass watchdog timer problem
    if (i % 2 == 0)
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(100);
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  dht.begin();
  delay(100);
  Serial.println("=== End setup ===");
}

void loop()
{
  Serial.println("=== Begin loop ===");
  Serial.println("ESP allumé !");
  connectWifi();
  // Simulate task -> ex DHT sensor 
  Serial.println("Humidity : " + String(dht.readHumidity()));
  Serial.println("Temperature : " + String(dht.readTemperature()));
  delay(120e3); // 2 minutes 
  disconnetWifi();
  Serial.println("ESP éteint !");
  Serial.println("=== End loop ===");
  ESP.deepSleep(300e6); // 5 minutes of Deep Sleep
  // Reset board -> setup()
}