void debug_print(String s)   { 
    if (debug_mode) Serial.print(s);
}
void debug_println(String s) { 
    if (debug_mode) Serial.println(s);
}
void debug_print(int s)   {
    if (debug_mode) Serial.print(s);
}
void debug_println(int s) { 
    if (debug_mode) Serial.println(s);
}
void debug_print(float s)   { 
    if (debug_mode) Serial.print(s);
}
void debug_println(float s) { 
    if (debug_mode) Serial.println(s);
}
void debug_print(double s)   { 
    if (debug_mode) Serial.print(s);
}
void debug_println(double s) {
    if (debug_mode) Serial.println(s);
}

void i2c_write(int i2c_addr, int num) {
    Wire.beginTransmission(i2c_addr);
    Wire.write(num);
    Wire.endTransmission();
}
