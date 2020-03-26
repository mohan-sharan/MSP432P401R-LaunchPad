#ifndef __CC3200R1M1RGC__

#include <SPI.h>
#endif
#include <WiFi.h>

// your network name also called SSID
char ssid[] = "";
// your network password
char password[] = "";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

WiFiServer server(80);

//led pin connections
int redLed = 30;
int greenLed = 29;
int yellowLed = 28;
int blueLed = 27;

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(redLed, OUTPUT);     
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

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
  
  // you're connected now, so print out the status  
  printWifiStatus();

  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");
}

void loop() {
  int i = 0;
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    char buffer[150] = {0};                 // make a buffer to hold incoming data
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (strlen(buffer) == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.println("<html><head><title>Energia CC3100 WiFi Web Server</title></head>");
            client.println("<body style=\"background-color:#212F3C;\"><center>");
            
            client.println("<h1><font color=\"#FBFCFC\" face=\"Courier\">CC3100 WIFI WEB SERVER</font></h1>");
            client.println("<h2><font color=\"#FBFCFC\" face=\"Courier\">MULTI LED CONTROL</font></h2>");
            
            client.println("<p><font size=\"4\" color=\"#E74C3C\" face=\"Courier\">RED LED</font></p>");
            client.println("<button onclick=\"location.href='/RH'\">HIGH</button>");
            client.println("<button onclick=\"location.href='/RL'\">LOW</button>");
            
            client.println("<br>");
            client.println("<br>");
            
            client.println("<p><font size=\"4\" color=\"#229954\" face=\"Courier\">GREEN LED</font></p>");
            client.println("<button onclick=\"location.href='/GH'\">HIGH</button>");
            client.println("<button onclick=\"location.href='/GL'\">LOW</button>");
            
            client.println("<br>");
            client.println("<br>");
            
            client.println("<p><font size=\"4\" color=\"#F4D03F\" face=\"Courier\">YELLOW LED</font></p>");
            client.println("<button onclick=\"location.href='/YH'\">HIGH</button>");
            client.println("<button onclick=\"location.href='/YL'\">LOW</button>");
            
            client.println("<br>");
            client.println("<br>");
            
            client.println("<p><font size=\"4\" color=\"#AED6F1\" face=\"Courier\">BLUE LED</font></p>");
            client.println("<button onclick=\"location.href='/BH'\">HIGH</button>");
            client.println("<button onclick=\"location.href='/BL'\">LOW</button>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear the buffer:
            memset(buffer, 0, 150);
            i = 0;
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          buffer[i++] = c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /RH" or "GET /RL":
        if (endsWith(buffer, "GET /RH")) {
          digitalWrite(redLed, HIGH);               
        }
        if (endsWith(buffer, "GET /RL")) {
          digitalWrite(redLed, LOW);                
        }
        
        if (endsWith(buffer, "GET /GH")) {
          digitalWrite(greenLed, HIGH);               
        }
        if (endsWith(buffer, "GET /GL")) {
          digitalWrite(greenLed, LOW);                
        }
        
        if (endsWith(buffer, "GET /YH")) {
          digitalWrite(yellowLed, HIGH);               
        }
        if (endsWith(buffer, "GET /YL")) {
          digitalWrite(yellowLed, LOW);                
        }
        
        if (endsWith(buffer, "GET /BH")) {
          digitalWrite(blueLed, HIGH);               
        }
        if (endsWith(buffer, "GET /BL")) {
          digitalWrite(blueLed, LOW);                
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

//
//a way to check if one array ends with another array
//
boolean endsWith(char* inString, char* compString) {
  int compLength = strlen(compString);
  int strLength = strlen(inString);
  
  //compare the last "compLength" values of the inString
  int i;
  for (i = 0; i < compLength; i++) {
    char a = inString[(strLength - 1) - i];
    char b = compString[(compLength - 1) - i];
    if (a != b) {
      return false;
    }
  }
  return true;
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
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}