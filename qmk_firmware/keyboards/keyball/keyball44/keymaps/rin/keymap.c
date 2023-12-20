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

enum custom_keycodes {
  LCTL_NICOLA = SAFE_RANGE,
  TO_DVORAK,
  TO_CMD_QWERTY_ESC,
  NICOLA_KA,
  NICOLA_TA,
  NICOLA_KO,
  NICOLA_SA,
  NICOLA_RA,
  NICOLA_TI,
  NICOLA_KU,
  NICOLA_TU,
  NICOLA_U,
  NICOLA_SI,
  NICOLA_TE,
  NICOLA_KE,
  NICOLA_SE,
  NICOLA_HA,
  NICOLA_TO,
  NICOLA_KI,
  NICOLA_I,
  NICOLA_NN,
  NICOLA_HI,
  NICOLA_SU,
  NICOLA_FU,
  NICOLA_HE,
  NICOLA_ME,
  NICOLA_SO,
  NICOLA_NE,
  NICOLA_HO,
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

const uint16_t PROGMEM nicola_xa[]     = {TO_CMD_QWERTY_ESC, KC_DOT, COMBO_END};
const uint16_t PROGMEM nicola_e[]      = {TO_CMD_QWERTY_ESC, NICOLA_KA, COMBO_END};
const uint16_t PROGMEM nicola_ri[]     = {TO_CMD_QWERTY_ESC, NICOLA_TA, COMBO_END};
const uint16_t PROGMEM nicola_xya[]    = {TO_CMD_QWERTY_ESC, NICOLA_KO, COMBO_END};
const uint16_t PROGMEM nicola_re[]     = {TO_CMD_QWERTY_ESC, NICOLA_SA, COMBO_END};
const uint16_t PROGMEM nicola_yo[]     = {RGUI_T(KC_SPC), NICOLA_RA, COMBO_END};
const uint16_t PROGMEM nicola_ni[]     = {RGUI_T(KC_SPC), NICOLA_TI, COMBO_END};
const uint16_t PROGMEM nicola_ru[]     = {RGUI_T(KC_SPC), NICOLA_KU, COMBO_END};
const uint16_t PROGMEM nicola_ma[]     = {RGUI_T(KC_SPC), NICOLA_TU, COMBO_END};
const uint16_t PROGMEM nicola_xe[]     = {RGUI_T(KC_SPC), KC_COMM, COMBO_END};
const uint16_t PROGMEM nicola_wo[]     = {TO_CMD_QWERTY_ESC, NICOLA_U, COMBO_END};
const uint16_t PROGMEM nicola_a[]      = {TO_CMD_QWERTY_ESC, NICOLA_SI, COMBO_END};
const uint16_t PROGMEM nicola_na[]     = {TO_CMD_QWERTY_ESC, NICOLA_TE, COMBO_END};
const uint16_t PROGMEM nicola_xyu[]    = {TO_CMD_QWERTY_ESC, NICOLA_KE, COMBO_END};
const uint16_t PROGMEM nicola_mo[]     = {TO_CMD_QWERTY_ESC, NICOLA_SE, COMBO_END};
const uint16_t PROGMEM nicola_mi[]     = {RGUI_T(KC_SPC), NICOLA_HA, COMBO_END};
const uint16_t PROGMEM nicola_o[]      = {RGUI_T(KC_SPC), NICOLA_TO, COMBO_END};
const uint16_t PROGMEM nicola_no[]     = {RGUI_T(KC_SPC), NICOLA_KI, COMBO_END};
const uint16_t PROGMEM nicola_xyo[]    = {RGUI_T(KC_SPC), NICOLA_I, COMBO_END};
const uint16_t PROGMEM nicola_xtu[]    = {RGUI_T(KC_SPC), NICOLA_NN, COMBO_END};
const uint16_t PROGMEM nicola_xu[]     = {RGUI_T(KC_SPC), MID_DOT, COMBO_END};
const uint16_t PROGMEM nicola_chouon[] = {TO_CMD_QWERTY_ESC, NICOLA_HI, COMBO_END};
const uint16_t PROGMEM nicola_ro[]     = {TO_CMD_QWERTY_ESC, NICOLA_SU, COMBO_END};
const uint16_t PROGMEM nicola_ya[]     = {TO_CMD_QWERTY_ESC, NICOLA_FU, COMBO_END};
const uint16_t PROGMEM nicola_xi[]     = {TO_CMD_QWERTY_ESC, NICOLA_HE, COMBO_END};
const uint16_t PROGMEM nicola_nu[]     = {RGUI_T(KC_SPC), NICOLA_ME, COMBO_END};
const uint16_t PROGMEM nicola_yu[]     = {RGUI_T(KC_SPC), NICOLA_SO, COMBO_END};
const uint16_t PROGMEM nicola_mu[]     = {RGUI_T(KC_SPC), NICOLA_NE, COMBO_END};
const uint16_t PROGMEM nicola_wa[]     = {RGUI_T(KC_SPC), NICOLA_HO, COMBO_END};
const uint16_t PROGMEM nicola_xo[]     = {RGUI_T(KC_SPC), UC(0x30FB), COMBO_END};
const uint16_t PROGMEM nicola_ga[]     = {RGUI_T(KC_SPC), NICOLA_KA, COMBO_END};
const uint16_t PROGMEM nicola_da[]     = {RGUI_T(KC_SPC), NICOLA_TA, COMBO_END};
const uint16_t PROGMEM nicola_go[]     = {RGUI_T(KC_SPC), NICOLA_KO, COMBO_END};
const uint16_t PROGMEM nicola_za[]     = {RGUI_T(KC_SPC), NICOLA_SA, COMBO_END};
const uint16_t PROGMEM nicola_pa[]     = {TO_CMD_QWERTY_ESC, NICOLA_RA, COMBO_END};
const uint16_t PROGMEM nicola_di[]     = {TO_CMD_QWERTY_ESC, NICOLA_TI, COMBO_END};
const uint16_t PROGMEM nicola_gu[]     = {TO_CMD_QWERTY_ESC, NICOLA_KU, COMBO_END};
const uint16_t PROGMEM nicola_du[]     = {TO_CMD_QWERTY_ESC, NICOLA_TU, COMBO_END};
const uint16_t PROGMEM nicola_pi[]     = {TO_CMD_QWERTY_ESC, KC_COMM, COMBO_END};
const uint16_t PROGMEM nicola_vu[]     = {RGUI_T(KC_SPC), KC_U, COMBO_END};
const uint16_t PROGMEM nicola_ji[]     = {RGUI_T(KC_SPC), NICOLA_SI, COMBO_END};
const uint16_t PROGMEM nicola_de[]     = {RGUI_T(KC_SPC), NICOLA_TE, COMBO_END};
const uint16_t PROGMEM nicola_ge[]     = {RGUI_T(KC_SPC), NICOLA_KE, COMBO_END};
const uint16_t PROGMEM nicola_ze[]     = {RGUI_T(KC_SPC), NICOLA_SE, COMBO_END};
const uint16_t PROGMEM nicola_ba[]     = {TO_CMD_QWERTY_ESC, NICOLA_HA, COMBO_END};
const uint16_t PROGMEM nicola_do[]     = {TO_CMD_QWERTY_ESC, NICOLA_TO, COMBO_END};
const uint16_t PROGMEM nicola_gi[]     = {TO_CMD_QWERTY_ESC, NICOLA_KI, COMBO_END};
const uint16_t PROGMEM nicola_po[]     = {TO_CMD_QWERTY_ESC, NICOLA_I, COMBO_END};
const uint16_t PROGMEM nicola_bi[]     = {RGUI_T(KC_SPC), NICOLA_HI, COMBO_END};
const uint16_t PROGMEM nicola_zu[]     = {RGUI_T(KC_SPC), NICOLA_SU, COMBO_END};
const uint16_t PROGMEM nicola_bu[]     = {RGUI_T(KC_SPC), NICOLA_FU, COMBO_END};
const uint16_t PROGMEM nicola_be[]     = {RGUI_T(KC_SPC), NICOLA_HE, COMBO_END};
const uint16_t PROGMEM nicola_pu[]     = {TO_CMD_QWERTY_ESC, NICOLA_ME, COMBO_END};
const uint16_t PROGMEM nicola_zo[]     = {TO_CMD_QWERTY_ESC, NICOLA_SO, COMBO_END};
const uint16_t PROGMEM nicola_pe[]     = {TO_CMD_QWERTY_ESC, NICOLA_NE, COMBO_END};
const uint16_t PROGMEM nicola_bo[]     = {TO_CMD_QWERTY_ESC, NICOLA_HO, COMBO_END};

combo_t key_combos[] = {
// shifted characters with same-side thumb shift
    COMBO(nicola_xa, NICOLA_XA),
    COMBO(nicola_e, NICOLA_E),
    COMBO(nicola_ri, NICOLA_RI),
    COMBO(nicola_xya, NICOLA_XYA),
    COMBO(nicola_re, NICOLA_RE),
    COMBO(nicola_yo, NICOLA_YO),
    COMBO(nicola_ni, NICOLA_NI),
    COMBO(nicola_ru, NICOLA_RU),
    COMBO(nicola_ma, NICOLA_MA),
    COMBO(nicola_xe, NICOLA_XE),
    COMBO(nicola_wo, NICOLA_WO),
    COMBO(nicola_a, NICOLA_A),
    COMBO(nicola_na, NICOLA_NA),
    COMBO(nicola_xyu, NICOLA_XYU),
    COMBO(nicola_mo, NICOLA_MO),
    COMBO(nicola_mi, NICOLA_MI),
    COMBO(nicola_o, NICOLA_O),
    COMBO(nicola_no, NICOLA_NO),
    COMBO(nicola_xyo, NICOLA_XYO),
    COMBO(nicola_xtu, NICOLA_XTU),
    COMBO(nicola_xu, NICOLA_XU),
    COMBO(nicola_chouon, NICOLA_CHOUON),
    COMBO(nicola_ro, NICOLA_RO),
    COMBO(nicola_ya, NICOLA_YA),
    COMBO(nicola_xi, NICOLA_XI),
    COMBO(nicola_nu, NICOLA_NU),
    COMBO(nicola_yu, NICOLA_YU),
    COMBO(nicola_mu, NICOLA_MU),
    COMBO(nicola_wa, NICOLA_WA),
    COMBO(nicola_xo, NICOLA_XO),
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

static bool gui_shortcut_registered = false;
static bool ctrl_shortcut_registered = false;
uint8_t mod_state;

#define HANDLE_DVORAK_KEY(keyname, keycode, keycode_gui)  \
    case DVRK_##keyname: \
    { \
        if (record->event.pressed) { \
            if (mod_state & MOD_MASK_GUI) { \
                del_mods(MOD_MASK_GUI); \
                register_code16(LGUI(keycode_gui)); \
                set_mods(mod_state); \
                gui_shortcut_registered = true; \
                return false; \
            } \
            tap_code16(keycode); \
        } else { \
            if (gui_shortcut_registered) { \
                set_mods(mod_state); \
                unregister_code16(LGUI(keycode_gui));        \
                gui_shortcut_registered = false; \
                return false; \
            } \
        } \
        return true; \
    } \

#define HANDLE_NICOLA_KEY(keyname, keystring) \
    case NICOLA_##keyname: \
        if (record->event.pressed) { \
            SEND_STRING(keystring); \
        } \
        return false

#define HANDLE_NICOLA_KEY_CTRL(keyname, keystring, keycode_gui, keycode_ctrl) \
    case NICOLA_##keyname: \
    { \
        if (record->event.pressed) { \
            if (mod_state & MOD_MASK_GUI) { \
                del_mods(MOD_MASK_GUI); \
                register_code16(LGUI(keycode_gui)); \
                set_mods(mod_state); \
                gui_shortcut_registered = true; \
                return false; \
            } else if (mod_state & MOD_MASK_CTRL) { \
                del_mods(MOD_MASK_CTRL); \
                register_code16(keycode_ctrl); \
                set_mods(mod_state); \
                ctrl_shortcut_registered = true; \
                return false; \
            } \
        } else { \
            if (gui_shortcut_registered) { \
                set_mods(mod_state); \
                unregister_code16(LGUI(keycode_gui));        \
                gui_shortcut_registered = false; \
                return false; \
            } else if (ctrl_shortcut_registered) { \
                set_mods(mod_state); \
                unregister_code16(keycode_ctrl); \
                ctrl_shortcut_registered = false; \
                return false; \
            } \
        } \
            SEND_STRING(keystring); \
        return true; \
    } \

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t keyhold_timer;

  mod_state = get_mods();
  switch (keycode) {
    case LCTL_NICOLA:
      if (record->event.pressed) {
        keyhold_timer = timer_read();
      } else {
        if (timer_elapsed(keyhold_timer) < TAPPING_TERM) {
          tap_code16(KC_LNG1);
          layer_off(1);
        }
      }
    case TO_CMD_QWERTY_ESC:
      if (record->event.pressed) {
        keyhold_timer = timer_read();

        add_mods(MOD_MASK_GUI); \
        layer_on(1);
      } else {
        del_mods(MOD_MASK_GUI); \
        layer_off(1);

        if (timer_elapsed(keyhold_timer) < TAPPING_TERM) {
          // tap
          tap_code16(KC_ESC);
        }
      }
      return true;
    case TO_DVORAK:
      if (record->event.pressed) {
        tap_code16(KC_LNG2);
        layer_on(1);
      }
      return false;
      case LCTL_T(KC_ESC):
        if (record->event.pressed) {
          keyhold_timer = timer_read();
          // 通常のLCTLの動作を有効にする
          register_mods(MOD_BIT(KC_LCTL));
        } else {
          unregister_mods(MOD_BIT(KC_LCTL));
          if (timer_elapsed(keyhold_timer) < TAPPING_TERM) {
            // タップされた場合、ESCを送出
            tap_code(KC_ESC);
          }
        }
        return false; // 他のキーの動作に影響を与えない
      HANDLE_NICOLA_KEY(KA, "ka");
      HANDLE_NICOLA_KEY(TA, "ta");
      HANDLE_NICOLA_KEY_CTRL(KO, "ko", KC_R, LCTL(KC_P));
      HANDLE_NICOLA_KEY_CTRL(SA, "sa", KC_T, LCTL(KC_Y));
      HANDLE_NICOLA_KEY_CTRL(RA, "ra", KC_Y, LCTL(KC_F));
      HANDLE_NICOLA_KEY(TI, "ti");
      HANDLE_NICOLA_KEY(KU, "ku");
      HANDLE_NICOLA_KEY(TU, "tu");
      HANDLE_NICOLA_KEY_CTRL(U, "u", KC_LEFT, LCTL(KC_A));
      HANDLE_NICOLA_KEY(SI, "si");
      HANDLE_NICOLA_KEY_CTRL(TE, "te", KC_D, LCTL(KC_E));
      HANDLE_NICOLA_KEY(KE, "ke");
      HANDLE_NICOLA_KEY_CTRL(SE, "se", KC_G, KC_TAB);
      HANDLE_NICOLA_KEY_CTRL(HA, "ha", KC_H, LCTL(KC_D));
      HANDLE_NICOLA_KEY_CTRL(TO, "to", KC_J, LCTL(KC_H));
      HANDLE_NICOLA_KEY_CTRL(KI, "ki", KC_K, LCTL(KC_T));
      HANDLE_NICOLA_KEY_CTRL(I, "i", KC_L, LCTL(KC_N));
      HANDLE_NICOLA_KEY(NN, "nn");
      HANDLE_NICOLA_KEY(HI, "hi");
      HANDLE_NICOLA_KEY(SU, "su");
      HANDLE_NICOLA_KEY_CTRL(FU, "fu", KC_V, LCTL(KC_K));
      HANDLE_NICOLA_KEY(HE, "he");
      HANDLE_NICOLA_KEY_CTRL(ME, "me", KC_N, LCTL(KC_B));
      HANDLE_NICOLA_KEY_CTRL(SO, "so", KC_M, KC_ENT);
      HANDLE_NICOLA_KEY(NE, "ne");
      HANDLE_NICOLA_KEY(HO, "ho");
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
  [0] = LAYOUT_universal(
   LGUI_T(KC_TAB), KC_DOT , NICOLA_KA , NICOLA_TA , NICOLA_KO , NICOLA_SA ,                                        NICOLA_RA , NICOLA_TI  ,  NICOLA_KU , NICOLA_TU  ,  KC_COMM , _______ ,
   LCTL_T(KC_ESC), NICOLA_U   , NICOLA_SI   , NICOLA_TE , NICOLA_KE , NICOLA_SE ,                                NICOLA_HA , NICOLA_TO , NICOLA_KI , NICOLA_I      ,  NICOLA_NN , _______ ,
   LSFT_T(KC_ESC)  , MID_DOT, NICOLA_HI, NICOLA_SU, NICOLA_FU, NICOLA_HE,                                      NICOLA_ME , NICOLA_SO , NICOLA_NE , NICOLA_HO ,  UC(0x30FB)   , RSFT_T(KC_ENT) ,
   LSFT_T(KC_CAPS)  , KC_LALT ,   TO_CMD_QWERTY_ESC , LT(2,KC_SPC)  , LCTL_NICOLA  ,                                        TO_DVORAK  , RGUI_T(KC_SPC)  , _______       , _______  , KC_BTN1
  ),
  [1] = LAYOUT_universal(
    LGUI_T(KC_TAB), KC_QUOT  , KC_COMM  , KC_DOT   , KC_P     , KC_Y     ,                                        KC_F     , KC_G     , KC_C     , KC_R     , KC_L     , KC_SLSH  ,
    KC_LCTL,        KC_A     , KC_O     , KC_E     , KC_U     , KC_I     ,                                        KC_D     , KC_H     , KC_T     , KC_N     , KC_S     , KC_MINS  ,
    LSFT_T(KC_ESC), KC_SCLN  , KC_Q     , KC_J     , KC_K     , KC_X     ,                                        KC_B     , KC_M     , KC_W     , KC_V     , KC_Z     , RSFT_T(KC_ENT),
       LSFT_T(KC_CAPS), KC_LALT,     _______, LT(1,KC_SPC), _______,                            LT(2, TO_DVORAK), _______, _______ ,   _______,  KC_BTN1
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
  [5] = LAYOUT_universal(
    G(KC_TAB), G(KC_Q)  , G(KC_W)  , G(KC_E) , G(KC_R)  , G(KC_T)  ,                                             G(KC_Y)   , G(KC_U)  , G(KC_I)    , G(KC_O)   , G(KC_P)    , _______   ,
    _______  , G(KC_A)  , G(KC_S)  , G(KC_D) , G(KC_F)  , G(KC_G)  ,                                             G(KC_H)   , G(KC_J)  , G(KC_K)    , G(KC_L)   , G(KC_SCLN) , G(KC_QUOT),
    _______  , G(KC_Z)  , G(KC_X)  , G(KC_C) , G(KC_V)  , G(KC_B)  ,                                             G(KC_N)   , G(KC_M)  , G(KC_COMM) , G(KC_DOT) , G(KC_SLSH) , _______   ,
                   _______ , _______ ,     _______ , _______  , _______  ,                           G(KC_LBRC)  , G(KC_RBRC)  , _______       , _______  , _______
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
