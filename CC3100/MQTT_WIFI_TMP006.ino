//EMAIL ALERTS - TMP006 
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#define USE_USCI_B1

#include "OPT3001.h"
opt3001 opt3001;

#include "Adafruit_TMP006.h"
Adafruit_TMP006 tmp006;

char ssid[] = "your network name";
char password[] = "your network password";

// MQTTServer to use
char server[] = "mqtt.eclipse.org";
/*
Publicly-accessible MQTT brokers:
https://github.com/mqtt/mqtt.github.io/wiki/public_brokers
*/

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

void setup()
{
  Serial.begin(115200);
  
  opt3001.begin();
 
  // Initalizes the TMP006 for operation and for I2C communication
  if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("No sensor found");
    while (1);
  } 
   
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  // We are connected and have an IP address.
  // Print the WiFi status.
  printWifiStatus();
}

void loop()
{
  /*uint32_t luxValue;
  luxValue = opt3001.readResult();
      
  char lightString[10];
  dtostrf(luxValue, 5, 0, lightString);
  Serial.println(lightString);*/
  
  float objt; 
  objt = tmp006.readObjTempC();
  
  char tempString[10];
  dtostrf(objt, 2, 2, tempString);
  Serial.println(tempString);
    
  if(client.connect("CC3100_EDUMKII_Client")) {
    //client.publish("EDUMKII_OPT3001", lightString); //topic 1
    client.publish("EDUMKII_TMP006", tempString); //topic 2
    Serial.println("Publish successful!!");
    client.disconnect();
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message for topic ");
  Serial.print(topic);
  Serial.print("with length ");
  Serial.println(length);
  Serial.println("Message:");
  Serial.write(payload, length);
  Serial.println();
}
