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

// Layer Mod-Tap
#define LMT_1Q LT(1, KC_Q)

// Mod-Tap
#define MT_SSPC SFT_T(KC_SPC)  // Shift when held, SPC when tapped
#define MT_GHEN GUI_T(KC_HENK) // Super when held, Henkan when tapped
#define MT_GF12 GUI_T(KC_F12)  // Super when held, F12 when tapped
#define MT_ECTL CTL_T(KC_ESC)  // Cntrol when held, ESC when tapped

// Shortcut
#define COPY C(KC_C)
#define CUT  C(KC_X)
#define PSTE C(KC_V)
#define UNDO C(KC_Z)
#define SALL C(KC_A) // Select All

#define NTAB C(KC_TAB)   // Next TAB (Ctrl+Tab)
#define PTAB RCS(KC_TAB) // Previous TAB (Ctrl+Shift+Tab)
#define CTAB C(KC_W)     // Close Tab/Window

#define VOLU KC__VOLUP
#define VOLM KC__MUTE
#define VOLD KC__VOLDOWN

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 0
 * ,------------------------------------------------.                     ,-----------------------------------------------.
 * |    `   |   1   |   2   |   3   |   4   |   5   |                     |   6   |   7   |   8   |   9   |   0   |   -   |
 * |--------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |  TAB   |   Q'  |   W   |   E   |   R   |   T   |                     |   Y   |   U   |   I   |   O   |   P   |   \   |
 * |--------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |  CTL'  |   A   |   S   |   D   |   F   |   G   |                     |   H   |   J   |   K   |   L   |   ;   |   '   |
 * |--------+-------+-------+-------+-------+-------|-------.     ,-------|-------+-------+-------+-------+-------+-------|
 * |  SHFT  |   Z   |   X   |   C   |   V   |   B   |   [   |     |   ]   |   N   |   M   |   ,   |   .   |   /   |   =   |
 * |----------------------------------------------------------. .---------------------------------------------------------|
 * |        |       |       |  ALT  |/  GUI' /  SPC' /  ---  /   \  ENT  \ BSPC  \|  ---  |  ---  |  ---  |       |       |
 * `--------------------------------------------------------'     '-------------------------------------------------------'
 */

  [0] = LAYOUT_universal(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  LMT_1Q,  KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    MT_ECTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
    SCRL_TO, SCRL_MO, MO(3)  , _______, KC_LALT, MT_GF12, MT_SSPC, KC_ENT , KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  KC_ESC
  ),

/* 1
 * ,------------------------------------------------.                     ,-----------------------------------------------.
 * |        |  F1   |  F2   |  F3   |  F4   |  F5   |                     |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |
 * |--------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |        |       |  F12  |  F13  |  F14  |  VOL+ |                     |  Copy |  Undo |  PgUp |  Ins  |  Pate |       |
 * |--------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |        |       |       |       |  SALL |  MUTE |                     |  Left |  Down |  Up   | Right |  End  |       |
 * |--------+-------+-------+-------+-------+-------|-------.     ,-------|-------+-------+-------+-------+-------+-------|
 * |        |       |       |       |  CUT  |  VOL- |       |     |       |  Home |  PgDn |  PTab |  NTab |  CTab | PSCR  |
 * |----------------------------------------------------------. .---------------------------------------------------------|
 * |        |       |       |       |/       /       /       /   \       \  DEL  \|  ---  |  ---  |  ---  |       |       |
 * `--------------------------------------------------------'     '-------------------------------------------------------'
 */

  [1] = LAYOUT_universal(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11 ,
    _______, _______, KC_F12,  KC_F13 , KC_F14 , VOLU,                      COPY,    UNDO,    KC_PGUP, KC_INS,  PSTE,    _______,
    _______, _______, _______, _______, SALL,    VOLM,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  _______,
    _______, _______, _______, _______, CUT,     VOLD,    _______, _______, KC_HOME, KC_PGDN, PTAB,    NTAB,    CTAB,    KC_PSCR,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL , XXXXXXX, XXXXXXX, XXXXXXX, _______, _______
  ),

/* 2
 * ,------------------------------------------------.                     ,-----------------------------------------------.
 * |        |       |       |       |       |       |                     |       |       |       |       |       |       |
 * |--------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |        |       |       |       |       |       |                     |       |       |       |       |       |       |
 * |--------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |        |       |       |       |       |       |                     |       |       |       |       |       |       |
 * |--------+-------+-------+-------+-------+-------|-------.     ,-------|-------+-------+-------+-------+-------+-------|
 * |        |       |       |       |       |       |       |     |       |       |       |       |       |       |       |
 * |----------------------------------------------------------. .---------------------------------------------------------|
 * |        |       |       |       |/       /       /       /   \       \       \|  ---  |  ---  |  ---  |       |       |
 * `--------------------------------------------------------'     '-------------------------------------------------------'
 */

  [2] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  _______  , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , KC_F12   ,
    _______  , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,            S(KC_9)  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , KC_0     , KC_DOT   , _______  , _______  , _______  ,             KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  , RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EEP_RST  ,            EEP_RST  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    RESET    , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , RESET
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif
