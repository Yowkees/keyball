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