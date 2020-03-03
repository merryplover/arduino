//Board	I2C / TWI pins
//Uno, Ethernet	A4 (SDA), A5 (SCL)
//Mega2560	20 (SDA), 21 (SCL)
//Leonardo	2 (SDA), 3 (SCL)
//Due	20 (SDA), 21 (SCL), SDA1, SCL1

#include <I2CLiquidCrystal.h>
#include <Wire.h>

I2CLiquidCrystal lcd(63, (bool)true);

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.setCursor(4, 1);
  lcd.print("Arduino UNO");
  delay(1000);
  lcd.clear();
  delay(1000);
}
