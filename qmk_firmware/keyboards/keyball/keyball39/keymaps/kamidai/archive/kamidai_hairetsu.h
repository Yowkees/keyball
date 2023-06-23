/* Copyright 2023 kamidai (@d_kamiichi)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// F
if (current_keycode == KC_F)
{ //
  if (my_abs(x) > my_abs(y))
  {
    // is_repeat = false;

    if (x < 0)
    { // swipe left
      tap_code(KC_N);
      tap_code(KC_I);
    }
    else
    { // swipe right
      tap_code(KC_M);
      tap_code(KC_E);
    }
  }

  if (my_abs(x) < my_abs(y))
  {
    if (y < 0)
    { // swipe up
      tap_code(KC_K);
      tap_code(KC_A);
    }
    else
    { // swipe down
      tap_code(KC_W);
      tap_code(KC_O);
    }
    // is_repeat = true;
  }
}

// D
if (current_keycode == KC_D)
{ //
  if (my_abs(x) > my_abs(y))
  {
    // is_repeat = false;

    if (x < 0)
    { // swipe left
      tap_code(KC_T);
      tap_code(KC_O);
    }
    else
    { // swipe right
      tap_code(KC_R);
      tap_code(KC_E);
    }
  }

  if (my_abs(x) < my_abs(y))
  {
    if (y < 0)
    { // swipe up
      tap_code(KC_M);
      tap_code(KC_O);
    }
    else
    { // swipe down
      tap_code(KC_N);
      tap_code(KC_O);
    }
    // is_repeat = true;
  }
}

// S
if (current_keycode == KC_S)
{ //
  if (my_abs(x) > my_abs(y))
  {
    // is_repeat = false;

    if (x < 0)
    { // swipe left
      tap_code(KC_R);
      tap_code(KC_O);
    }
    else
    { // swipe right
      tap_code(KC_H);
      tap_code(KC_A);
    }
  }

  // if (my_abs(x) < my_abs(y))
  // {
  //   if (y < 0)
  //   { // swipe up
  //     tap_code(KC_M);
  //     tap_code(KC_O);
  //   }
  //   else
  //   { // swipe down
  //     tap_code(KC_N);
  //     tap_code(KC_O);
  //   }
  //   // is_repeat = true;
  // }
}