#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>
#define MAX_FONT_SIZE 1

Screen_HX8353E myScreen;

#include <Servo.h>
Servo myServo;

const int trig_pin = 33;
const int echo_pin = 32;

int ledGreen = 38;
int ledRed = 39;

int distance_cm;
long duration;
int pos = 0;

void setup()
{
  myScreen.begin();
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  myServo.attach(19);
}

void loop()
{
  //Display some geometrical shapes on the 128x128 LCD 
  myScreen.circle(50, 80, 4, whiteColour);
  myScreen.circle(80, 80, 4, whiteColour);
  
  myScreen.circle(55, 108, 1, whiteColour);
  myScreen.circle(60, 110, 1, whiteColour);
  myScreen.circle(65, 112, 1, whiteColour);
  myScreen.circle(70, 110, 1, whiteColour);
  myScreen.circle(75, 108, 1, whiteColour);
 
  myScreen.rectangle(10, 70, 120, 120, magentaColour);
  
  //Servo    
  for(pos = 0; pos < 180; pos+=10)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 10 degrees 
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    ultrasonic_sensor_reading();    
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=10)     // goes from 180 degrees to 0 degrees 
  {                                
    myServo.write(pos);              
    ultrasonic_sensor_reading();    
    delay(15);                       
  }
}

//Ultrasonic sensor
void ultrasonic_sensor_reading()
{
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance_cm = (duration*0.034)/2.0;
  
  Serial.println(distance_cm); 
  
  if (distance_cm > 20)
  {
    digitalWrite(ledGreen, HIGH); //TURN ON - Green LED
    digitalWrite(ledRed, LOW); //TURN OFF - Red LED
  }
  else if (distance_cm < 20)
  {
    digitalWrite(ledGreen, LOW); //TURN OFF - Green LED
    digitalWrite(ledRed, HIGH); //TURN ON - Red LED
  }
  
  //Display the sensor reading on the 128x128 LCD
  myScreen.gText(0, 10, "**ULTRASONIC SENSOR**", whiteColour);
  myScreen.gText(0, 30, "OBJECT DETECTED(cm): ", yellowColour);
  myScreen.gText(25, 45, "--> " + i32toa(distance_cm, 1, 1), greenColour);
  
  delay(15);
}
