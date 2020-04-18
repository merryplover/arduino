
//ディレイのライブラリを取り込む
#include <util/delay.h>
//同期信号、三色の出力を設定、定義しておく
#define SYNC  (PORTB=B00000000)
#define WHITE (PORTB=B00000011)
#define BLACK (PORTB=B00000001)
#define GRAY  (PORTB=B00000010)

void setup(){
  //8番と9番ピンをデジタル出力に設定
  //DDRB=B00000011;と書くことも可能
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  //割り込み禁止設定
  noInterrupts();
}
void loop(){
  //同期、前後余白の設定
  BLACK;
  _delay_us(2);
  SYNC;
  _delay_us(5);
  BLACK;
  _delay_us(5);

  //画面表示
  WHITE;
  _delay_us(17);
  BLACK;
  _delay_us(17);
  GRAY;
  _delay_us(17);
}
