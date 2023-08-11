#include "DHT.h"  // Including library for dht
 
#define DHTPIN 8    
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:

   Serial.begin(9600);

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
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
                 }else{
                  Serial.print("Temperature: ");
                             Serial.println(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.println(h);
                 }

                 


                 

}
