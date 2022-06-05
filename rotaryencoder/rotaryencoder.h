/* test of totary encoder
 *  
 *  Arduinoとの接続:
 *  5V
 *  GND
 *  ロータリーエンコーダA相→digital 2 pin
 *  ロータリーエンコーダB相→digital 3 pin
 *  
 *  used rotary encoder: https://akizukidenshi.com/catalog/g/gP-00292/
 *  ref for program: http://219.117.208.26/~saka/ham/rotary_encoder/
 *  ref for circuit: https://monorepi.jp/archives/1440
 */

#ifndef ROTARY_ENCODER
#define ROTARY_ENCODER
#include "Arduino.h"

// pin difinition
#define pin_a 2 // TODO value should be determined according to the board type
#define pin_b 3

// define rotate directions
#define d_still 0
#define d_right 1
#define d_left  2

int a;          // A相の値
int b;          // B相の値
int previous_a; // 過去のA相の値
int previous_b; // 過去のB相の値
byte rotate_direction; // ロータリーエンコーダの回転方向。判定結果を入れる。
boolean flag_interrupt;  // 割り込みがあったときのフラグ

void setup_re();
void when_interrupt();

#endif

