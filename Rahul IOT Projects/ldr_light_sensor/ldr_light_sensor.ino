int value=0;
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);
}

void loop()
  
{
  
  value= analogRead(A0);
  
  if(value<10)
  {
    digitalWrite(11, HIGH);
    delay(1000);
    Serial.println("Light ON");
    Serial.println(value);
  }
  else
  {
     digitalWrite(11, LOW);
    delay(1000);
    Serial.println("Light OFF");
    Serial.println(value);
  }
}
