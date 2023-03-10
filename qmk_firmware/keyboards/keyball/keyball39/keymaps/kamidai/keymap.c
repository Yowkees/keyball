/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "quantum.h"

// コード表
// 【KBC_RST: 0x5DA5】Keyball 設定のリセット
// 【KBC_SAVE: 0x5DA6】現在の Keyball 設定を EEPROM に保存します
// 【CPI_I100: 0x5DA7】CPI を 100 増加させます(最大:12000)
// 【CPI_D100: 0x5DA8】CPI を 100 減少させます(最小:100)
// 【CPI_I1K: 0x5DA9】CPI を 1000 増加させます(最大:12000)
// 【CPI_D1K: 0x5DAA】CPI を 1000 減少させます(最小:100)
// 【SCRL_TO: 0x5DAB】タップごとにスクロールモードの ON/OFF を切り替えます
// 【SCRL_MO: 0x5DAC】キーを押している間、スクロールモードになります
// 【SCRL_DVI: 0x5DAD】スクロール除数を１つ上げます(max D7 = 1/128)← 最もスクロール遅い
// 【SCRL_DVD: 0x5DAE】スクロール除数を１つ下げます(min D0 = 1/1)← 最もスクロール速い
// https://github.com/kamiichi99/keyball/tree/main/qmk_firmware/keyboards/keyball/keyball39/keymaps/kamidai

enum custom_keycodes
{
  KC_MY_BTN1 = KEYBALL_SAFE_RANGE, // Remap上では 0x5DAF
  KC_MY_BTN2,                      // Remap上では 0x5DB0
  KC_MY_BTN3,                      // Remap上では 0x5DB1
};

// 自前の絶対数を返す関数。 Functions that return absolute numbers.
int16_t my_abs(int16_t num)
{
  if (num < 0)
  {
    num = -num;
  }
  return num;
}

// 自前の符号を返す関数。 Function to return the sign.
int16_t mmouse_move_y_sign(int16_t num)
{
  if (num < 0)
  {
    return -1;
  }
  return 1;
}

////////////////////////////////////
///
/// 自動マウスレイヤーの実装 ここから
/// 参考にさせていただいたページ
/// https://zenn.dev/takashicompany/articles/69b87160cda4b9
///
////////////////////////////////////

enum ball_state
{
  NONE = 0,
  WAITING,   // マウスレイヤーが有効になるのを待つ。 Wait for mouse layer to activate.
  CLICKABLE, // マウスレイヤー有効になりクリック入力が取れる。 Mouse layer is enabled to take click input.
  CLICKING,  // クリック中。 Clicking.
  SWIPE,     // スワイプモードが有効になりスワイプ入力が取れる。 Swipe mode is enabled to take swipe input.
  SWIPING    // スワイプ中。 swiping.
};

enum ball_state state; // 現在のクリック入力受付の状態 Current click input reception status
uint16_t click_timer;  // タイマー。状態に応じて時間で判定する。 Timer. Time to determine the state of the system.

uint16_t to_reset_time = 800; // この秒数(千分の一秒)、CLICKABLE状態ならクリックレイヤーが無効になる。 For this number of seconds (milliseconds), the click layer is disabled if in CLICKABLE state.

const int16_t to_clickable_movement = 0; // クリックレイヤーが有効になるしきい値
const uint16_t click_layer = 6;          // マウス入力が可能になった際に有効になるレイヤー。Layers enabled when mouse input is enabled

int16_t mouse_record_threshold = 30; // ポインターの動きを一時的に記録するフレーム数。 Number of frames in which the pointer movement is temporarily recorded.
int16_t mouse_move_count_ratio = 5;  // ポインターの動きを再生する際の移動フレームの係数。 The coefficient of the moving frame when replaying the pointer movement.

const uint16_t ignore_disable_mouse_layer_keys[] = {KC_LANG1, KC_LANG2}; // この配列で指定されたキーはマウスレイヤー中に押下してもマウスレイヤーを解除しない

int16_t mouse_movement;

// クリック用のレイヤーを有効にする。　Enable layers for clicks
void enable_click_layer(void)
{
  layer_on(click_layer);
  click_timer = timer_read();
  state = CLICKABLE;
}

// クリック用のレイヤーを無効にする。 Disable layers for clicks.
void disable_click_layer(void)
{
  state = NONE;
  layer_off(click_layer);
}

////////////////////////////////////
///
/// 自動マウスレイヤーの実装 ここまで
///
////////////////////////////////////

