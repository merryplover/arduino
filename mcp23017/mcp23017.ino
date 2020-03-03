#include <I2CLiquidCrystal.h>
#include <mglcd.h>


#include <Wire.h>
#include <MsTimer2.h>
#include <I2CLiquidCrystal.h>
I2CLiquidCrystal lcd(30, (bool)false);
// デバイスアドレス(スレーブ)
uint8_t DEVICE_ADDRESS = 0x27;  // 2進 100000
byte sw,enc;
int led;
int timer_on=0;
byte enc_A_val,enc_B_val; 
byte enc_C_val,enc_D_val;  

void flash() {
  static boolean output = HIGH;
  digitalWrite(13, output);
  output = !output;
  timer_on=1;
}

void setup() {
  pinMode(13, OUTPUT);
  MsTimer2::set(10, flash); // 500msごとにオンオフ
  MsTimer2::start();
  
  Wire.begin();     // マスタとしてI2Cバスに接続する    
 
  // 初期設定(IODIRA/IODIRB)
  Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x00);  // 先頭アドレスへ
    Wire.write(0xf0);  // I/O設定A4～7を入力設定にする
    Wire.write(0xff);  // I/O設定Bの全てを入力設定にする  
  Wire.endTransmission();
 
  // GPIOA(GPA0～GPA7)
  Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x12);
    Wire.write(0x00);// 全てのGPAピンをLOW(出力)にする-----
  Wire.endTransmission();  

  lcd.begin(16, 2);
  Serial.begin(9600); 
}
 
void loop() {

    
  if (timer_on == 1) {
    //-------------sw-----------------------
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x12);
    Wire.endTransmission();
    Wire.requestFrom(DEVICE_ADDRESS, 1);     // 読み出すアドレスを指定する
    while(Wire.available())  {   // 要求より短いデータが来る可能性あり
      sw=Wire.read();     // 読み出す 
    }
    //-------------led-----------------------
    led=0;
    if ((sw & 16) == 0) {
      led=led+8;
    }
    if ((sw & 32) == 0) {
      led=led+4;
    }
    if ((sw & 64) == 0) {
      led=led+2;
    }
    if ((sw & 128) == 0) {
      led=led+1;
    }
    led=led+240;
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x12); 
    Wire.write(led);//2進 00001000-----
    Wire.endTransmission();
    
    //-------------encoder-----------------------
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x13);
    Wire.endTransmission();
    Wire.requestFrom(DEVICE_ADDRESS, 1);     // 読み出すアドレスを指定する
    while(Wire.available())  {   // 要求より短いデータが来る可能性あり
      enc=Wire.read();     // 読み出す 
    }
    //----------------------------------------------------------ENC_A

    if ((enc & 1)==0) {
      enc_A_val = enc_A_val &= B11111101;
    }else{
      enc_A_val = enc_A_val |= B00000010;
    }
    if ((enc & 2)==0) {
      enc_A_val = enc_A_val &= B11111110;
    }else{
      enc_A_val = enc_A_val |= B00000001;
    }
    switch(enc_A_val){
    case B00000001:break;
    case B00000111:break;
    case B00001110:
          Serial.println("RightA ");
          break;
    case B00001000:break;
    
    case B00000010:break;
    case B00001011:break;
    case B00001101:break;
    case B00000100:
          Serial.println("LeftA ");
          break;
   default:
      break;
  }
  enc_A_val = (enc_A_val<<2) & B00001100;
    //----------------------------------------------------------
    //----------------------------------------------------------ENC_B
    if ((enc & 4)==0) {
      enc_B_val = enc_B_val &= B11111101;
    }else{
      enc_B_val = enc_B_val |= B00000010;
    }
    if ((enc & 8)==0) {
      enc_B_val = enc_B_val &= B11111110;
    }else{
      enc_B_val = enc_B_val |= B00000001;
    }
    switch(enc_B_val){
    case B00000001:break;
    case B00000111:break;
    case B00001110:
          Serial.println("RightB ");
          break;
    case B00001000:break;
    
    case B00000010:break;
    case B00001011:break;
    case B00001101:break;
    case B00000100:
          Serial.println("LeftB ");
          break;
   default:
      break;
  }
  enc_B_val = (enc_B_val<<2) & B00001100;
    //----------------------------------------------------------    
    //----------------------------------------------------------ENC_C
    if ((enc & 16)==0) {
      enc_C_val = enc_C_val &= B11111101;
    }else{
      enc_C_val = enc_C_val |= B00000010;
    }
    if ((enc & 32)==0) {
      enc_C_val = enc_C_val &= B11111110;
    }else{
      enc_C_val = enc_C_val |= B00000001;
    }
    switch(enc_C_val){
    case B00000001:break;
    case B00000111:break;
    case B00001110:
          Serial.println("RightC ");
          break;
    case B00001000:break;
    
    case B00000010:break;
    case B00001011:break;
    case B00001101:break;
    case B00000100:
          Serial.println("LeftC ");
          break;
   default:
      break;
  }
  enc_C_val = (enc_C_val<<2) & B00001100;
    //----------------------------------------------------------
    //----------------------------------------------------------ENC_D
    if ((enc & 64)==0) {
      enc_D_val = enc_D_val &= B11111101;
    }else{
      enc_D_val = enc_D_val |= B00000010;
    }
    if ((enc & 128)==0) {
      enc_D_val = enc_D_val &= B11111110;
    }else{
      enc_D_val = enc_D_val |= B00000001;
    }
    switch(enc_D_val){
    case B00000001:break;
    case B00000111:break;
    case B00001110:
          Serial.println("RightD ");
          break;
    case B00001000:break;
    
    case B00000010:break;
    case B00001011:break;
    case B00001101:break;
    case B00000100:
          Serial.println("LeftD ");
          break;
   default:
      break;
  }
  enc_D_val = (enc_D_val<<2) & B00001100;
    //----------------------------------------------------------
    timer_on=0;
  }
    lcd.setCursor(0, 0);
  lcd.print("Bloco Mikusamba");

  lcd.setCursor(2, 1);
  lcd.print("plover diretor");
}  
 
