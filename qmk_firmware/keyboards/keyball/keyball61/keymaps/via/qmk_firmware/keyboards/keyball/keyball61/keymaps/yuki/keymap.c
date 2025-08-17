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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_DEL   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_INT3  ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    MO(1)    , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_RBRC  ,              KC_NUHS, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
    _______  , KC_LCTL  , KC_LALT  , KC_LGUI,LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1),    KC_BSPC,LT(2,KC_ENT),LT(1,KC_LNG2),KC_RGUI, _______ , KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    S(KC_ESC), S(KC_1)  , KC_LBRC  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                  KC_EQL   , S(KC_6)  ,S(KC_QUOT), S(KC_8)  , S(KC_9)  ,S(KC_INT1),
    S(KC_DEL), S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                                  S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,S(KC_INT3),
    S(KC_TAB), S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                                  S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L)  , KC_QUOT  , S(KC_2)  ,
    _______  , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,S(KC_RBRC),           S(KC_NUHS), S(KC_N)  , S(KC_M)  ,S(KC_COMM), S(KC_DOT),S(KC_SLSH),S(KC_RSFT),
    _______  ,S(KC_LCTL),S(KC_LALT),S(KC_LGUI), _______  , _______  , _______  ,            _______  , _______  , _______  ,S(KC_RGUI), _______  , S(KC_RALT), _______
  ),

  [2] = LAYOUT_universal(
    SSNP_FRE , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  _______  , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , KC_F12   ,
    SSNP_HOR , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,            S(KC_9)  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , KC_0     , KC_DOT   , _______  , _______  , _______  ,             KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
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
    keyball_oled_render_layerinfo();
}
#endif

#ifdef COMBO_ENABLE

enum combos{

TQ_QUES,
OS_SING,
OW_DOUB,
OB_BOU,
OP_PER,
OD_DOL,
TU_UNDER,
TA_AND,
OH_HUSH,
TE_EXCL,
ON_NAMI,
OT_TASU,
OY_YAMA,
OK_KAKE,
LU_UP,
XC_DOWN,
IA_LEFT,
AO_RIGHT,
TN_BTN1,
NS_BTN2,
WR_BTN4,
RY_BTN5,
TS_BTN3

};

const uint16_t PROGMEM my_tq[] = {KC_T, KC_Q, COMBO_END};
const uint16_t PROGMEM my_os[] = {KC_O, KC_S, COMBO_END};
const uint16_t PROGMEM my_ow[] = {KC_O, KC_W, COMBO_END};
const uint16_t PROGMEM my_ob[] = {KC_O, KC_B, COMBO_END};
const uint16_t PROGMEM my_op[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM my_od[] = {KC_O, KC_D, COMBO_END};
const uint16_t PROGMEM my_tu[] = {KC_T, KC_U, COMBO_END};
const uint16_t PROGMEM my_ta[] = {KC_T, KC_A, COMBO_END};
const uint16_t PROGMEM my_oh[] = {KC_O, KC_H, COMBO_END};
const uint16_t PROGMEM my_te[] = {KC_T, KC_E, COMBO_END};
const uint16_t PROGMEM my_on[] = {KC_O, KC_N, COMBO_END};
const uint16_t PROGMEM my_ot[] = {KC_O, KC_T, COMBO_END};
const uint16_t PROGMEM my_oy[] = {KC_O, KC_Y, COMBO_END};
const uint16_t PROGMEM my_ok[] = {KC_O, KC_K, COMBO_END};
const uint16_t PROGMEM my_lu[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM my_xc[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM my_ia[] = {KC_I, KC_A, COMBO_END};
const uint16_t PROGMEM my_ao[] = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM my_tn[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM my_ns[] = {KC_N, KC_S, COMBO_END};
const uint16_t PROGMEM my_wr[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM my_ry[] = {KC_R, KC_Y, COMBO_END};
const uint16_t PROGMEM my_ts[] = {KC_T, KC_S, COMBO_END};

combo_t key_combos[] = {

[TQ_QUES] = COMBO(my_tq, KC_QUES),

[OS_SING] = COMBO(my_os, KC_QUOT),

[OW_DOUB] = COMBO(my_ow, KC_DQUO),

[OB_BOU] = COMBO(my_ob, KC_PIPE),

[OP_PER] = COMBO(my_op, KC_PERC),

[OD_DOL] = COMBO(my_od, KC_DLR),

[TU_UNDER] = COMBO(my_tu, LSFT(KC_MINS)),

[TA_AND] = COMBO(my_ta, KC_AMPR),

[OH_HUSH] = COMBO(my_oh, KC_HASH),

[TE_EXCL] = COMBO(my_te, KC_EXLM),

[ON_NAMI] = COMBO(my_on, KC_TILD),

[OT_TASU] = COMBO(my_ot, KC_PLUS),

[OY_YAMA] = COMBO(my_oy, KC_CIRC),

[OK_KAKE] = COMBO(my_ok, LSFT(KC_8)),

[LU_UP] = COMBO(my_lu, KC_UP),

[XC_DOWN] = COMBO(my_xc, KC_DOWN),

[IA_LEFT] = COMBO(my_ia, KC_LEFT),

[AO_RIGHT] = COMBO(my_ao, KC_RIGHT),

[TN_BTN1] = COMBO(my_tn, KC_BTN1),

[NS_BTN2] = COMBO(my_ns, KC_BTN2),

[WR_BTN4] = COMBO(my_wr, KC_BTN4),

[RY_BTN5] = COMBO(my_ry, KC_BTN5),

[TS_BTN3] = COMBO(my_ts, KC_BTN3),

};


#endif
