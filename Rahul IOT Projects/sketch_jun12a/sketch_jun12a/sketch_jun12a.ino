void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
 lcd.begin(16, 2);
 Serial.begin(9600); 
}

void loop()
{
  lcd.setCursor(3,0);          
  lcd.print("RAHUL RAI"); 
  lcd.setCursor(1,1);           
  lcd.print("MUSKAN WASHDEV");    
  }
