#define RS_PIN 4
#define E_PIN 7
#define DB4_PIN 8
#define DB5_PIN 9
#define DB6_PIN 10
#define DB7_PIN 11

#include <LiquidCrystal.h>;

LiquidCrystal lcd(RS_PIN, E_PIN, DB4_PIN, DB5_PIN, DB6_PIN, DB7_PIN);

void setup() {
  lcd.begin(20,4);
  lcd.print("(^-^*)/ hello,world!");
  delay(3000);
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  delay(100);
}
