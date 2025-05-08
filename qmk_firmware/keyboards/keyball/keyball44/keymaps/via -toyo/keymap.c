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
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
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
const uint16_t PROGMEM my_jq[] = {KC_J, KC_Q, COMBO_END};

combo_t key_combos[] = {
COMBO(my_jq, KC_QUES),
};
#endif

#ifdef COMBO_ENABLE
enum combos{
JQ_QUES,
JS_SING,
JW_DOUB,
JB_BOU,
FP_PER,
JD_DOL,
FU_UNDER,
JA_AND,
FH_HUSH,
JE_EXCL,
FN_NAMI,
JT_TASU,
FY_YAMA,
FK_KAKE,
UI_UP,
MC_DOWN,
JK_LEFT,
KL_RIGHT,
FD_LAYER,
};

const uint16_t PROGMEM my_jq[] = {KC_J, KC_Q, COMBO_END};
const uint16_t PROGMEM my_js[] = {KC_J, KC_S, COMBO_END};
const uint16_t PROGMEM my_jw[] = {KC_J, KC_W, COMBO_END};
const uint16_t PROGMEM my_jb[] = {KC_J, KC_B, COMBO_END};
const uint16_t PROGMEM my_fp[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM my_jd[] = {KC_J, KC_D, COMBO_END};
const uint16_t PROGMEM my_fu[] = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM my_ja[] = {KC_J, KC_A, COMBO_END};
const uint16_t PROGMEM my_fh[] = {KC_F, KC_H, COMBO_END};
const uint16_t PROGMEM my_je[] = {KC_J, KC_E, COMBO_END};
const uint16_t PROGMEM my_fn[] = {KC_F, KC_N, COMBO_END};
const uint16_t PROGMEM my_jt[] = {KC_J, KC_T, COMBO_END};
const uint16_t PROGMEM my_fy[] = {KC_F, KC_Y, COMBO_END};
const uint16_t PROGMEM my_fk[] = {KC_F, KC_K, COMBO_END};
const uint16_t PROGMEM my_ui[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM my_mco[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM my_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM my_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM my_fd[] = {KC_F, KC_D, COMBO_END};

combo_t key_combos[] = {
[JQ_QUES] = COMBO(my_jq, KC_QUES),
[JS_SING] = COMBO(my_js, KC_QUOT),
[JW_DOUB] = COMBO(my_jw, KC_DQUO),
[JB_BOU] = COMBO(my_jb, KC_PIPE),
[FP_PER] = COMBO(my_fp, KC_PERC),
[JD_DOL] = COMBO(my_jd, KC_DLR),
[FU_UNDER] = COMBO(my_fu, LSFT(KC_MINS)),
[JA_AND] = COMBO(my_ja, KC_AMPR),
[FH_HUSH] = COMBO(my_fh, KC_HASH),
[JE_EXCL] = COMBO(my_je, KC_EXLM),
[FN_NAMI] = COMBO(my_fn, KC_TILD),
[JT_TASU] = COMBO(my_jt, KC_PLUS),
[FY_YAMA] = COMBO(my_fy, KC_CIRC),
[FK_KAKE] = COMBO(my_fk, LSFT(KC_8)),
[UI_UP] = COMBO(my_ui, KC_UP),
[MC_DOWN] = COMBO(my_mco, KC_DOWN),
[JK_LEFT] = COMBO(my_jk, KC_LEFT),
[KL_RIGHT] = COMBO(my_kl, KC_RGHT),
[FD_LAYER] = COMBO(my_fd, MO(4)),
};
#endif