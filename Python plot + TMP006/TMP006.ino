#include <Wire.h>
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 

Adafruit_TMP006 tmp006;
void printFloat(float value, int places) ;

void setup()
{
  Serial.begin(115200);

  // Initalizes the TMP006 for operation and for I2C communication
  if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("No sensor found");
    while (1);
  }
}

void loop()
{
  float objt = tmp006.readObjTempC();
  float diet = tmp006.readDieTempC();
  
  Serial.print(objt); //Object Temperature
  Serial.print(" -- ");
  Serial.println(diet); //Die Temperature  

  delay(1000);
}
