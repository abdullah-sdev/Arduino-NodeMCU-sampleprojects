#include<LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(7, DHT11);

void setup()
{
 lcd.begin(16, 2);
 Serial.begin(9600); 
}

void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //lcd.setCursor(0,0);
  //lcd.print("hum:");
  //lcd.print(h);
  Serial.println(h);
  //lcd.print("% ");
  //lcd.setCursor(0,1);
  //lcd.print("temp:");
  //lcd.print(t);
  Serial.println(t);
}
