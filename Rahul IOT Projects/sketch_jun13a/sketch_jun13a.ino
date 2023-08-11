#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

LiquidCrystal lcd(9,8,7,6,5,4);
DHT dht(10, DHT11);

void setup() {
  dht.begin();
  lcd.begin(16,2);

}
 
void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("hum:");
  lcd.print(h);
  lcd.print("% ");
  lcd.setCursor(0,1);
  lcd.print("temp:");
  lcd.print(t);
}
