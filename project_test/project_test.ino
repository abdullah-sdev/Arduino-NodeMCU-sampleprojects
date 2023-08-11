#include "DHT.h"


#include <ESP8266WiFi.h>

WiFiClient client;

const char* server = "api.thingspeak.com";
//const char* ssid =  "APTECHUNI";     // replace with your wifi ssid and wpa2 key
  //const char* pass =  "password";
  const char* ssid =  "HUAWEI-5WRD";     // replace with your wifi ssid and wpa2 key
const char* pass =  "f7t78d6K";

String apiKey = "D0EIVSGKUK3L33BC";     //   Enter your Write API key here

#define DHTPIN D3          // GPIO Pin where the dht11 is connected
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE); 
float h;                  // humidity reading
float t;                  //temperature reading

const int motorPin = D1;

const int moisturePin = A0;             // moisteure sensor pin
float moisturePercentage;              //moisture reading


unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(10);

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW); // keep motor off initally

  dht.begin();


  
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
    

  
  


    moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1000.00) * 100.00 ) );
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
