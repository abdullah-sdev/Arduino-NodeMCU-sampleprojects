

int pinRed = 13;
int pinYellow = 12;
int pinGreen = 11;

void setup() {
  // put your setup code here, to run once:

 pinMode(pinRed, OUTPUT);
 pinMode(pinYellow, OUTPUT);
 pinMode(pinGreen, OUTPUT);
 Serial.begin(9600); //baud rate
 

  

}

void loop() {
  // put your main code here, to run repeatedly:
  
//  stop red  
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinYellow, LOW);
  digitalWrite(pinGreen, LOW);
  Serial.println("Stop...");
  delay(3000);
  
//  yellow hold
  digitalWrite(pinRed, LOW);
  digitalWrite(pinYellow, HIGH);
  Serial.println("Readyy...");
  delay(3000);
  
//  green go
  digitalWrite(pinYellow, LOW);
  digitalWrite(pinGreen, HIGH);
  Serial.println("Go...");
  delay(3000);

  

}
