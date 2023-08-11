
const int inhibit = D1;
const int inhibit2 = D2;
const int led = D0;
const int led2 = D4;

const int dA = D5;
const int dB = D6;
const int dC = D7;

int wait = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inhibit, OUTPUT); //Inhibit Set
  digitalWrite(inhibit,LOW);  //Inhibit Low
  
  pinMode(inhibit2, OUTPUT); //Inhibit2 Set
  digitalWrite(inhibit2,LOW);  //Inhibit2 Low

  // Declare and Set AddressLines Mux1
  pinMode(dA, OUTPUT);
  pinMode(dB, OUTPUT);
  pinMode(dC, OUTPUT);

  digitalWrite(dA, LOW);
  digitalWrite(dB, LOW);
  digitalWrite(dC, LOW);

  // Set Input Pin
  pinMode(led, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  
  digitalWrite(inhibit2, LOW);
  
  //led 1
  addressSet(0, 0, 0);
//  digitalWrite(dA, LOW);
//  digitalWrite(dB, LOW);
//  digitalWrite(dC, LOW);
  digitalWrite(led, 1);  
  delay(500); 
  digitalWrite(led, 0);

  //led 2
  addressSet(0, 0, 1);
//  digitalWrite(dA, HIGH);
//  digitalWrite(dB, LOW);
//  digitalWrite(dC, LOW);
  digitalWrite(led, 1);  
  delay(500);
  digitalWrite(led, 0);

  //led 3
  addressSet(0, 1, 1);
//digitalWrite(dA, HIGH);
//  digitalWrite(dB, HIGH);
//  digitalWrite(dC, LOW);
  digitalWrite(led, 1);  
  delay(500);
  digitalWrite(led, 0);

////////////
  digitalWrite(inhibit, HIGH);
  delay(wait);
  
  digitalWrite(inhibit2, LOW);

  //led 1
  addressSet(0, 0, 0);
//  digitalWrite(dA, LOW);
//  digitalWrite(dB, LOW);
//  digitalWrite(dC, LOW);
  digitalWrite(led, 1);  
  delay(500); 
  digitalWrite(led, 0);

  //led 2
  addressSet(0, 0, 1);
//  digitalWrite(dA, HIGH);
//  digitalWrite(dB, LOW);
//  digitalWrite(dC, LOW);
  digitalWrite(led, 1);  
  delay(500);
  digitalWrite(led, 0);

  //led 3
  addressSet(0, 1, 1);
//digitalWrite(dA, HIGH);
//  digitalWrite(dB, HIGH);
//  digitalWrite(dC, LOW);
  digitalWrite(led, 1);  
  delay(500);
  digitalWrite(led, 0);

  digitalWrite(inhibit2, HIGH);
  delay(wait);
  
  digitalWrite(inhibit, LOW);

  
//  digitalWrite(inhibit, HIGH);
//  delay(wait);
//  digitalWrite(inhibit, LOW);

}


void addressSet(bool c, bool b, bool a) {
  // Set AddressLines
  Serial.print("a = ");
  Serial.println(a);

  Serial.print("b = ");
  Serial.println(b);

  Serial.print("c = ");
  Serial.println(c);
  digitalWrite(dA, a);
  digitalWrite(dB, b);
  digitalWrite(dC, c);
}
