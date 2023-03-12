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

  if (current_keycode == KC_D)
  { // カーソル移動
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

  if (current_keycode == KC_T)
  { // フリック風
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