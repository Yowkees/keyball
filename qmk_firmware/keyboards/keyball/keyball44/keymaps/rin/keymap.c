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

enum custom_layers {
  NICOLA,
  DVORAK,
};

enum custom_keycodes {
  LCTL_NICOLA = SAFE_RANGE,
  TO_DVORAK,
  TO_CMD_QWERTY_ESC,
// shifted characters with same-side thumb shift
  NICOLA_XA,
  NICOLA_E,
  NICOLA_RI,
  NICOLA_XYA,
  NICOLA_RE,
  NICOLA_YO,
  NICOLA_NI,
  NICOLA_RU,
  NICOLA_MA,
  NICOLA_XE,
  NICOLA_WO,
  NICOLA_A,
  NICOLA_NA,
  NICOLA_XYU,
  NICOLA_MO,
  NICOLA_MI,
  NICOLA_O,
  NICOLA_NO,
  NICOLA_XYO,
  NICOLA_XTU,
  NICOLA_XU,
  NICOLA_CHOUON,
  NICOLA_RO,
  NICOLA_YA,
  NICOLA_XI,
  NICOLA_NU,
  NICOLA_YU,
  NICOLA_MU,
  NICOLA_WA,
  NICOLA_XO,
// shifted characters with opposite-side thumb shift
  NICOLA_GA,
  NICOLA_DA,
  NICOLA_GO,
  NICOLA_ZA,
  NICOLA_PA,
  NICOLA_DI,
  NICOLA_GU,
  NICOLA_DU,
  NICOLA_PI,
  NICOLA_VU,
  NICOLA_JI,
  NICOLA_DE,
  NICOLA_GE,
  NICOLA_ZE,
  NICOLA_BA,
  NICOLA_DO,
  NICOLA_GI,
  NICOLA_PO,
  NICOLA_BI,
  NICOLA_ZU,
  NICOLA_BU,
  NICOLA_BE,
  NICOLA_PU,
  NICOLA_ZO,
  NICOLA_PE,
  NICOLA_BO,
  MID_DOT,
};

const uint16_t PROGMEM nicola_xa[]     = {TO_CMD_QWERTY_ESC, KC_QUOT, COMBO_END};
const uint16_t PROGMEM nicola_e[]      = {TO_CMD_QWERTY_ESC, KC_COMM, COMBO_END};
const uint16_t PROGMEM nicola_ri[]     = {TO_CMD_QWERTY_ESC, KC_DOT,  COMBO_END};
const uint16_t PROGMEM nicola_xya[]    = {TO_CMD_QWERTY_ESC, KC_P,    COMBO_END};
const uint16_t PROGMEM nicola_re[]     = {TO_CMD_QWERTY_ESC, KC_Y,    COMBO_END};
const uint16_t PROGMEM nicola_yo[]     = {RGUI_T(KC_SPC),    KC_F,    COMBO_END};
const uint16_t PROGMEM nicola_ni[]     = {RGUI_T(KC_SPC),    KC_G,    COMBO_END};
const uint16_t PROGMEM nicola_ru[]     = {RGUI_T(KC_SPC),    KC_C,    COMBO_END};
const uint16_t PROGMEM nicola_ma[]     = {RGUI_T(KC_SPC),    KC_R,    COMBO_END};
const uint16_t PROGMEM nicola_xe[]     = {RGUI_T(KC_SPC),    KC_L,    COMBO_END};

const uint16_t PROGMEM nicola_wo[]     = {TO_CMD_QWERTY_ESC, KC_A, COMBO_END};
const uint16_t PROGMEM nicola_a[]      = {TO_CMD_QWERTY_ESC, KC_O, COMBO_END};
const uint16_t PROGMEM nicola_na[]     = {TO_CMD_QWERTY_ESC, KC_E, COMBO_END};
const uint16_t PROGMEM nicola_xyu[]    = {TO_CMD_QWERTY_ESC, KC_U, COMBO_END};
const uint16_t PROGMEM nicola_mo[]     = {TO_CMD_QWERTY_ESC, KC_I, COMBO_END};
const uint16_t PROGMEM nicola_mi[]     = {RGUI_T(KC_SPC),    KC_D, COMBO_END};
const uint16_t PROGMEM nicola_o[]      = {RGUI_T(KC_SPC),    KC_H, COMBO_END};
const uint16_t PROGMEM nicola_no[]     = {RGUI_T(KC_SPC),    KC_T, COMBO_END};
const uint16_t PROGMEM nicola_xyo[]    = {RGUI_T(KC_SPC),    KC_N, COMBO_END};
const uint16_t PROGMEM nicola_xtu[]    = {RGUI_T(KC_SPC),    KC_S, COMBO_END};

