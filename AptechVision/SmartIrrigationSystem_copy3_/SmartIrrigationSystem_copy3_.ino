#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
//#include <ESP8266WiFi.h>
#include <WiFiManager.h>
//WiFiClient client;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define DHTPIN D4          // GPIO Pin where the dht11 is connected
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE); 
float h;                  // humidity reading
float t;                  //temperature reading


const int dryval = 890;
const int wetval = 400;
int triggerVal = 50;

const int inhibit = D0;
//const int inhibit2 = D3;
const int mux1 = A0;  // Input Sensors
//const int mux2 = D4;  // OutPut Actuators

const int dA = D5;
const int dB = D6;
const int dC = D7;

int wait = 10;

unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;

//class pump {
//  private: 
//  bool a, b, c;
//  public:
//  bool state;
//  
//  pump(bool c, bool b, bool a) {
//    c = c;
//    b = b;
//    a = a;
//    
//    
//  }
//
//  void onn(){
//    digitalWrite(inhibit, HIGH);
//    digitalWrite(inhibit2, LOW);
//    addressSet(c,b,a);
//    digitalWrite(mux2, HIGH);
//    state = 1;
//    digitalWrite(inhibit2, HIGH);
//    
//  }
//
//  void off() {
//    digitalWrite(inhibit, HIGH);
//    digitalWrite(inhibit2, LOW);
//    addressSet(c,b,a);
//    digitalWrite(mux2, LOW);
//    state = 0;
//    digitalWrite(inhibit2, HIGH);
//  }
//};

void setup() {
  // put your setup code here, to run once:
  

  Serial.begin(9600);
  
    lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
//  lcd.print("Hello, world!");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aptech Vision'22");
  lcd.setCursor(0,1);
  lcd.print("WiFi Signal..");
  WiFiManager wm;
  wm.resetSettings();  //for testing
  bool res;
  res = wm.autoConnect("IrrigationProject","123456"); // password protected ap
  
  if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        lcd.setCursor(0,1);
        lcd.print("Connected");
        delay(1000);
    }
  lcd.setCursor(0,0);
  lcd.print("WiFi connected");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Smart Irrigation");
  delay(500);

    dht.begin();



  pinMode(inhibit, OUTPUT); //Inhibit Set
  digitalWrite(inhibit,LOW);  //Inhibit Low
  
//  pinMode(inhibit2, OUTPUT); //Inhibit2 Set
//  digitalWrite(inhibit2,LOW);  //Inhibit2 Low

  // Declare and Set AddressLines Mux1
  pinMode(dA, OUTPUT);
  pinMode(dB, OUTPUT);
  pinMode(dC, OUTPUT);

  digitalWrite(dA, LOW);
  digitalWrite(dB, LOW);
  digitalWrite(dC, LOW);

  // Set Input Pin
  pinMode(mux1, OUTPUT);
//  pinMode(mux2, INPUT);


 

}

void loop() {
  // put your main code here, to run repeatedly:

//  int dhtdata[2];
//  dhtRead( dhtdata );
//  Serial.print(dhtdata[0]); // Humidity
//  Serial.println(dhtdata[1]); // Temp


  h = dht.readHumidity();     // read humidity
  t = dht.readTemperature();     // read temperature
  Serial.print("H = ");
  Serial.println(h);
  Serial.print("T = ");
  Serial.println(t);

  
  
  int moistureValue1 = moistureRead(0,1,0); // 2nd pin Mux2
  Serial.println(moistureValue1);
  int moisturePercentage1 = map(moistureValue1, dryval, wetval, 0, 100);
  moisturePercentage1 = constrain(moisturePercentage1, 0, 100);

  int moistureValue2 = moistureRead(0,1,1); // 3rd pin Mux2
  int moisturePercentage2 = map(moistureValue2, dryval, wetval, 0, 100);
  moisturePercentage2 = constrain(moisturePercentage2, 0, 100);
  Serial.println(moistureValue2);
  

 // Pump Set
//  pump pump1(0,1,0);
//  pump pump2(0,1,1);
//
//  pump1.off();
//  pump2.off();

  if(moisturePercentage1 <= triggerVal ) {
    Serial.println("Pump On");
//    pump1.onn();
  }else {
    Serial.println("Pump Off");
//    pump1.off();
  }
//  Serial.print("Pump1 State: ");
//  Serial.println(pump1.state);
//  
//  if(moistureValue2 <= triggerVal ) {
//    pump2.onn();
//  }else {
//    pump2.off();
//  }
//  Serial.print("Pump2 State: ");
//  Serial.println(pump2.state);
  

  delay(1000);
  

}



void addressSet(bool c, bool b, bool a) {
  // Set AddressLines
//  Serial.print("a = ");
//  Serial.println(a);
//  Serial.print("b = ");
//  Serial.println(b);
//  Serial.print("c = ");
//  Serial.println(c);
  
  digitalWrite(dA, a);
  digitalWrite(dB, b);
  digitalWrite(dC, c);
}

//void dhtRead(float arr[]) {
//  // Turn On Mux 1
//  digitalWrite(inhibit, LOW);
//  digitalWrite(inhibit2, HIGH);
//  addressSet(0,0,0);
//  
//  DHT dht(mux2, DHTTYPE);
//  dht.begin();
//  
//  float h;                  // humidity reading
//  float t;                  //temperature reading
//  
//  h = dht.readHumidity();     // read humidity
//  t = dht.readTemperature();     // read temperature
//  arr[0] = h;
//  arr[1] = t;
////  delay(2000);
//digitalWrite(inhibit, HIGH);
//}


int moistureRead(bool c, bool b, bool a){
  // Turn On Mux 1
  int moisturePercentage;
  digitalWrite(inhibit, LOW);
//  digitalWrite(inhibit2, HIGH);
  addressSet(c,b,a);
  int moistureValue = analogRead(mux1);
  digitalWrite(inhibit, HIGH);
  
  
  return moistureValue;
}
