
const int moisturePin = A0;             // moisteure sensor pin

float moisturePercentage;              //moisture reading



void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
//    unsigned long currentMillis = millis(); // grab current time


    Serial.println(analogRead(moisturePin));

    delay(1000);


}
