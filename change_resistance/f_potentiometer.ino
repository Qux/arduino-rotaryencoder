/*
 * 
 */



void setup_digital_potentiometer() {
  pinMode(A0, INPUT);
  // TODO: setup I2C. I2C address is fixed at 0x2F

}

void set_resistance(int num) {
  Wire.beginTransmission(0x2F);
  Wire.write(num);
  Wire.endTransmission();

  debug_print("resistance set (");
  debug_print(num / 127.0 * 10.0);
  debug_println(" k Ohm)");
}

void get_resistance() { // TODO: change type into int and return a value
  int r = analogRead(pin_monitor_r);
  debug_print("analogRead = ");
  debug_print(r);
  debug_print(" ( ");
  debug_print(r / 1024.0 * 5.0);
  debug_println(" [V]");
}

void loop_set_resistance() {
  static int i = 10; // WARN: static
  set_resistance(i);
  get_resistance();
  i += 10;
  
  if (i >= 1200) {
    i = 0;
  }
  delay(500);
}
