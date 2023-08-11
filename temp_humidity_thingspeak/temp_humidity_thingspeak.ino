#include "DHT.h"  // Including library for dht
 
#include <ESP8266WiFi.h>
 
String apiKey = "ZA3KDUZAKYCZM2UP";     //  Enter your Write API key from ThingSpeak
 
const char* ssid =  "HUAWEI-5WRD";     // replace with your wifi ssid and wpa2 key
const char* pass =  "f7t78d6K";
const char* server = "api.thingspeak.com";
 
#define DHTPIN D3     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
//       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {

                    if (isnan(h))
                    {
                      Serial.println("humidity prblm");
                      
                    }
                    if (isnan(t))
                    {
                      Serial.println("temp prblm");
                      
                    }
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(h);
                             postStr +="&field2=";
                             postStr += String(t);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
