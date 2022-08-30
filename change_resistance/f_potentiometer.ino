/*
 * 
 */
#ifndef INCLUDED_Wire_h_
#include <Wire.h>
#endif
#ifndef INCLUDED_SPI_h_
#include <SPI.h>
#endif
#ifndef INCLUDED_potentiometer_h_
#include "potentiometer.h"
#endif



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
  SPI.beginTransaction(SPISettings(7000000, MSBFIRST, SPI_MODE3));

  num_potentiometer = 0;
}

// set resistance of a digital potentiometer supporting I2C.
// addr_cs: I2C address.
// num:     step count to set.
void set_resistance_i2c(pot_i2c *pot, unsigned int wiper_pos) {
// void set_resistance_i2c() { // FIXME: unknown error 
  pot->wiper_pos = wiper_pos;
  i2c_write(pot->addr, wiper_pos);

  debug_println("[func] set_resistance_i2c ");
  debug_print(wiper_pos);
  debug_print(" (");
  debug_print(wiper_pos / (pot->entire_steps-1.0) * pot->entire_resistance);
  debug_println(" k Ohm)");
  return;
}

// set resistance of a digital potentiometer supporting SPI.
// pin_cs: digital pin for Chip Select
// num: step count to set.
void set_resistance_spi(pot_spi *pot, unsigned int wiper_pos, enum spimode mode) {
// void set_resistance_spi() {
  byte buf[3];
  digitalWrite(pot->pin_cs, LOW);

  switch (mode) {
    case set_position:
      pot->wiper_pos = wiper_pos;
      buf[0] = 0x00;
      buf[1] = (wiper_pos & 0x003F) >> 2;
      buf[2] = (wiper_pos & 0x0003) << 6;
      break;
    case save_position:
      buf[0] = 0x20;
      buf[1] = 0x00;
      buf[2] = 0x00;
      break;
    case load_position:
      buf[0] = 0x30;
      buf[1] = 0x00;
      buf[2] = 0x00;
      break;
  }
  SPI.transfer(buf,24); // MAX5483EUD+TのSPI通信は24bit

  debug_println("[func] set_resistance_spi ");
  debug_print(wiper_pos);
  debug_print(" (");
  debug_print(wiper_pos / (pot->entire_steps - 1.0) * pot->entire_resistance);
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

  // set_resistance(i);// エラーメッセージうっとうしいのでコメントアウトしただけ
  get_resistance();
  i += 1;
  
  // if (i >= potentio_steps) {
  //   i = 0;
  // } // エラーメッセージうっとうしいのでコメントアウトしただけ
  delay(100);
}
