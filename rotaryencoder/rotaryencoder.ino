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
// pin difinition
#define pin_a 2
#define pin_b 3

// define rotate directions
#define d_still 0
#define d_right 1
#define d_left  2

int a = 0;          // A相の値
int b = 0;          // B相の値
int previous_a = 0; // 過去のA相の値
int previous_b = 0; // 過去のB相の値
byte rotate_direction = d_still; // ロータリーエンコーダの回転方向。判定結果を入れる。
boolean flag_interrupt = false;  // 割り込みがあったときのフラグ



void when_interrupt() {
  flag_interrupt = true;
  a = digitalRead(pin_a);
  b = digitalRead(pin_b);

  // judge the direction of rotation
  int temp_num = (8*previous_b) + (4*previous_a) + (2*b) + (1*a);
  switch (temp_num) {
    case 1:
    case 7:
    case 8:
    case 14:
      rotate_direction = d_right;
      break;
    case 2:
    case 4:
    case 11:
    case 13:
      rotate_direction = d_left;
      break;
    default:
      rotate_direction = d_still;
      break;
  }
  
  // update previous values
  previous_a = a;
  previous_b = b;
}

void setup() {
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