////////////////////////////////////
///
/// スワイプジェスチャーの実装 ここから
/// 参考にさせていただいたページ
/// https://www.reddit.com/r/ploopy/comments/pbmrh3/qmk_options_on_ploopy_mouse_gestures/
/// https://github.com/RobertCurry0216/qmk_firmware/blob/59f83aac8fa06010c3a1a0a53fcd453d96ce2f80/keyboards/ploopyco/trackball/keymaps/robertcurry0216/keymap.c
///
////////////////////////////////////

// 変数
int16_t current_keycode;
const int16_t SWIPE_THRESHOLD = 10;
bool is_swiped = false;

// スワイプジェスチャーで何が起こるかを実際に処理する関数です
// 上、下、左、右、スワイプなしの5つのオプションがあります
void process_swipe_gesture(int16_t x, int16_t y)
{
  if (current_keycode == KC_D)
  {
    register_code(KC_BSPC);
    unregister_code(KC_BSPC);

    if (my_abs(x) > my_abs(y))
    {
      if (x > 0)
      { // swipe right
        register_code(KC_LANG1);
        unregister_code(KC_LANG1);
      }

      else
      { // swipe left
        register_code(KC_LANG2);
        unregister_code(KC_LANG2);
      }
    }
  }

  if (current_keycode == KC_F)
  {
    register_code(KC_BSPC);
    unregister_code(KC_BSPC);

    if (my_abs(x) > my_abs(y))
    {
      if (x > 0)
      { // swipe right
        register_code(KC_S);
        unregister_code(KC_S);
      }

      else
      { // swipe left
        register_code(KC_W);
        unregister_code(KC_W);
      }
    }

    if (my_abs(x) < my_abs(y))
    {
      if (y > 0)
      { // swipe down
        register_code(KC_V);
        unregister_code(KC_V);
      }
      else
      { // swipe up
        register_code(KC_H);
        unregister_code(KC_H);
      }
    }
  }
}

////////////////////////////////////
///
/// スワイプジェスチャーの実装 ここまで
///
////////////////////////////////////

// マクロキーを設定
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case KC_MY_BTN1:
  case KC_MY_BTN2:
  case KC_MY_BTN3:
  {
    report_mouse_t currentReport = pointing_device_get_report();

    // どこのビットを対象にするか。 Which bits are to be targeted?
    uint8_t btn = 1 << (keycode - KC_MY_BTN1);

    if (record->event.pressed)
    {
      // キーダウン時
      // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
      // Bit OR compares bits in the same position on the left and right sides of the operator and sets them to "1" if either of both bits is "1".
      currentReport.buttons |= btn;
      state = CLICKING;
    }
    else
    {
      // キーアップ時
      // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
      // Bit AND compares the bits in the same position on the left and right sides of the operator and sets them to "1" only if both bits are "1" together.
      currentReport.buttons &= ~btn;
      enable_click_layer();
    }

    pointing_device_set_report(currentReport);
    pointing_device_send();
    return false;
  }

  // 自動クリックレイヤーでLang1とLang2を押せるようにする
  case KC_LANG1:
  case KC_LANG2:
  {
    if (state == CLICKABLE)
    {
      if (record->event.pressed)
      {
        // キーダウン時
        enable_click_layer();
        return true;
      }
      else
      {
        // キーアップ時
        disable_click_layer();
      }
    }
  }

  // クリックすると state が SWIPE になり、離したら NONE になる
  case KC_D:
    if (record->event.pressed)
    {
      // キーダウン時
      // スワイプ操作が可能です
      state = SWIPE;
      is_swiped = false;
      current_keycode = keycode;

      if (is_swiped == false)
      {
        register_code(keycode);
        unregister_code(keycode);
      }
    }
    else
    {
      // キーアップ時
      disable_click_layer();
    }
    return false;

  default:
    if (record->event.pressed)
    {
      // キーダウン時
      disable_click_layer();
    }
  }

  return true;
}

