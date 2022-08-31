void setup_rotary_encoder() {
  a = 0;          // A相の値
  b = 0;          // B相の値
  previous_a = 0; // 過去のA相の値
  previous_b = 0; // 過去のB相の値
  rotate_direction = d_still; // ロータリーエンコーダの回転方向。判定結果を入れる。
  flag_interrupt = false;  // 割り込みがあったときのフラグ

  attachInterrupt(0, when_interrupt, CHANGE); // pin2(a)
  attachInterrupt(1, when_interrupt, CHANGE); // pin3(b)
}

void when_interrupt() {
  flag_interrupt = true;
  a = digitalRead(pin_a);
  b = digitalRead(pin_b);

  // judge the direction of rotation
  volatile int temp_num = (8*previous_b) + (4*previous_a) + (2*b) + (1*a);
  switch (temp_num) {
    case 1:
    case 7:
    case 8:
    case 14:
      rotate_direction = d_left;
      break;
    case 2:
    case 4:
    case 11:
    case 13:
      rotate_direction = d_right;
      break;
    default:
      rotate_direction = d_still;
      break;
  }
  
  // update previous values
  previous_a = a;
  previous_b = b;
}

int interpret_rotation() {
    switch (rotate_direction) {
      case d_still:
        debug_println("still");
        return 0;
        break;
      case d_right:
        debug_println("right");
        return 1;
        break;
      case d_left:
        debug_println("left");
        return -1;
        break;
    }
}
