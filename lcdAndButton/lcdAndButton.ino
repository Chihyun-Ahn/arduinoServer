#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int upButtonPin = 7;
int selectButtonPin = 6;
int downButtonPin = 5;

void setup()
{
  lcd.begin();
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
}

void loop()
{
  lcd.setCursor(1,1);
  lcd.clear();
  lcd.print("Ready");
  if(digitalRead(upButtonPin)==LOW){
    lcd.clear();
    lcd.print("Up btn pressed!");
  }
  if(digitalRead(downButtonPin)==LOW){
    lcd.clear();
    lcd.print("Down btn pressed!");
  }
  if(digitalRead(selectButtonPin)==LOW){
    lcd.clear();
    lcd.print("Select btn pressed!");
  }
  delay(200);

  
//  lcd.setCursor(5,0);
//  lcd.print("Hi ^^");
//  delay(1000);
//  lcd.setCursor(3,1);
//  lcd.print("Codingrun");
//  delay(1000);
//  lcd.clear();
//  delay(1000);
}