const uint16_t PROGMEM nicola_xu[]     = {TO_CMD_QWERTY_ESC, KC_SCLN, COMBO_END};
const uint16_t PROGMEM nicola_chouon[] = {TO_CMD_QWERTY_ESC, KC_Q,    COMBO_END};
const uint16_t PROGMEM nicola_ro[]     = {TO_CMD_QWERTY_ESC, KC_J,    COMBO_END};
const uint16_t PROGMEM nicola_ya[]     = {TO_CMD_QWERTY_ESC, KC_K,    COMBO_END};
const uint16_t PROGMEM nicola_xi[]     = {TO_CMD_QWERTY_ESC, KC_X,    COMBO_END};
const uint16_t PROGMEM nicola_nu[]     = {RGUI_T(KC_SPC),    KC_B,    COMBO_END};
const uint16_t PROGMEM nicola_yu[]     = {RGUI_T(KC_SPC),    KC_M,    COMBO_END};
const uint16_t PROGMEM nicola_mu[]     = {RGUI_T(KC_SPC),    KC_W,    COMBO_END};
const uint16_t PROGMEM nicola_wa[]     = {RGUI_T(KC_SPC),    KC_V,    COMBO_END};
const uint16_t PROGMEM nicola_xo[]     = {RGUI_T(KC_SPC),    KC_Z,    COMBO_END};

const uint16_t PROGMEM nicola_ga[]     = {RGUI_T(KC_SPC),    KC_COMM, COMBO_END};
const uint16_t PROGMEM nicola_da[]     = {RGUI_T(KC_SPC),    KC_DOT,  COMBO_END};
const uint16_t PROGMEM nicola_go[]     = {RGUI_T(KC_SPC),    KC_P,    COMBO_END};
const uint16_t PROGMEM nicola_za[]     = {RGUI_T(KC_SPC),    KC_Y,    COMBO_END};
const uint16_t PROGMEM nicola_pa[]     = {TO_CMD_QWERTY_ESC, KC_F,    COMBO_END};
const uint16_t PROGMEM nicola_di[]     = {TO_CMD_QWERTY_ESC, KC_G,    COMBO_END};
const uint16_t PROGMEM nicola_gu[]     = {TO_CMD_QWERTY_ESC, KC_C,    COMBO_END};
const uint16_t PROGMEM nicola_du[]     = {TO_CMD_QWERTY_ESC, KC_R,    COMBO_END};
const uint16_t PROGMEM nicola_pi[]     = {TO_CMD_QWERTY_ESC, KC_L,    COMBO_END};

const uint16_t PROGMEM nicola_vu[]     = {RGUI_T(KC_SPC),    KC_A, COMBO_END};
const uint16_t PROGMEM nicola_ji[]     = {RGUI_T(KC_SPC),    KC_O, COMBO_END};
const uint16_t PROGMEM nicola_de[]     = {RGUI_T(KC_SPC),    KC_E, COMBO_END};
const uint16_t PROGMEM nicola_ge[]     = {RGUI_T(KC_SPC),    KC_U, COMBO_END};
const uint16_t PROGMEM nicola_ze[]     = {RGUI_T(KC_SPC),    KC_I, COMBO_END};
const uint16_t PROGMEM nicola_ba[]     = {TO_CMD_QWERTY_ESC, KC_D, COMBO_END};
const uint16_t PROGMEM nicola_do[]     = {TO_CMD_QWERTY_ESC, KC_H, COMBO_END};
const uint16_t PROGMEM nicola_gi[]     = {TO_CMD_QWERTY_ESC, KC_T, COMBO_END};
const uint16_t PROGMEM nicola_po[]     = {TO_CMD_QWERTY_ESC, KC_N, COMBO_END};

