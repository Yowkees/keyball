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

  // #include "features/kamidai_hairetsu.h"

  // Command
  if (current_keycode == LCMD_T(KC_SPACE))
  {
    if (my_abs(x) > my_abs(y))
    { // 音声入力とsiri
      unregister_code(KC_LCMD);

      if (x < 0)
      { // swipe left: 音声入力
        tap_code(KC_F5);
      }
      else
      { // swipe right: siri
        register_code(KC_F5);
      }
    }

    if (my_abs(x) < my_abs(y))
    { // 拡大と縮小
      register_code(KC_LCMD);

      if (y < 0)
      { // swipe up: 拡大
        tap_code(KC_EQUAL);
      }
      else
      { // swipe down: 縮小
        tap_code(KC_MINUS);
      }
    }
  }

  // shift
  // if (current_keycode == LSFT_T(KC_LANG2) || current_keycode == LCTL_T(KC_Q) || current_keycode == LCMD_T(KC_SPACE))
  // if (current_keycode == LSFT_T(KC_LANG2) || current_keycode == LCTL_T(KC_Q) || current_keycode == LCMD_T(KC_SPACE))
  if (current_keycode == LSFT_T(KC_LANG2))
  // if (current_keycode == LCMD_T(KC_SPACE))
  {
    unregister_code(KC_LSFT);
    // unregister_code(KC_LCTRL);
    register_code(KC_LCMD);

    if (my_abs(x) > my_abs(y))
    { // ページの戻る、進む
      if (x < 0)
      { // swipe left: 戻る
        tap_code(KC_LBRACKET);
      }
      else
      { // swipe right: 進む
        tap_code(KC_RBRACKET);
      }
    }

    if (my_abs(x) < my_abs(y))
    { // タブ移動（要、Mac側でのショートカット設定）
      if (y < 0)
      { // swipe up: 右のタブへ移動
        tap_code(KC_1);
      }
      else
      { // swipe down: 左のタブへ移動
        tap_code(KC_2);
      }
    }
  }

  // Ctrl
  if (current_keycode == LCTL_T(KC_Q))
  {
    if (my_abs(x) > my_abs(y))
    { // ウインドウのサイズ変更と移動（BetterTouchToolで設定）
      register_code(KC_LCMD);

      if (x < 0)
      { // swipe left: ウインドウを1/2サイズで左へ
        tap_code(KC_4);
      }
      else
      { // swipe right: ウインドウを1/2サイズで右へ
        tap_code(KC_6);
      }
    }

    if (my_abs(x) < my_abs(y))
    { // ウインドウのサイズ変更と移動（BetterTouchToolで設定）
      register_code(KC_LCMD);

      if (y < 0)
      { // swipe up: ウィンドウを最大化
        tap_code(KC_8);
      }
      else
      { // swipe down: ウインドウを最小サイズで中央へ
        tap_code(KC_2);
      }
    }
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
  //       // tap_code(KC_RBRACKET);
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
  //       tap_code(KC_RBRACKET);
  //     }
  //     else
  //     { // swipe left
  //       tap_code(KC_LBRACKET);
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