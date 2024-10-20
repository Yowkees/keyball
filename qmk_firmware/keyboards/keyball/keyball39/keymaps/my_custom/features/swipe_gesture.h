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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------
 *
 * 参考文献：
 * - 以下のリソースを参考にしました：
 *   https://www.reddit.com/r/ploopy/comments/pbmrh3/qmk_options_on_ploopy_mouse_gestures/
 *   https://github.com/RobertCurry0216/qmk_firmware/blob/59f83aac8fa06010c3a1a0a53fcd453d96ce2f80/keyboards/ploopyco/trackball/keymaps/robertcurry0216/keymap.c
 *
 */

int16_t current_keycode;
const int16_t SWIPE_THRESHOLD = 10;
bool is_swiped = false;
bool is_repeat = false;

// スワイプジェスチャーで何が起こるかを処理する関数です
// 上、下、左、右の4つのオプションがあります
void process_swipe_gesture(int16_t x, int16_t y) {
  // Alt
  if (current_keycode == ALT_T(KC_F13)) {
    unregister_code(KC_LALT);

    // 拡大と縮小
    if (my_abs(x) < my_abs(y)) {
      register_code(KC_LCMD);

      if (y < 0) {
        // swipe up: 拡大
        tap_code(KC_EQUAL);
      } else {
        // swipe down: 縮小
        tap_code(KC_MINUS);
      }
    }

    // 次のモニターへ移動
    if (my_abs(x) > my_abs(y)) {
      register_code(KC_LCTL);

      if (x < 0) {
        // swipe left:
        tap_code(KC_7);
      } else {
        // swipe right:
        tap_code(KC_7);
      }
    }
    unregister_code(KC_LCMD);
    unregister_code(KC_LCTL);

    register_code(KC_LALT);
  }

  // shift
  if (current_keycode == SFT_T(KC_LNG2)) {
    unregister_code(KC_LALT);
    register_code(KC_LCMD);

    // CMD + J
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up:
        tap_code(KC_J);
      } else {
        // swipe down:
        tap_code(KC_J);
      }
    }
    // ページの戻る、進む
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left: 戻る
        tap_code(KC_LBRC);
      } else {
        // swipe right: 進む
        tap_code(KC_RBRC);
      }
    }
    unregister_code(KC_LCMD);
    register_code(KC_LALT);
  }

  // CMD
  if (current_keycode == CMD_T(KC_SPACE)) {
    unregister_code(KC_LCMD);
    register_code(KC_LCTL);

    // ウインドウのサイズ変更と移動（BetterTouchToolで設定）
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up: ウィンドウを最大化
        tap_code(KC_8);
      } else {
        // swipe down: ウインドウを最小サイズで中央へ
        tap_code(KC_2);
      }
    }
    // ウインドウのサイズ変更と移動（BetterTouchToolで設定）
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left: ウインドウを1/2サイズで左へ
        tap_code(KC_4);
      } else {
        // swipe right: ウインドウを1/2サイズで右へ
        tap_code(KC_6);
      }
    }

    unregister_code(KC_LCTL);
    register_code(KC_LCMD);
  }

  // alt
  // if (current_keycode == KC_LALT)
  // {
  //   if (my_abs(x) > my_abs(y))
  //   { // ウインドウのサイズ変更と移動
  //     register_code(KC_LCMD);

  //     if (x > 0)
  //     { // swipe right
  //       tap_code(KC_6);
  //     }
  //     else
  //     { // swipe left
  //       tap_code(KC_4);
  //     }
  //   }

  //   if (my_abs(x) < my_abs(y))
  //   { // ウインドウのサイズ変更と移動s
  //     register_code(KC_LCMD);

  //     if (y > 0)
  //     { // swipe down
  //       tap_code(KC_2);
  //     }
  //     else
  //     { // swipe up
  //       tap_code(KC_8);
  //     }
  //   }
  // }

  // alt
  // if (current_keycode == KC_LALT)
  // { //
  //   unregister_code(KC_LALT);
  //   // register_code(KC_LCMD);
  //   register_code(KC_LCTL);

  //   if (my_abs(x) > my_abs(y))
  //   {
  //     // is_repeat = false;
  //     if (x > 0)
  //     { // swipe right
  //       // register_code16(HYPR(KC_RIGHT));
  //       // tap_code(KC_RBRC);
  //       tap_code(KC_LEFT);
  //       // unregister_code(KC_LCMD);
  //     }
  //     else
  //     { // swipe left
  //       tap_code(KC_RIGHT);
  //       // register_code16(HYPR(KC_LEFT));
  //     }
  //   }

  //   if (my_abs(x) < my_abs(y))
  //   {
  //     if (y > 0)
  //     { // swipe down
  //       // register_code(KC_LCMD);
  //       // register_code(KC_LCTL);
  //       tap_code(KC_DOWN);
  //       // unregister_code(KC_LCMD);
  //       // unregister_code(KC_LCTL);
  //     }
  //     else
  //     { // swipe up
  //       // register_code(KC_LCMD);
  //       // register_code(KC_LCTL);
  //       tap_code(KC_UP);
  //       // unregister_code(KC_LCMD);
  //       // unregister_code(KC_LCTL);
  //     }
  //     // is_repeat = true;
  //   }

  //   // unregister_code(KC_LCMD);
  //   unregister_code(KC_LCTL);
  // }

  // layer2 & a
  // if (current_keycode == LT(2, KC_A))
  // {
  //   register_code(KC_LCMD);

  //   if (my_abs(x) > my_abs(y))
  //   { // 英かな切り替え
  //     if (x > 0)
  //     { // swipe right
  //       tap_code(KC_RBRC);
  //     }
  //     else
  //     { // swipe left
  //       tap_code(KC_LBRC);
  //     }
  //   }

  //   if (my_abs(x) < my_abs(y))
  //   { // 拡大と縮小
  //     if (y > 0)
  //     { // swipe down
  //       tap_code(KC_2);
  //     }
  //     else
  //     { // swipe up
  //       tap_code(KC_1);
  //     }
  //   }
}