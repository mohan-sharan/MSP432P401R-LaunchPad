//MSP432P401R
//LaunchPad Development Kit
//LED Control

const int LED1 = 75; //RED
const int LED2 = 76; //GREEN
const int LED3 = 77; //BLUE

char incoming_data = '\0';
  
void setup() {
  Serial.begin(9600);  
  
  pinMode(LED1, OUTPUT);  
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);  
}

// the loop routine runs over and over again forever:
void loop() {
  //check for incoming data
  if (Serial.available() > 0)
  {
    //read the incoming data
    incoming_data = Serial.read();
    
    if (incoming_data == 'r')
    {
      //RED LED - ON
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
    else if (incoming_data == 'g')
    {
      //GREEN LED - ON
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
    }
    else if (incoming_data == 'b')
    {
      //BLUE LED - ON
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
    }
    else if (incoming_data == 'm')
    {
      setColor(255, 165, 0); // Orange Color
      delay(1000);
      setColor(0, 255, 255);  // Aqua Color
      delay(1000);
      setColor(255, 255, 255); // White Color
      delay(1000);
      setColor(128, 0, 128); // Purple Color
      delay(1000);
    }
    else if (incoming_data == 'q')
    {
      //LEDs - OFF
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
  delay(1000); // wait for a second
}
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(LED1, redValue);
  analogWrite(LED2, greenValue);
  analogWrite(LED3, blueValue);
}
