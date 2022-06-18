
/* test of totary encoder
 *  
 *  # Arduinoとの接続:
 *  5V
 *  GND
 *  ## ロータリーエンコーダ
 *    A相→digital 2 pin
 *    B相→digital 3 pin
 *  ## デジタルポテンショメータ
 *    1. VDD
 *    2. B端子→GND
 *    3. SCL→A5
 *    4. SDA→A4
 *    5. W端子→デバッグ用に、10kΩ抵抗を介してArduino A0に接続。
 *    6. A端子→デバッグ用に5Vに接続。
 *    
 *  
 *  
 *  used rotary encoder: https://akizukidenshi.com/catalog/g/gP-00292/
 *  ref for program: http://219.117.208.26/~saka/ham/rotary_encoder/
 *  ref for circuit: https://monorepi.jp/archives/1440
 *  
 *  used digital potentiometer: MCP4018T-103E/LT https://akizukidenshi.com/catalog/g/gI-07610/
 *  ref: https://www.shujima.work/entry/2018/10/07/221909
 *  I2C address: ‘0101111’ or '0x2F'
 *  
 *  devwholeブランチでは、全てinoファイルでとりあえず作る。Arduinoライブラリ化は二の次。
 */

#include <Wire.h>

// rotary encoder
//// pin difinition
#define pin_a 2
#define pin_b 3
//// define rotate directions
#define d_still 0
#define d_right 1
#define d_left  2

// digital potentiometer
//// pin difinition
#define pin_monitor_r 0

// variables for rotary_encoder
int a = 0;          // A相の値
int b = 0;          // B相の値
int previous_a = 0; // 過去のA相の値
int previous_b = 0; // 過去のB相の値
byte rotate_direction = d_still; // ロータリーエンコーダの回転方向。判定結果を入れる。
boolean flag_interrupt = false;  // 割り込みがあったときのフラグ




void setup() {
  setup_rotary_encoder();
  setup_digital_potentiometer();
  Serial.begin(9600);
  Wire.begin();
  
}

void loop() {
  if (flag_interrupt == true) {
    switch (rotate_direction) {
      case d_still:
        debug_println("still");
        break;
      case d_right:
        debug_println("right");
        break;
      case d_left:
        debug_println("left");
        break;
    }
    flag_interrupt = false;
  }

  loop_set_resistance();
}