// ball_stateの設定
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report)
{
  int16_t current_x = mouse_report.x;
  int16_t current_y = mouse_report.y;

  if (current_x != 0 || current_y != 0)
  {

    switch (state)
    {
    case CLICKABLE:
      click_timer = timer_read();
      break;

    case CLICKING:
      break;

    case WAITING:
      mouse_movement += my_abs(current_x) + my_abs(current_y);

      if (mouse_movement >= to_clickable_movement)
      {
        mouse_movement = 0;
        enable_click_layer();
      }
      break;

    case SWIPE:
      click_timer = timer_read();

      if (my_abs(current_x) >= SWIPE_THRESHOLD || my_abs(current_y) >= SWIPE_THRESHOLD)
      {
        rgblight_sethsv(HSV_BLUE);
        process_swipe_gesture(current_x, current_y);
        state = SWIPING;
        is_swiped = true;
      }
      break;
      ;

    case SWIPING:
      break;

    default:
      click_timer = timer_read();
      state = WAITING;
      mouse_movement = 0;
    }
  }
  else
  {
    switch (state)
    {
    case CLICKING:
      break;

    case CLICKABLE:
      if (timer_elapsed(click_timer) > to_reset_time)
      {
        disable_click_layer();
      }
      break;

    case WAITING:
      if (timer_elapsed(click_timer) > 50)
      {
        mouse_movement = 0;
        state = NONE;
      }
      break;

    case SWIPE:
      rgblight_sethsv(HSV_RED);
      break;

    case SWIPING:
      if (timer_elapsed(click_timer) > 300)
      {
        state = SWIPE;
      }
      break;

    default:
      mouse_movement = 0;
      state = NONE;
    }
  }

  mouse_report.x = current_x;
  mouse_report.y = current_y;

  return mouse_report;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
SFT_T(KC_TAB), KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , SFT_T(KC_P),
   LT(2,KC_A), KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , LT(2,KC_SCOLON),
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLASH  ,
    KC_LALT  ,KC_F5, LT(1,KC_Q) , KC_SPACE ,CTL_T(KC_DEL), KC_ESC  ,      KC_BSPC  , KC_ENT   , _______  , _______  , _______  , LT(3,KC_ESC)
  ),

  [1] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                           G(KC_LBRC), _______  , G(KC_1)  , G(KC_2)  , _______  ,
    _______  ,C(KC_LEFT), KC_LEFT  , KC_RIGHT,C(KC_RIGHT),                           G(KC_RBRC), KC_DOWN  , KC_UP    , G(KC_V)  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            G(KC_Z)  , G(KC_C)  , G(KC_X)  , G(KC_A)  ,SGUI(KC_Z),
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , _______  , S(KC_1)  ,S(KC_SLSH), _______  ,                            KC_NUM   , KC_7     , KC_8     , KC_9     , KC_MINUS ,
    KC_LBRC  , S(KC_9)  , S(KC_0)  , KC_RBRC  , KC_QUOTE ,                            KC_COMMA , KC_4     , KC_5     , KC_6     , KC_EQUAL ,
    _______  , _______  , _______  , _______  , KC_SCOLON,                            KC_DOT	 , KC_1     , KC_2     , KC_3     ,KC_BSLS  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  KC_0     , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , RGB_MOD  , RGB_RMOD , _______  , _______  ,                            RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN ,
    SCRL_DVD , SCRL_DVI , CPI_D100 , CPI_I100 , _______  ,                            RGB_M_K  , RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    RESET    , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______  
  ),

  [5] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______  
  ),

  [6] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  ,KC_MY_BTN1, _______  ,KC_MY_BTN2, _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______  
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state)
{
  // レイヤーが1または3の場合、スクロールモードが有効になる
  // keyball_set_scroll_mode(get_highest_layer(state) == 3);
  keyball_set_scroll_mode(get_highest_layer(state) == 1 || get_highest_layer(state) == 3);

  // レイヤーとLEDを連動させる
  uint8_t layer = biton32(state);
  switch (layer)
  {
  case 6:
    rgblight_sethsv(HSV_WHITE);
    break;

  default:
    rgblight_sethsv(HSV_OFF);
  }

  return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();

  oled_write_P(PSTR("Layer:"), false);
  oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);
  // oled_write_P(PSTR(" MV:"), false);
  // oled_write(get_u8_str(mouse_movement, ' '), false);
  // oled_write_P(PSTR("/"), false);
  // oled_write(get_u8_str(to_clickable_movement, ' '), false);

  switch (state)
  {
  case NONE:
    oled_write_ln_P(PSTR("  NONE"), false);
    break;
  case CLICKABLE:
    oled_write_ln_P(PSTR("  CLICKABLE"), false);
    break;
  case WAITING:
    oled_write_ln_P(PSTR("  WAITING"), false);
    break;
  case CLICKING:
    oled_write_ln_P(PSTR("  CLICKING"), false);
    break;
  case SWIPE:
    oled_write_ln_P(PSTR("  SWIPE"), false);
    break;
  case SWIPING:
    oled_write_ln_P(PSTR("  SWIPING"), false);
    break;
  }
}
#endif
