#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>
#define MAX_FONT_SIZE 1

Screen_HX8353E myScreen;

const int buttonOne = 33;  // the number of the pushbutton pin
const int buttonTwo = 32;  // the number of the pushbutton pin

int red[] = {30,29,28,27};  // red led pin nos.
int blue[] = {35,36,12,18}; //blue led pin nos.

int buttonOneState = 0;  // variable for reading the pushbutton #1 status
int buttonTwoState = 0;  // variable for reading the pushbutton #2 status

int waitTime = 1000;

void setup()
{
  myScreen.begin();
  
  // initialize the pushbutton pin as an input
  pinMode(buttonOne, INPUT_PULLUP);     
  pinMode(buttonTwo, INPUT_PULLUP);  
  
  for(int i=0; i<4; i++)
  {
   digitalWrite(blue[i], OUTPUT);
   digitalWrite(red[i], OUTPUT);  
   digitalWrite(blue[i], LOW);
   digitalWrite(red[i], LOW);
  }    
}

void loop()
{
  
  // display text
  myScreen.gText(0, 10, "*********************", greenColour);
  myScreen.gText(0, 30, "    4-BIT COUNTER    ", yellowColour);
  myScreen.gText(0, 50, "*********************", greenColour);
  myScreen.gText(0, 100, "*********************", greenColour);
  myScreen.gText(0, 110, "PRESS -> B1: UP", yellowColour);
  myScreen.gText(0, 120, "PRESS -> B2: DOWN", yellowColour);
  
  // read the state of the pushbutton value
  buttonOneState = digitalRead(buttonOne);
  
  if (buttonOneState == LOW)
  {
   for (int i=0; i<=15; i++) {
   blueLeds(i);
   myScreen.gText(0, 75, "  UP: " + btoa(i) + " | " + i32toa(i, 1, 1), whiteColour);
   delay(waitTime);
  }    
  }
  else
  {
   myScreen.gText(0, 75, "                     ");
   for(int i=0; i<4; i++)
   {
   digitalWrite(blue[i], LOW);
   } 
  }

  // read the state of the pushbutton value
  buttonTwoState = digitalRead(buttonTwo);
  
  if (buttonTwoState == LOW)
  {
   for (int i=15; i>=0; i--) {
   redLeds(i);
   myScreen.gText(0, 75, "DOWN: " + btoa(i) + " | " + i32toa(i, 1, 1), whiteColour);
   delay(waitTime);
  }    
  }
  else
  {
   myScreen.gText(0, 75, "                     ");
   for(int i=0; i<4; i++)
   {
   digitalWrite(red[i], LOW);
   } 
  }   
}

void blueLeds(int n) 
{
  for (int i=0; i<4; i++) {
    if (n % 2)
      digitalWrite(blue[i], HIGH);
    else
      digitalWrite(blue[i], LOW);
    n /= 2;
  } 
}

void redLeds(int m) 
{
  for (int i=0; i<4; i++) {
	// bitRead() function: reads a bit of a number to see if its 1 or 0
	// if its a 1 then turn LED ON
	// if its a 0 then turn LED OFF
    if (bitRead(m, i) == 1){
      digitalWrite(red[i], HIGH);
    }
    else{
      digitalWrite(red[i], LOW);
    }
  } 
}
