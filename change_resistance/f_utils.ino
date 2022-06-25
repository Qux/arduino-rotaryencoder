void debug_print(String s)   { Serial.print(s); }
void debug_println(String s) { Serial.println(s); }
void debug_print(int s)   { Serial.print(s); }
void debug_println(int s) { Serial.println(s); }
void debug_print(float s)   { Serial.print(s); }
void debug_println(float s) { Serial.println(s); }
void debug_print(double s)   { Serial.print(s); }
void debug_println(double s) { Serial.println(s); }

void i2c_write(int i2c_addr, int num) {
    Wire.beginTransmission(i2c_addr);
    Wire.write(num);
    Wire.endTransmission();
}
