/*
 * 
 */

typedef struct potentiometer_i2c {
  int addr;
  int entire_steps;
  float entire_resistance; // kOhm
} pot_i2c;

typedef struct potentiometer_spi {
  int pin_cs;
  int entire_steps;
  float entire_resistance; // kOhm
} pot_spi;

pot_i2c q_i2c; // AD5243BRMZ10
q_i2c.addr                = 0x2F;
q_i2c.entire_steps        = 256;
q_i2c.entire_resistance   = 10.0;
pot_i2c f_i2c;
f_i2c.addr                = 0x2C;
f_i2c.entire_steps        = 256;
f_i2c.entire_resistance   = 10.0;
pot_spi f_spi1;
f_spi1.pin_cs             = pin_spi_nCS1;
f_spi1.entire_steps       = 1024;
f_spi1.entire_resistance  = 10.0;
pot_spi f_spi2;
f_spi2.pin_cs             = pin_spi_nCS2;
f_spi2.entire_steps       = 1024;
f_spi2.entire_resistance  = 10.0;


void setup_digital_potentiometer() {
  // pinMode(A0, INPUT); // for debug
  // spi
  pinMode(f_spi2.pin_cs, OUTPUT);
  pinMode(f_spi1.pin_cs, OUTPUT);
  pinMode(pin_spi_mosi, OUTPUT);
  pinMode(pin_spi_miso, OUTPUT);
  pinMode(pin_spi_sck, OUTPUT);
  digitalWrite(f_spi1.pin_cs, HIGH);
  digitalWrite(f_spi2.pin_cs, HIGH);
  SPI.beginTransaction(SPIsettings(7000000, MSBFIRST, SPI_MODE3));

  num_potentiometer = 0;
}

// set resistance of a digital potentiometer supporting I2C.
// addr_cs: I2C address.
// num:     step count to set.
void set_resistance_i2c(int addr,int num) {
  i2c_write(addr, num);

  debug_print("resistance set ");
  debug_print(num);
  debug_print(" (");
  debug_print(num / (potentio_steps-1.0) * entire_res);
  debug_println(" k Ohm)");
}

// set resistance of a digital potentiometer supporting SPI.
// pin_cs: digital pin for Chip Select
// num: step count to set.
// mode: 0 -> set without storing position, 1 -> set with storing position, 2 -> load stored position.
void set_resistance_spi(int pin_cs,int num, int mode) {
  digitalWrite(pin_cs, LOW);

// TODO: modeによる場合分け
  SPI.transfer(buffer,size);// TODO: ちゃんと書く。24bit送受信が必要。

  debug_print("resistance set ");
  debug_print(num);
  debug_print(" (");
  debug_print(num / (potentio_steps-1.0) * entire_res);
  debug_println(" k Ohm)");
}


void get_resistance() { // TODO: change type into int and return a value
  int r = analogRead(pin_monitor_r);
  debug_print("analogRead = ");
  debug_print(r);
  debug_print(" ( ");
  debug_print(r / 1023.0 * 5.0);
  debug_println(" [V]");
}

void loop_set_resistance() {
  static int i = 0; // WARN: static

  debug_print("\n[debug] i = ");
  debug_println(i);

  set_resistance(i);
  get_resistance();
  i += 1;
  
  if (i >= potentio_steps) {
    i = 0;
  }
  delay(100);
}
