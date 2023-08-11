const int buzzer = 9; //buzzer to arduino pin 9
const int buzzer1 = 8; //buzzer to arduino pin 9

void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(buzzer1, OUTPUT); // Set buzzer - pin 9 as an output

}

void loop(){
 
  tone(buzzer, 5000); // Send 1KHz sound signal...
  delay(50);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(50);        // ...for 1sec

 tone(buzzer1, 10000); // Send 1KHz sound signal...
  delay(50);        // ...for 1 sec
  noTone(buzzer1);     // Stop sound...
  delay(50);        // ...for 1sec

  tone(buzzer, 15000); // Send 1KHz sound signal...
  delay(50);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(50);        // ...for 1sec

  tone(buzzer, 150000); // Send 1KHz sound signal...
  delay(50);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(50);        // ...for 1sec


}
