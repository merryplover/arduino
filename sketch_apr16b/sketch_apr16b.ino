#include <util/delay.h>
#define SYNC  (PORTB=B00000000)
#define WHITE (PORTB=B00000011)
#define BLACK (PORTB=B00000001)
#define GRAY  (PORTB=B00000010)

//水平同期信号
void hsync(){
  SYNC;
  _delay_us(5);
  BLACK;
  _delay_us(7);
}

//垂直同期信号
void vsync(){
  SYNC;
  _delay_us(25);
  BLACK;
  _delay_us(5);
}

void setup(){
  //8,9番ピンをデジタル出力に設定
  //DDRB=B00000011; //でも可
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);  

  //割り込み禁止
  //noInterrupts(); //でも可
  cli();
}

int count=1;//走査線を数える変数

void loop(){
  if(count>=3 && count<=5){
    vsync();//垂直同期信号２回送信
    vsync();
  }else if(count>=5&&count<100){
    hsync();    //水平同期信号
    BLACK;      //矩形の上部背景描画
   _delay_us(48);
  }else if(count>200){
    hsync();    //水平同期信号
    BLACK;      //矩形の下部背景描画
   _delay_us(48);
  }else{        
    hsync();    //水平同期信号
    BLACK;      //矩形の左側背景描画
    _delay_us(20);
    WHITE;      //矩形の描画
    _delay_us(8);
    BLACK;      //矩形の右側背景描画
    _delay_us(20);
  }
  count++;      //走査線の数をカウントアップ
  if(count>262){//走査線が画面下端へ行ったら
    count=1;    //一番目の走査線に戻る
  }
}