const uint16_t PROGMEM nicola_bi[]     = {RGUI_T(KC_SPC),    KC_Q, COMBO_END};
const uint16_t PROGMEM nicola_zu[]     = {RGUI_T(KC_SPC),    KC_J, COMBO_END};
const uint16_t PROGMEM nicola_bu[]     = {RGUI_T(KC_SPC),    KC_K, COMBO_END};
const uint16_t PROGMEM nicola_be[]     = {RGUI_T(KC_SPC),    KC_X, COMBO_END};
const uint16_t PROGMEM nicola_pu[]     = {TO_CMD_QWERTY_ESC, KC_B, COMBO_END};
const uint16_t PROGMEM nicola_zo[]     = {TO_CMD_QWERTY_ESC, KC_M, COMBO_END};
const uint16_t PROGMEM nicola_pe[]     = {TO_CMD_QWERTY_ESC, KC_W, COMBO_END};
const uint16_t PROGMEM nicola_bo[]     = {TO_CMD_QWERTY_ESC, KC_V, COMBO_END};

combo_t key_combos[] = {
// shifted characters with same-side thumb shift
    COMBO(nicola_xa,     NICOLA_XA),
    COMBO(nicola_e,      NICOLA_E),
    COMBO(nicola_ri,     NICOLA_RI),
    COMBO(nicola_xya,    NICOLA_XYA),
    COMBO(nicola_re,     NICOLA_RE),
    COMBO(nicola_yo,     NICOLA_YO),
    COMBO(nicola_ni,     NICOLA_NI),
    COMBO(nicola_ru,     NICOLA_RU),
    COMBO(nicola_ma,     NICOLA_MA),
    COMBO(nicola_xe,     NICOLA_XE),
    COMBO(nicola_wo,     NICOLA_WO),
    COMBO(nicola_a,      NICOLA_A),
    COMBO(nicola_na,     NICOLA_NA),
    COMBO(nicola_xyu,    NICOLA_XYU),
    COMBO(nicola_mo,     NICOLA_MO),
    COMBO(nicola_mi,     NICOLA_MI),
    COMBO(nicola_o,      NICOLA_O),
    COMBO(nicola_no,     NICOLA_NO),
    COMBO(nicola_xyo,    NICOLA_XYO),
    COMBO(nicola_xtu,    NICOLA_XTU),
    COMBO(nicola_xu,     NICOLA_XU),
    COMBO(nicola_chouon, NICOLA_CHOUON),
    COMBO(nicola_ro,     NICOLA_RO),
    COMBO(nicola_ya,     NICOLA_YA),
    COMBO(nicola_xi,     NICOLA_XI),
    COMBO(nicola_nu,     NICOLA_NU),
    COMBO(nicola_yu,     NICOLA_YU),
    COMBO(nicola_mu,     NICOLA_MU),
    COMBO(nicola_wa,     NICOLA_WA),
    COMBO(nicola_xo,     NICOLA_XO),
// shifted characters with opposite-side thumb shift
    COMBO(nicola_ga, NICOLA_GA),
    COMBO(nicola_da, NICOLA_DA),
    COMBO(nicola_go, NICOLA_GO),
    COMBO(nicola_za, NICOLA_ZA),
    COMBO(nicola_pa, NICOLA_PA),
    COMBO(nicola_di, NICOLA_DI),
    COMBO(nicola_gu, NICOLA_GU),
    COMBO(nicola_du, NICOLA_DU),
    COMBO(nicola_pi, NICOLA_PI),
    COMBO(nicola_vu, NICOLA_VU),
    COMBO(nicola_ji, NICOLA_JI),
    COMBO(nicola_de, NICOLA_DE),
    COMBO(nicola_ge, NICOLA_GE),
    COMBO(nicola_ze, NICOLA_ZE),
    COMBO(nicola_ba, NICOLA_BA),
    COMBO(nicola_do, NICOLA_DO),
    COMBO(nicola_gi, NICOLA_GI),
    COMBO(nicola_po, NICOLA_PO),
    COMBO(nicola_bi, NICOLA_BI),
    COMBO(nicola_zu, NICOLA_ZU),
    COMBO(nicola_bu, NICOLA_BU),
    COMBO(nicola_be, NICOLA_BE),
    COMBO(nicola_pu, NICOLA_PU),
    COMBO(nicola_zo, NICOLA_ZO),
    COMBO(nicola_pe, NICOLA_PE),
    COMBO(nicola_bo, NICOLA_BO),
};

