
/* test of totary encoder
 *  
 *  # Arduinoとの接続:
 *  5V
 *  GND
 *  ## ロータリーエンコーダ
 *    A相→digital 2 pin
 *    B相→digital 3 pin
 *  ## デジタルポテンショメータ I2C
 *    1. VDD
 *    2. B端子 ->   GND
 *    3. SCL ->     A5
 *    4. SDA ->     A4
 *    5. W端子->デバッグ用に、10kΩ抵抗を介してArduino A0に接続。
 *    6. A端子->デバッグ用に5Vに接続。
 *  ## デジタルポテンショメータ SPI
 *    1. SCK ->   D13
 *    2. MISO ->  D12
 *    3. MOSI ->  D11
 *    4. nCS1 ->  D10
 *    5. nCS2 ->  D8
 *  
 *  # information about components
 *  ## rotary encoder
 *  used rotary encoder: https://akizukidenshi.com/catalog/g/gP-00292/
 *  ref for program: http://219.117.208.26/~saka/ham/rotary_encoder/
 *  ref for circuit: https://monorepi.jp/archives/1440
 *
 *  ## digital potentiometer
 *    1. Q (I2C)
 *      AD5243BRMZ10
 *      https://www.analog.com/jp/products/ad5243.html
 *    2. F (I2C)
 *      AD5248BRMZ10
 *      https://www.analog.com/jp/products/ad5248.html
 *    3. F (SPI)
 *      MAX5483EUD+T
 *      https://www.maximintegrated.com/jp/products/analog/data-converters/digital-potentiometers/MAX5483.html
 *
 *  ref for I2C: https://www.shujima.work/entry/2018/10/07/221909
 *  
 *  devwholeブランチでは、全てinoファイルでとりあえず作る。Arduinoライブラリ化は二の次。
 */

#include <Wire.h>
#include <SPI.h>

#define debug_mode 1
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
//// parameters
#define potentio_steps 128
#define entire_res 10.0 // k Ohm
#define i2c_addr_MCP4018 0x2F

// variables for rotary_encoder
volatile int a = 0;          // A相の値
volatile int b = 0;          // B相の値
volatile int previous_a = 0; // 過去のA相の値
volatile int previous_b = 0; // 過去のB相の値
volatile byte rotate_direction = d_still; // ロータリーエンコーダの回転方向。判定結果を入れる。
volatile bool flag_interrupt = false;  // 割り込みがあったときのフラグ
// variables for digital_potentiometer
int num_potentiometer = 0;



void setup() {
  setup_rotary_encoder();
  setup_digital_potentiometer();
  Serial.begin(9600);
  Wire.begin();
  SPI.begin();
}

void loop() {
  if (flag_interrupt == true) {
    num_potentiometer += interpret_rotation();
    // if num_potentiometer is out of range, adjust the number.
    if (num_potentiometer >= (potentio_steps - 1)) { 
      num_potentiometer = potentio_steps - 1;
    } else if (num_potentiometer <= 0) {
      num_potentiometer = 0;
    }
    debug_print("num_potentiometer = ");
    debug_println(num_potentiometer);

    set_resistance(num_potentiometer);
    get_resistance();
    flag_interrupt = false;
  }

  // loop_set_resistance();
}
