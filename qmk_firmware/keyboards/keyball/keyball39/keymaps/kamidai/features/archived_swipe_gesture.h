void process_swipe_gesture(int16_t x, int16_t y)
{
  // カーソル移動
  if (current_keycode == KC_D)
  {
    if (my_abs(x) > my_abs(y))
    {
      if (x > 0)
      { // swipe right
        tap_code(KC_RIGHT);
      }
      else
      { // swipe left
        tap_code(KC_LEFT);
      }
    }

    if (my_abs(x) < my_abs(y))
    {
      if (y > 0)
      { // swipe down
        tap_code(KC_DOWN);
      }
      else
      { // swipe up
        tap_code(KC_UP);
      }
    }
  }

  // フリック風
  if (current_keycode == KC_T)
  {
    tap_code(KC_BSPC);

    if (my_abs(x) > my_abs(y))
    {
      if (x > 0)
      { // swipe right
        tap_code(KC_S);
      }

      else
      { // swipe left
        tap_code(KC_W);
      }
    }

    if (my_abs(x) < my_abs(y))
    {
      if (y > 0)
      { // swipe down
        tap_code(KC_V);
      }
      else
      { // swipe up
        tap_code(KC_H);
      }
    }
  }
}