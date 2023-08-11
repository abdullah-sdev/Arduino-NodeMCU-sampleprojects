#include "DHT.h"
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
#include <WiFiManager.h>
WiFiClient client;

const char* server = "api.thingspeak.com";
const char* ssid =  "APTECHUNI";     // replace with your wifi ssid and wpa2 key
const char* pass =  "password6";

String apiKey = "D0EIVSGKUK3L33BC";     //   Enter your Write API key here

#define DHTPIN D3          // GPIO Pin where the dht11 is connected
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE); 
float h;                  // humidity reading
float t;                  //temperature reading

const int motorPin = D1;

const int moisturePin = A0;             // moisteure sensor pin
float moisturePercentage;              //moisture reading


const int RS = D2, EN = D4, d4 = D5, d5 = D6, d6 = D7, d7 = D8;  
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;



void setup() {
  // put your setup code here, to run once:
//     WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);
//      Serial.begin(9600);
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
     wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("Plantbro","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
         ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("WiFi connected");
    }

  delay(10);

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW); // keep motor off initally

  dht.begin();

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Aptech Vision'22");


  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");

  lcd.print("WiFi connected");
  delay(500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis(); // grab current time

  char data[]= "";
  
  
  h = dht.readHumidity();     // read humiduty
  t = dht.readTemperature();     // read temperature
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    

  
  


    moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );
    if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
      Serial.println("---------------");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" C,");
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.println(" ");
      Serial.print("Soil Moisture is  = ");
      Serial.print(moisturePercentage);
      Serial.println("%");
      
     
        
      
      previousMillis1 = millis();
    }

    if (moisturePercentage < 50) {
      digitalWrite(motorPin, HIGH);         // tun on motor
    }
    if (moisturePercentage > 50 && moisturePercentage < 55) {
      digitalWrite(motorPin, HIGH);        //turn on motor pump
    }
    if (moisturePercentage > 50) {
      digitalWrite(motorPin, LOW);          // turn off mottor
    }

    
    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      sendThingspeak();           //send data to thing speak
      previousMillis = millis();

      
      lcd.setCursor(0, 1);


      lcd.print("M: " + char(moisturePercentage));
      lcd.print("H: " + char(h));
      lcd.print("T: " + char(t));


      
      client.stop();
    }

    




    
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
