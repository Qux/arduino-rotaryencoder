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
#include "rotaryencoder.h"

void setup() {
  setup_re();
  Serial.begin(9600);

  attachInterrupt(0, when_interrupt, CHANGE); // pin2(a)
  attachInterrupt(1, when_interrupt, CHANGE); // pin3(b)
  
}

void loop() {
  if (flag_interrupt == true) {
    switch (rotate_direction) {
      case d_still:
        Serial.println("still");
        break;
      case d_right:
        Serial.println("right");
        break;
      case d_left:
        Serial.println("left");
        break;
    }
    flag_interrupt = false;
  }
}
