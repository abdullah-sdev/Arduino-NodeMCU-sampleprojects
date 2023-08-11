int IRSensor = 2; // connect ir sensor to arduino pin 2
int pinLED = 13; // conect Led to arduino pin 13



void setup() 
{



  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (pinLED, OUTPUT); // Led pin OUTPUT
}

void loop()
{
  int statusSensor = digitalRead(IRSensor);
  
  if (statusSensor == 1)
  {
    digitalWrite(pinLED, LOW); // LED LOW
  }
  
  else
  {
    digitalWrite(pinLED, HIGH); // LED High
  }
  
}
