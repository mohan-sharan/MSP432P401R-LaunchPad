#include <Wire.h>			
#include "OPT3001.h"
#define USE_USCI_B1 

opt3001 op;
int ledBlue = 37;

void setup()
{
  unsigned int readings = 0;
  
  Serial.begin(115200);
  delay(1000);  
  op.begin(); 
}

void loop()
{
  // Variables
  uint32_t readings;
     
  // Read OPT3001
  readings = op.readResult();  
  Serial.println(readings, DEC); //LUX Readings
  if (readings < 100)
  {
    digitalWrite(ledBlue, HIGH); //TURN ON - Blue Led             
  }
  else if (readings > 100)
  {
    digitalWrite(ledBlue, LOW); //Turn OFF - Blue Led
  }
  delay(500);
}