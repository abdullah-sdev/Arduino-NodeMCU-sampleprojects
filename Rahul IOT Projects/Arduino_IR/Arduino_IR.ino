
int irSensor = 12;
int relayPin = 7;
void setup()
{
  Serial.begin(9600);
  pinMode(irSensor, INPUT);
  pinMode(relayPin, OUTPUT);
}
void loop()
{
  int value = digitalRead(irSensor);
  Serial.println("");
  Serial.print("Sensor Value = ");
  Serial.print(value);
  
  if(value == 0)
  {
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }
  delay(50);
}
