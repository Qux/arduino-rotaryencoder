#include <Arduino.h>
#include "rotaryencoder.h"


void when_interrupt() {
  flag_interrupt = true;
  a = digitalRead(pin_a);
  b = digitalRead(pin_b);

  // judge the direction of rotation
  int temp_num = (8*previous_b) + (4*previous_a) + (2*b) + (1*a);
  switch (temp_num) {
    case 1:
    case 7:
    case 8:
    case 14:
      rotate_direction = d_right;
      break;
    case 2:
    case 4:
    case 11:
    case 13:
      rotate_direction = d_left;
      break;
    default:
      rotate_direction = d_still;
      break;
  }
  
  // update previous values
  previous_a = a;
  previous_b = b;
}
