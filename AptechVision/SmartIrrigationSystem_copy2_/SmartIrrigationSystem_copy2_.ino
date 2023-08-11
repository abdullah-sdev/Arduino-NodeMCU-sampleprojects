#include "DHT.h"
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
#include <WiFiManager.h>
WiFiClient client;

const char* server = "api.thingspeak.com";
//const char* ssid =  "HUAWEI-5WRD";     // replace with your wifi ssid and wpa2 key
//const char* pass =  "f7t78d6K";

String apiKey = "D0EIVSGKUK3L33BC";     //   Enter your Write API key here

#define DHTPIN D3          // GPIO Pin where the dht11 is connected
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE); 
float h;                  // humidity reading
float t;                  //temperature reading

const int motorPin = D4;
String motorVal = "OFF";
int triggerVal = 50;
String print_lcd_output = "...";
const int moisturePin = A0;             // moisteure sensor pin
int moistureValue;
float moisturePercentage;              //moisture reading
const int dryval = 890;
const int wetval = 400;

int count = 0;

const int RS = D2, EN = D1, d4 = D5, d5 = D6, d6 = D7, d7 = D8;  
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

  unsigned long interval = 10000;
  unsigned long previousMillis = 0;
  unsigned long interval1 = 1000;
  unsigned long previousMillis1 = 0;

int h_prev = 0;
int t_prev = 0;

void setup() {
  // put your setup code here, to run once:
// WiFi.mode(WIFI_STA);

  

  Serial.begin(9600);
  delay(10);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aptech Vision'22");
  lcd.setCursor(0,1);
  lcd.print("WiFi Signal..");
WiFiManager wm;
 wm.resetSettings();  //for testing
bool res;
res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
  
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


    
  
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, HIGH); // keep motor off initally

  dht.begin();


  
//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, pass);
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");              // print ... till not connected
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
  lcd.setCursor(0,0);
  lcd.print("WiFi connected");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Smart Irrigation");
  delay(500);
  
//  lcd.clear();
  lcd.setCursor(0, 1);
//  
//  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis(); // grab current time

//reading data from sensors

if (motorVal == "ON"){

  pumpOff();
  motorVal = "ON";
  moistureValue = analogRead(moisturePin);
  h = dht.readHumidity();     // read humidity
  t = dht.readTemperature();     // read temperature
  
//  lcd_output_disp();
  
  pumpOn();
  

  
}else{
  moistureValue = analogRead(moisturePin);
  h = dht.readHumidity();     // read humidity
  t = dht.readTemperature();     // read temperature
  
//  lcd_output_disp();
  
}


if (isnan(h) || isnan(t))
      {
        h = h_prev;
        t = t_prev;
      }


//     moisturePercentage = map(analogRead(moisturePin), wetval, dryval, 0, 100);
    moisturePercentage = map(moistureValue, dryval, wetval, 0, 100);
    moisturePercentage = constrain(moisturePercentage, 0, 100);
    
//    moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );

//  h = dht.readHumidity();     // read humidity
//  t = dht.readTemperature();     // read temperature

  
     
 ///////////// Logic 1
      if(moisturePercentage <= triggerVal ) {
        pumpOn();
      }else {
        pumpOff();
      }
    
    if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
      
      
      
      Serial.println("---------------");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" C,");
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.println(" ");
      Serial.print("Soil Moisture is  = ");
      Serial.println(moistureValue);
      Serial.print("Soil Moisture is  = ");
      Serial.print(moisturePercentage);
      Serial.println("%");
      Serial.print("Motor: ");
      Serial.println( motorVal );

      print_lcd_output = "M:" + String(moisturePercentage) + ",H:" + String(h) + ",T:" + String(t);
      
     lcd_output_disp(print_lcd_output);
     print_lcd_output= "";
      previousMillis1 = millis();
    }
    
    

//  if (isnan(h) || isnan(t))
//  {
//    Serial.println("Failed to read from DHT sensor!");
//    
//    delay(5);
//    pumpOff();
//    moisturePercentage = moisturePercentage;
//    lcd_output_disp(print_lcd_output);
//  }



    
    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      sendThingspeak();           //send data to thing speak
      previousMillis = millis();
      
      
//lcd_output_disp();
      
      client.stop();
    }

   

////////////////// Logic 2
//    if (moisturePercentage < 50) {
//      digitalWrite(motorPin, LOW);         // tun on motor
//    }
//    if (moisturePercentage > 50 && moisturePercentage < 55) {
//      digitalWrite(motorPin, LOW);        //turn on motor pump
//    }
//    if (moisturePercentage > 50) {
//      digitalWrite(motorPin, HIGH);          // turn off mottor
//    }


//count += 1;
//Serial.println("Count: ");
//Serial.println(count );
////Serial.println(count % 10);
//if((count % 10)== 0){
//  count = 0;
//  lcd.clear();
//  delay(500);
//   lcd_output_disp_r();
//   
//  
//}

 if (h != 0 && t != 0 )
      {
        h_prev = h;
        t_prev = t;
      }
    
}
//void lcd_output_disp_r(){
//  lcd.begin(16,2);
//  lcd.clear();
//  lcd.setCursor(0,0);
//  
//  lcd_output_disp();
//  
//}
void lcd_output_disp(String p_lcd){

      
      
      lcd.begin(16,2);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Smart Irrigation");
      
      lcd.setCursor(0, 1);
      lcd.print(print_lcd_output);
  
}

void pumpOn(){

  digitalWrite(motorPin, LOW); // turn On 
  delay(2000);
 
  motorVal = "ON";
  
}

void pumpOff(){
  digitalWrite(motorPin, HIGH); // turn Off
  delay(100);
  motorVal = "OFF";
}


void sendThingspeak() {
  if (client.connect(server, 80))
  {
    String postStr = apiKey;              // add api key in the postStr string
    postStr += "&field1=";
    postStr += String(moisturePercentage);    // add mositure reading
    postStr += "&field2=";
    postStr += String(t);                 // add tempr readin
    postStr += "&field3=";
    postStr += String(h);                  // add humidity readin
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());           //send lenght of the string
    client.print("\n\n");
    client.print(postStr);                      // send complete string
    Serial.print("Moisture Percentage: ");
    Serial.println(moisturePercentage);
    Serial.print("%. Temperature: ");
    Serial.print(t);
    Serial.print(" C, Humidity: ");
    Serial.println(h);
    Serial.println("%. Sent to Thingspeak.");
  }

}
