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
lcd.clear();
lcd.setCursor(0,0);// set the cursor on the first row and column
   lcd.print("Humidity=");
   lcd.print((float)dht.readHumidity());//print the humidity
   lcd.print("%");
   lcd.setCursor(0,1);//set the cursor on the second row and first column
   lcd.print("Temp=");
   lcd.print((float)dht.readTemperature());//print the temperature
   lcd.print("Celsius");
   delay(2000);
   lcd.clear();
   if ( dht.readHumidity() >= 20 )
  {
    digitalWrite(LED1, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }

   

}
