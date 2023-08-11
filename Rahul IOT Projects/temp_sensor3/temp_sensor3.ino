#include <DHT.h>
#include <DHT_U.h>

DHT dht(9,DHT11);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
Serial.println("Humidity: ");
Serial.print(h);
Serial.println(" %");
Serial.println("Temperature: ");
Serial.print(t);
Serial.println(" *c");
delay(1000);



}
