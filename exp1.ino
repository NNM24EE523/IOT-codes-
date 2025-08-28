#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  

  
}
void loop(){
  for(int i=0;i<=10;i++){
    lcd.print("akshith");
    
    delay(1000);
  }
  while(1);

 }
  