uint8_t mod_state;

#define HANDLE_DVORAK_NICOLA(code_dvorak, code_qwerty, nicola_plain) \
  case KC_##code_dvorak: { \
      if (record->event.pressed) { \
          if (mod_state & MOD_MASK_GUI) { \
              tap_code(KC_##code_qwerty); \
              return false; \
          } \
          if (layer_state_is(NICOLA)) { \
              if (mod_state & MOD_MASK_SHIFT) { \
                  return true; \
              } \
              return false; \
          } \
          return true; \
      } else { \
          if (layer_state_is(NICOLA)) { \
              send_string(nicola_plain); \
              return false; \
          } \
          return true; \
      } \
  } \

#define HANDLE_NICOLA_KEY(keyname, keystring) \
    case NICOLA_##keyname: \
        if (record->event.pressed) { \
            SEND_STRING(keystring); \
        } \
        return false

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t lctl_timer;
  static uint16_t cmd_timer;

  mod_state = get_mods();
  switch (keycode) {
    case LCTL_NICOLA:
      if (record->event.pressed) {
        lctl_timer = timer_read();
        register_mods(MOD_BIT(KC_LCTL));
        return false;
      } else {
        unregister_mods(MOD_BIT(KC_LCTL));
        if (timer_elapsed(lctl_timer) < TAPPING_TERM) {
          tap_code16(KC_LNG1);
          layer_off(DVORAK);
        }
      }
      return false;
    case TO_CMD_QWERTY_ESC:
      if (record->event.pressed) {
        cmd_timer = timer_read();

        //add_mods(MOD_MASK_GUI);
        register_code16(KC_LGUI);
        layer_on(DVORAK);
        return true;
      } else {
        unregister_code16(KC_LGUI);
        layer_off(DVORAK);

        if (timer_elapsed(cmd_timer) < TAPPING_TERM) {
          // tap
          tap_code16(KC_ESC);
        }
        return true;
      }
      return true;
    case TO_DVORAK:
      if (record->event.pressed) {
        tap_code16(KC_LNG2);
        layer_on(DVORAK);
      }
      return false;
      case LCTL_T(KC_ESC):
        if (record->event.pressed) {
          lctl_timer = timer_read();
          // 通常のLCTLの動作を有効にする
          register_mods(MOD_BIT(KC_LCTL));
        } else {
          unregister_mods(MOD_BIT(KC_LCTL));
          if (timer_elapsed(lctl_timer) < TAPPING_TERM) {
            // タップされた場合、ESCを送出
            tap_code(KC_ESC);
          }
        }
        return false; // 他のキーの動作に影響を与えない
      HANDLE_DVORAK_NICOLA(QUOT, Q,    ".");
      HANDLE_DVORAK_NICOLA(COMM, W,    "ka");
      HANDLE_DVORAK_NICOLA(DOT,  E,    "ta");
      HANDLE_DVORAK_NICOLA(P,    R,    "ko");
      HANDLE_DVORAK_NICOLA(Y,    T,    "sa");
      HANDLE_DVORAK_NICOLA(F,    Y,    "ra");
      HANDLE_DVORAK_NICOLA(G,    U,    "ti");
      HANDLE_DVORAK_NICOLA(C,    I,    "ku");
      HANDLE_DVORAK_NICOLA(R,    O,    "tu");
      HANDLE_DVORAK_NICOLA(L,    P,    ",");
      HANDLE_DVORAK_NICOLA(SLSH, LBRC, "dousiyou");
      HANDLE_DVORAK_NICOLA(A,    A,    "u");
      HANDLE_DVORAK_NICOLA(O,    S,    "si");
      HANDLE_DVORAK_NICOLA(E,    D,    "te");
      HANDLE_DVORAK_NICOLA(U,    F,    "ke");
      HANDLE_DVORAK_NICOLA(I,    G,    "se");
      HANDLE_DVORAK_NICOLA(D,    H,    "ha");
      HANDLE_DVORAK_NICOLA(H,    J,    "to");
      HANDLE_DVORAK_NICOLA(T,    K,    "ki");
      HANDLE_DVORAK_NICOLA(N,    L,    "i");
      HANDLE_DVORAK_NICOLA(S,    SCLN, "nn");
      HANDLE_DVORAK_NICOLA(MINS, QUOT, "dousiyou");
      HANDLE_DVORAK_NICOLA(SCLN, Z,    "dousiyou");
      HANDLE_DVORAK_NICOLA(Q,    X,    "hi");
      HANDLE_DVORAK_NICOLA(J,    C,    "su");
      HANDLE_DVORAK_NICOLA(K,    V,    "fu");
      HANDLE_DVORAK_NICOLA(X,    B,    "he");
      HANDLE_DVORAK_NICOLA(B,    N,    "me");
      HANDLE_DVORAK_NICOLA(M,    M,    "so");
      HANDLE_DVORAK_NICOLA(W,    COMM, "ne");
      HANDLE_DVORAK_NICOLA(V,    DOT,  "ho");
      HANDLE_DVORAK_NICOLA(Z,    SLSH, "dousiyou");
      // shifted characters with same-side thumb shift
      HANDLE_NICOLA_KEY(XA,     "xa");
      HANDLE_NICOLA_KEY(E,      "e");
      HANDLE_NICOLA_KEY(RI,     "ri");
      HANDLE_NICOLA_KEY(XYA,    "xya");
      HANDLE_NICOLA_KEY(RE,     "re");
      HANDLE_NICOLA_KEY(YO,     "yo");
      HANDLE_NICOLA_KEY(NI,     "ni");
      HANDLE_NICOLA_KEY(RU,     "ru");
      HANDLE_NICOLA_KEY(MA,     "ma");
      HANDLE_NICOLA_KEY(XE,     "xe");
      HANDLE_NICOLA_KEY(WO,     "wo");
      HANDLE_NICOLA_KEY(A,      "a");
      HANDLE_NICOLA_KEY(NA,     "na");
      HANDLE_NICOLA_KEY(XYU,    "xyu");
      HANDLE_NICOLA_KEY(MO,     "mo");
      HANDLE_NICOLA_KEY(MI,     "mi");
      HANDLE_NICOLA_KEY(O,      "o");
      HANDLE_NICOLA_KEY(NO,     "no");
      HANDLE_NICOLA_KEY(XYO,    "xyo");
      HANDLE_NICOLA_KEY(XTU,    "xtu");
      HANDLE_NICOLA_KEY(XU,     "xu");
      HANDLE_NICOLA_KEY(CHOUON, "-");
      HANDLE_NICOLA_KEY(RO,     "ro");
      HANDLE_NICOLA_KEY(YA,     "ya");
      HANDLE_NICOLA_KEY(XI,     "xi");
      HANDLE_NICOLA_KEY(NU,     "nu");
      HANDLE_NICOLA_KEY(YU,     "yu");
      HANDLE_NICOLA_KEY(MU,     "mu");
      HANDLE_NICOLA_KEY(WA,     "wa");
      HANDLE_NICOLA_KEY(XO,     "xo");
      // shifted characters with opposite-side thumb shift
      HANDLE_NICOLA_KEY(GA, "ga");
      HANDLE_NICOLA_KEY(DA, "da");
      HANDLE_NICOLA_KEY(GO, "go");
      HANDLE_NICOLA_KEY(ZA, "za");
      HANDLE_NICOLA_KEY(PA, "pa");
      HANDLE_NICOLA_KEY(DI, "di");
      HANDLE_NICOLA_KEY(GU, "gu");
      HANDLE_NICOLA_KEY(DU, "du");
      HANDLE_NICOLA_KEY(PI, "pi");
      HANDLE_NICOLA_KEY(VU, "vu");
      HANDLE_NICOLA_KEY(JI, "ji");
      HANDLE_NICOLA_KEY(DE, "de");
      HANDLE_NICOLA_KEY(GE, "ge");
      HANDLE_NICOLA_KEY(ZE, "ze");
      HANDLE_NICOLA_KEY(BA, "ba");
      HANDLE_NICOLA_KEY(DO, "do");
      HANDLE_NICOLA_KEY(GI, "gi");
      HANDLE_NICOLA_KEY(PO, "po");
      HANDLE_NICOLA_KEY(BI, "bi");
      HANDLE_NICOLA_KEY(ZU, "zu");
      HANDLE_NICOLA_KEY(BU, "bu");
      HANDLE_NICOLA_KEY(BE, "be");
      HANDLE_NICOLA_KEY(PU, "pu");
      HANDLE_NICOLA_KEY(ZO, "zo");
      HANDLE_NICOLA_KEY(PE, "pe");
      HANDLE_NICOLA_KEY(BO, "bo");
    default:
      return true;
  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [NICOLA] = LAYOUT_universal(
   LGUI_T(KC_TAB),  KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y,                                  KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH,
   LCTL_T(KC_ESC),  KC_A,    KC_O,    KC_E,   KC_U, KC_I,                                  KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS,
   LSFT_T(KC_ESC),  KC_SCLN, KC_Q,    KC_J,   KC_K, KC_X,                                  KC_B, KC_M, KC_W, KC_V, KC_Z, RSFT_T(KC_ENT),
   LSFT_T(KC_CAPS), KC_LALT, TO_CMD_QWERTY_ESC, LT(2,KC_SPC), LCTL_NICOLA,   TO_DVORAK, RGUI_T(KC_SPC), _______, _______, KC_BTN1
  ),
  [DVORAK] = LAYOUT_universal(
   _______, _______, _______, _______, _______, _______,                                   _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______,                                   _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______,                                   _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______,                                                     _______, _______, _______, _______, _______
  ),

  [2] = LAYOUT_universal(
         KC_TILDE ,  S(KC_1) ,  S(KC_2) ,  S(KC_3) ,  S(KC_4) , S(KC_5)  ,                                       S(KC_6)   ,S(KC_7)   ,S(KC_8)   ,S(KC_9)   ,S(KC_0)   , KC_EQL   ,
         KC_LBRC  ,  KC_1    ,  KC_2    ,  KC_3    ,  KC_4    ,  KC_5    ,                                         KC_6    ,  KC_7    ,  KC_8    ,  KC_9    ,  KC_0    , KC_RBRC  ,
         _______  ,  _______ ,  KC_BTN2 ,  KC_BTN3 , KC_BTN1  , KC_LPRN  ,                                        KC_RPRN  , KC_BSLS  , _______  , _______  , _______  , _______  ,
                _______  , _______ ,      _______  , _______  , _______  ,                              _______  , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______  ,_______,        _______, KC_GRAVE, KC_QUOT  , KC_QUES ,                                          KC_EXLM , _______ , _______ , _______ , _______ , _______  ,
    _______  ,KC_BSLS, KC_LCBR  , KC_LBRC , KC_LPRN  , KC_LABK ,                                               KC_RABK , KC_RPRN  , KC_RBRC, KC_RCBR , KC_SLSH  , _______ ,
    _______  ,KC_SCLN, _______  , KC_UNDS , KC_MINS  , KC_PIPE ,                                               KC_EQL  , KC_PLUS, KC_MINS  , KC_ASTR , KC_SLSH, _______ ,
                  _______ , _______  ,     _______ , _______  , _______  ,                              _______  , _______  , _______       , _______  , _______
  ),
  [4] = LAYOUT_universal(
    _______  , _______  , KC_7     , KC_8    , KC_9  , _______ ,                                        _______  , _______  ,  _______ , _______  ,  _______  , _______ ,
    _______  , KC_SLSH  , KC_4     , KC_5    , KC_6  , KC_ASTR ,                                        _______  , _______  , _______  , _______  ,  _______  , _______ ,
    _______  , KC_MINS  , KC_1     , KC_2    , KC_3  , KC_PLUS ,                                        _______  , KC_LEFT  , KC_DOWN  , KC_RIGHT  , _______  , _______ ,
                  KC_0  , KC_0 ,   KC_DOT , KC_ENT  , KC_BSPC   ,                                        KC_EQL  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

void keyboard_post_init_user(void) {
    default_layer_set(0);
}

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
