#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>
//#define tmp 7
#define buzer 8
LiquidCrystal lcd(13,12,11,10,9,8,7);
DHT dht(7, DHT11);

void setup() {
  dht.begin();
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(buzer, OUTPUT);
}
 
void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.println("hum:");
  Serial.println(h);
  Serial.print("%");
  Serial.println("temp:");
  Serial.println(t);
  
  lcd.setCursor(0,0);
  lcd.print("hum:");
  lcd.print(h);
  lcd.print("% ");
  lcd.setCursor(0,1);
  lcd.print("temp:");
  lcd.print(t);

  if(h >= 31){
  digitalWrite(buzer, HIGH);
  }
  else{
   digitalWrite(buzer, LOW);
  }

}
