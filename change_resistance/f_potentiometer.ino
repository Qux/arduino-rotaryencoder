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
f_spi1.pin_cs             = 10;
f_spi1.entire_steps       = 1024;
f_spi1.entire_resistance  = 10.0;
pot_spi f_spi2;
f_spi2.pin_cs             = 8;
f_spi2.entire_steps       = 1024;
f_spi2.entire_resistance  = 10.0;


void setup_digital_potentiometer() {
  // pinMode(A0, INPUT); // for debug
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  num_potentiometer = 0;
}

// set resistance of a digital potentiometer.
// This covers both of I2C and SPI.
// i2c_spi: 1->i2c, 0->spi
// addr_cs: I2C address or CS for SPI.
// num:     step count to set of potentiometer.
void set_resistance(bool i2c_spi, int addr_cs,int num) {
  if (i2c_spi == true) {
    i2c_write(addr_cs, num);
  } else {
    // TODO: SPI
  }

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
