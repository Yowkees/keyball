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

// 矩形選択のプリントスクリーン
#define PS_SELECT C(S(G(KC_4)))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default (VIA) Keymap
  [0] = LAYOUT_universal(
    KC_ESC    , KC_Q         , KC_W         , KC_E         , KC_R         , KC_T         ,                KC_Y         , KC_U         , KC_I         , KC_O         , KC_P         , TO(1)       ,
    KC_TAB    , LT(4,KC_A)   , KC_S         , SFT_T(KC_D)  , KC_F         , KC_G         ,                KC_H         , KC_J         , SFT_T(KC_K)  , KC_L         , LT(3,KC_MINS), TO(0)       ,
    KC_LNG2   , KC_Z         , KC_X         , KC_C         , KC_V         , KC_B         ,                KC_N         , KC_M         , KC_COMM      , KC_DOT       , KC_SLSH      , KC_LNG1     ,
                KC_LCTL      , KC_LALT      , GUI_T(KC_SPC), MO(1)        , MO(2)        , KC_BSPC      , GUI_T(KC_ENT), XXXXXXX      , XXXXXXX      , PS_SELECT
  ),

  // Special Key Layer
  [1] = LAYOUT_universal(
    _______   , S(KC_4)      , S(KC_3)      , S(KC_2)      , S(KC_SCLN)   , XXXXXXX      ,                XXXXXXX      , S(KC_EQL)    , S(KC_8)      , S(KC_5)      , S(KC_6)     , TO(2)       ,
    _______   , KC_LBRC      , S(KC_LBRC)   , S(KC_9)      , KC_SCLN      , S(KC_COMM)   ,                S(KC_DOT)    , KC_EQL       , S(KC_0)      , S(KC_RBRC)   , KC_RBRC     , _______     ,
    _______   , S(KC_GRV)    , KC_GRV       , S(KC_QUOT)   , KC_QUOT      , XXXXXXX      ,                S(KC_SLSH)   , S(KC_1)      , S(KC_7)      , S(KC_BSLS)   , KC_BSLS     , _______     ,
                _______      , _______      , _______      , _______      , _______      , _______      , _______      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Number Key Layer
  [2] = LAYOUT_universal(
    _______   , KC_F1        , KC_F2        , KC_F3        , KC_F4       , KC_F5         ,                KC_F6        , KC_F7        , KC_F8        , KC_F9        , KC_F10      , TO(3)       ,
    _______   , KC_1         , KC_2         , KC_3         , KC_4        , KC_5          ,                KC_6         , KC_7         , KC_8         , KC_9         , KC_0        , _______     ,
    _______   , KC_F11       , KC_F12       , XXXXXXX      , XXXXXXX     , XXXXXXX       ,                XXXXXXX      , XXXXXXX      , XXXXXXX      , KC_DOT       , XXXXXXX     , _______     ,
                _______      , _______      , _______      , _______     , _______       , _______      , _______      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Arrow Key and Window Control Key Layer
  [3] = LAYOUT_universal(
    _______   , XXXXXXX      , C(A(KC_LEFT)), C(A(KC_ENT)), C(A(KC_RGHT)), XXXXXXX       ,                XXXXXXX      , G(KC_C)      , KC_UP        , G(KC_V)      , S(G(KC_V))  , TO(4)       ,
    _______   , XXXXXXX      , G(KC_LBRC)   , XXXXXXX     , G(KC_RBRC)   , XXXXXXX       ,                XXXXXXX      , KC_LEFT      , KC_DOWN      , KC_RGHT     , XXXXXXX     , _______     ,
    _______   , C(KC_L)      , C(KC_A)      , C(KC_C)     , C(KC_E)      , XXXXXXX       ,                XXXXXXX      , C(KC_LEFT)   , C(KC_UP)     , C(KC_RGHT)   , XXXXXXX     , _______     ,
                _______      , _______      , _______      , _______     , _______       , _______      , _______      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Programming Key Layer
  [4] = LAYOUT_universal(
    _______   , XXXXXXX      , KC_F2        , XXXXXXX     , C(KC_R)     , XXXXXXX       ,                 XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX     , TO(5)       ,
    _______   , XXXXXXX      , C(KC_MINS)   , C(KC_GRV)   , KC_F12      , XXXXXXX       ,                 XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX     , _______     ,
    _______   , XXXXXXX      , XXXXXXX      , XXXXXXX     , XXXXXXX     , XXXXXXX       ,                 XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX     , _______     ,
                _______      , _______      , _______     , _______     , _______       , _______       , _______      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Keyball Key Layer
  [5] = LAYOUT_universal(
    _______   , KBC_RST      , KBC_SAVE     , CPI_I100    , CPI_D100    , CPI_I1K       ,                 CPI_D1K      , SCRL_TO      , SCRL_MO      , SCRL_DVI     , SCRL_DVD    , _______     ,
    _______   , AML_TO       , AML_I50      , AML_D50     , SSNP_VRT    , SSNP_HOR      ,                 SSNP_FRE     , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX     , _______     ,
    _______   , XXXXXXX      , XXXXXXX      , XXXXXXX     , XXXXXXX     , XXXXXXX       ,                 XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX     , _______     ,
                _______      , _______      , _______     , _______     , _______       , _______       , _______      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Mouse Key Layer
  [6] = LAYOUT_universal(
    _______   , _______      , _______      , _______     , _______     , _______       ,                 XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX     , _______     ,
    _______   , _______      , _______      , _______     , _______     , _______       ,                 XXXXXXX      , KC_MS_BTN1   , SCRL_MO      , KC_MS_BTN2   , XXXXXXX     , _______     ,
    _______   , _______      , _______      , _______     , _______     , _______       ,                 XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX     , _______     ,
                _______      , _______      , _______     , _______     , _______       , _______       , _______      , XXXXXXX      , XXXXXXX      , _______
  ),
};

// clang-format on

/**
 * https://docs.qmk.fm/#/feature_pointing_device?id=pointing-device-auto-mouse
 */
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
