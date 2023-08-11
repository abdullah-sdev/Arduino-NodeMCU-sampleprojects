#include "DHT.h"


#define DHTPIN D3          // GPIO Pin where the dht11 is connected
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE); 
float h;                  // humidity reading
float t;       

void setup() {
    dht.begin();

}

void loop() {
   
  h = dht.readHumidity();     // read humiduty
  t = dht.readTemperature();     // read temperature
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
}
