//AMBIENT LIGHT SENSOR DATA - TO THE WEB
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#define USE_USCI_B1 
#include "OPT3001.h"
opt3001 opt3001;

char ssid[] = "Your network name";
char password[] = "Your network password";

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
  uint32_t luxValue;
  luxValue = opt3001.readResult();
  Serial.println(luxValue); 
    
  String str = (String)luxValue;
  int str_len = str.length() + 1;
  char char_array[str_len];
  str.toCharArray(char_array, str_len);
  

  if(client.connect("Energia_Client_EDUMKII")) {
    client.publish("EDUMKII_IOT", char_array); //topic
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

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
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
