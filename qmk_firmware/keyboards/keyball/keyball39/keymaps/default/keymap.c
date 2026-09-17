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

// ================================================
// レイヤー定義
// ================================================
#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _BALL   3
#define _VSCRL  4  // Q長押し: 縦スクロール
#define _HSCRL  5  // W長押し: 横スクロール
#define _FAST   6  // E長押し: スクロール2倍速
#define _SLOW   7  // R長押し: CPI 1/2倍（低速）

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [_BASE] = LAYOUT_universal(
    LT(_VSCRL,KC_Q), LT(_HSCRL,KC_W), LT(_FAST,KC_E), LT(_SLOW,KC_R), KC_T,                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

  [_LOWER] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [_RAISE] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [_BALL] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),

  // Q長押し: 縦スクロール
  [_VSCRL] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  // W長押し: 横スクロール
  [_HSCRL] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  // E長押し: スクロール2倍速
  [_FAST] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  // R長押し: CPI 1/2倍（低速カーソル）
  [_SLOW] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

// ================================================
// スクロール・CPI 制御（LT による layer_state_set_user で管理）
// ================================================
static bool init_done = false;
static uint8_t base_scroll_div;    // 1..7
static uint8_t base_cpi;           // 100cpi単位
static uint8_t fast_scroll_div;    // 2倍速用: ceil(base_div/2)
static uint8_t half_cpi;           // 1/2倍用: floor(base_cpi/2), 最低1

static void ensure_init(void) {
    if (init_done) return;

    base_scroll_div = keyball_get_scroll_div();
    if (base_scroll_div < 1) base_scroll_div = 1;
    if (base_scroll_div > 7) base_scroll_div = 7;

    base_cpi = keyball_get_cpi();

    fast_scroll_div = (base_scroll_div + 1) / 2;
    if (fast_scroll_div < 1) fast_scroll_div = 1;
    if (fast_scroll_div > 7) fast_scroll_div = 7;

    half_cpi = base_cpi / 2;
    if (half_cpi < 1) half_cpi = 1;

    init_done = true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    ensure_init();

    bool vscrl = layer_state_cmp(state, _VSCRL);
    bool hscrl = layer_state_cmp(state, _HSCRL);
    bool fast  = layer_state_cmp(state, _FAST);
    bool slow  = layer_state_cmp(state, _SLOW);
    bool ball  = layer_state_cmp(state, _BALL);

    bool scrolling = vscrl || hscrl || ball;

    // スクロールモード
    keyball_set_scroll_mode(scrolling);

    // スクロール方向スナップ
#if KEYBALL_SCROLLSNAP_ENABLE == 2
    if (vscrl) {
        keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
    } else if (hscrl) {
        keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_HORIZONTAL);
    }
#endif

    // スクロール速度（E長押しで2倍速）
    if (scrolling && fast) {
        keyball_set_scroll_div(fast_scroll_div);
    } else {
        keyball_set_scroll_div(base_scroll_div);
    }

    // CPI（R長押しで1/2倍）
    if (slow) {
        keyball_set_cpi(half_cpi);
    } else {
        keyball_set_cpi(base_cpi);
    }

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
