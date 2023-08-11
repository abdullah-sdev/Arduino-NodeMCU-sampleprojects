int pushButton = 2;
int led = 13;
void setup() {
  Serial.begin(9600);
  pinMode(pushButton,INPUT);
  pinMode(led, OUTPUT);
}
void loop() {
  int buttonState = digitalRead(2);
  Serial.println(buttonState);
  delay(1);
  //read the output pin
  if(buttonState > 0 ) {
  digitalWrite(led,HIGH);
  delay(1000);
  }
 else{
  digitalWrite(led,LOW);
  delay(1000);
  }
}
