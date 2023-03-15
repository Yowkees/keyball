////////////////////////////////////
///
/// 参考にさせていただいたページ
/// https://www.reddit.com/r/ploopy/comments/pbmrh3/qmk_options_on_ploopy_mouse_gestures/
/// https://github.com/RobertCurry0216/qmk_firmware/blob/59f83aac8fa06010c3a1a0a53fcd453d96ce2f80/keyboards/ploopyco/trackball/keymaps/robertcurry0216/keymap.c
///
////////////////////////////////////

int16_t current_keycode;
const int16_t SWIPE_THRESHOLD = 10;
bool is_swiped = false;
bool is_repeat = false;

// スワイプジェスチャーで何が起こるかを実際に処理する関数です
// 上、下、左、右、スワイプなしの5つのオプションがあります
void process_swipe_gesture(int16_t x, int16_t y)
{
  // LCMD
  if (current_keycode == KC_LCMD)
  {
    if (my_abs(x) > my_abs(y))
    { // 英かな切り替え
      unregister_code(KC_LCMD);

      if (x > 0)
      { // swipe right
        tap_code(KC_LANG1);
      }
      else
      { // swipe left
        tap_code(KC_LANG2);
      }
    }

    if (my_abs(x) < my_abs(y))
    { // 拡大と縮小
      if (y > 0)
      { // swipe down
        tap_code(KC_MINUS);
      }
      else
      { // swipe up
        tap_code(KC_EQUAL);
      }
    }
  }

  // D
  if (current_keycode == KC_LALT)
  { //
    unregister_code(KC_LALT);

    if (my_abs(x) > my_abs(y))
    {
      // is_repeat = false;

      if (x > 0)
      { // swipe right
        register_code(KC_LCMD);
        tap_code(KC_RBRACKET);
        unregister_code(KC_LCMD);
      }
      else
      { // swipe left
        register_code(KC_LCMD);
        tap_code(KC_LBRACKET);
        unregister_code(KC_LCMD);
      }
    }

    if (my_abs(x) < my_abs(y))
    {
      if (y > 0)
      { // swipe down
        register_code(KC_LCMD);
        tap_code(KC_2);
        unregister_code(KC_LCMD);
      }
      else
      { // swipe up
        register_code(KC_LCMD);
        tap_code(KC_1);
        unregister_code(KC_LCMD);
      }
      // is_repeat = true;
    }
  }
  // S
  if (current_keycode == KC_S)
  {
    tap_code(KC_BSPC);

    if (my_abs(x) > my_abs(y))
    {
      if (x > 0)
      { // swipe right
        tap_code(KC_RBRACKET);
      }

      else
      { // swipe left
        tap_code(KC_LBRACKET);
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