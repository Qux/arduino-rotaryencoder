/*
 * 
 */



void setup_digital_potentiometer() {
  pinMode(A0, INPUT);
  num_potentiometer = 0;
}

void set_resistance(int num) {
  i2c_write(i2c_addr_MCP4018, num);

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
