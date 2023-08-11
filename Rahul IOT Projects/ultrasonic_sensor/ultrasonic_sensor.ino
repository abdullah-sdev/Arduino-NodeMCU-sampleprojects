int trigPin = 2;
int echoPin = 7;
int duration, cm, inches;

void setup() {
  
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);

  
}
void loop() {
  digitalWrite(trigPin, LOW);
  delay(1000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
  inches = (duration/2) / 74;
  Serial.println(inches);
  Serial.println("inches:");
  Serial.println(cm);
  Serial.println("cm:");
  delay(1000);

 if(duration <= 7){
  digitalWrite(13, HIGH);
//  delay(1000);
  }
  else{
    digitalWrite(13, LOW);
 //   delay(1000);
    }
    if(duration <= 10){
  digitalWrite(12, HIGH);
//  delay(1000);
  }
  else{
    digitalWrite(12, LOW);
 //   delay(1000);
    }
}
