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

// コンボキーの定義-S ref:https://note.com/mamelog0103/n/n5a51fcd24f26
#ifdef COMBO_ENABLE
enum combos{
JQ_QUES,  // J + Q = ?
JS_SING,  // J + S = ' (シングルクォーテーション)
JW_DOUB,  // J + W = " (ダブルクォーテーション)
JB_BOU,   // J + B = | (棒、パイプ)
FP_PER,   // F + P = %
JD_DOL,   // J + D = $
FU_UNDER, // F + U = _ (アンダーバー)
JA_AND,   // J + A = &
FH_HUSH,  // F + H = #
JE_EXCL,  // J + E = ! (エクスクラメーションマーク)
FN_NAMI,  // F + N = ~
JT_TASU,  // J + T = + (足す、プラス)
FY_YAMA,  // F + Y = ^ (山、ハット)
FK_KAKE,  // F + K = * (かける、アスタリスク)
UI_UP,    // U + I = ↑ (U(↑)とその右隣)
MC_DOWN,  // M + , = ↓ (M(↓)とその右隣)
JK_LEFT,  // J + K = ← (J(←)とその右隣)
KL_RIGHT, // K + L = → (K(→)とその右隣)
FD_LAYER, // F + D = レイヤー4に移動
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
// コンボキーの定義-E

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    // ref:https://mazcon.hatenablog.com/entry/2023/11/10/080000
    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 1:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }
    #endif

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

// ref:https://mazcon.hatenablog.com/entry/2023/11/10/080000
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif