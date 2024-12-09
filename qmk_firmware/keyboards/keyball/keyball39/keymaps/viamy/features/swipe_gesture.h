/* Copyright 2023 kamidai (@d_kamiichi)
 *
 * 参考にさせていただいたページ
 * https://www.reddit.com/r/ploopy/comments/pbmrh3/qmk_options_on_ploopy_mouse_gestures/
 * https://github.com/RobertCurry0216/qmk_firmware/blob/59f83aac8fa06010c3a1a0a53fcd453d96ce2f80/keyboards/ploopyco/trackball/keymaps/robertcurry0216/keymap.c
 *
 */

int16_t current_keycode;
const int16_t SWIPE_THRESHOLD = 10;
bool is_swiped = false;
bool is_repeat = false;

// スワイプジェスチャーで何が起こるかを実際に処理する関数
// 上、下、左、右、スワイプなしの5つのオプションがあります
void process_swipe_gesture(int16_t x, int16_t y) {
  // KC_GESTURE1
  if (current_keycode == KC_GESTURE1) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        tap_code(KC_F13);
      } else {
        // swipe down
        tap_code(KC_F14);
      }
    }
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left
        tap_code(KC_F15);
      } else {
        // swipe right
        tap_code(KC_F16);
      }
    }
  }

  // KC_GESTURE2
  if (current_keycode == KC_GESTURE2) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        tap_code(KC_F17);
      } else {
        // swipe down
        tap_code(KC_F18);
      }
    }
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left
        tap_code(KC_F19);
      } else {
        // swipe right
        tap_code(KC_F20);
      }
    }
  }

  // KC_GESTURE3
  if (current_keycode == KC_GESTURE3) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        tap_code(KC_F21);
      } else {
        // swipe down
        tap_code(KC_F22);
      }
    }
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left
        tap_code(KC_F23);
      } else {
        // swipe right
        tap_code(KC_F24);
      }
    }
  }
}