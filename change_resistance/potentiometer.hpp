#pragma once

#include "Pin_Assignments.h"

struct pot_i2c {
  int addr;
  int entire_steps;
  float entire_resistance; // kOhm
  unsigned int wiper_pos;
};

typedef struct  {
  int pin_cs;
  int entire_steps;
  float entire_resistance; // kOhm
  int buf_size;
  unsigned int wiper_pos;
} pot_spi;

enum spimode {
  set_position, // Write Wiper Register
  save_position, // Copy Wiper Register to NV Register
  load_position // Copy NV Register to Wiper Register
};


pot_i2c q_i2c; // AD5243BRMZ10
//q_i2c.addr                = 0x2F;
//q_i2c.entire_steps        = 256;
//q_i2c.entire_resistance   = 10.0;
// TODO: position初期化する？

pot_i2c f_i2c; // AD5248BRMZ10
//f_i2c.addr                = 0x2C;
//f_i2c.entire_steps        = 256;
//f_i2c.entire_resistance   = 10.0;
// TODO: position初期化する？

pot_spi f_spi1; // MAX5483EUD+T
//f_spi1.pin_cs             = pin_spi_nCS1;
//f_spi1.entire_steps       = 1024;
//f_spi1.entire_resistance  = 10.0;
//f_spi1.buf_size           = 24;
// TODO: position初期化する？

pot_spi f_spi2; // MAX5483EUD+T
//f_spi2.pin_cs             = pin_spi_nCS2;
//f_spi2.entire_steps       = 1024;
//f_spi2.entire_resistance  = 10.0;
//f_spi1.buf_size           = 24;   // ここはf_spi2 ?
// TODO: position初期化する？

void setup_potentiometer() {
  q_i2c.addr                = 0x2F;
  q_i2c.entire_steps        = 256;
  q_i2c.entire_resistance   = 10.0;

  f_i2c.addr                = 0x2C;
  f_i2c.entire_steps        = 256;
  f_i2c.entire_resistance   = 10.0;

  f_spi1.pin_cs             = pin_spi_nCS1;
  f_spi1.entire_steps       = 1024;
  f_spi1.entire_resistance  = 10.0;
  f_spi1.buf_size           = 24;

  f_spi2.pin_cs             = pin_spi_nCS2;
  f_spi2.entire_steps       = 1024;
  f_spi2.entire_resistance  = 10.0;
  f_spi2.buf_size           = 24;   // ここはf_spi2 ?

}
