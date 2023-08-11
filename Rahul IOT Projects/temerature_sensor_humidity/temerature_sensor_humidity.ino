#include <DHT.h>
#include <DHT_U.h>
#include<LiquidCrystal.h>
const int LED1 = 6;


DHT dht(9,DHT11);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600);
lcd.begin(16, 2);
dht.begin();
Serial.begin(9600);
pinMode(LED1 , OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
//lcd.clear();
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if ( dht.readHumidity() >= 70 )
  {
    digitalWrite(LED1, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }

  lcd.setCursor(0,0);
  lcd.print("hum:");
  lcd.print(h);
  lcd.print("% ");
  lcd.setCursor(0,1);
  lcd.print("temp:");
  lcd.print(t);
  


//   lcd.clear();
   
   

}
