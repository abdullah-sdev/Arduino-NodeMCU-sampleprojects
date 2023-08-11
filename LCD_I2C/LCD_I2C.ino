 #include <Wire.h>  // library for I2C protocol  
 #include <LiquidCrystal_I2C.h> // library for I2C LCD  
 LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display 
 int thisChar = 'a'; 
 void setup()  
 {  
  lcd.init();    // initialize the lcd   
  lcd.backlight(); // backlight ON  
//  lcd.print("voidloopRobotech");  
//  lcd.setCursor(2,1);  
//  lcd.print("Automation");  
 }  
 void loop()  
 {  
    // reverse directions at 'm':
  if (thisChar == 'm') {
    // go right for the next letter
    lcd.rightToLeft();
  }
  // reverse again at 's':
  if (thisChar == 's') {
    // go left for the next letter
    lcd.leftToRight();
  }
  // reset at 'z':
  if (thisChar > 'z') {
    // go to (0,0):
    lcd.home();
    // start again at 0
    thisChar = 'a';
  }
  // print the character
  lcd.print(thisChar);
  // wait a second:
  delay(1000);
  // increment the letter:
  thisChar++;
 }  
