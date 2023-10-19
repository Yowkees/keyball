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
  NICOLA_KA,
  NICOLA_TA,
  NICOLA_KO,
  NICOLA_SA,
  NICOLA_RA,
  NICOLA_TI,
  NICOLA_KU,
  NICOLA_TU,
  NICOLA_SI,
  NICOLA_TE,
  NICOLA_KE,
  NICOLA_SE,
  NICOLA_HA,
  NICOLA_TO,
  NICOLA_KI,
  NICOLA_NN,
  NICOLA_HI,
  NICOLA_SU,
  NICOLA_FU,
  NICOLA_HE,
  NICOLA_ME,
  NICOLA_SO,
  NICOLA_NE,
  NICOLA_HO,
  MID_DOT,
};


const uint32_t PROGMEM unicode_map[] = {
    [MID_DOT]  = 0x30FB  // ・
};

#define HANDLE_NICOLA_KEY(keyname, keystring) \
    case NICOLA_##keyname: \
        if (record->event.pressed) { \
            SEND_STRING(keystring); \
        } \
        return false

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t lctl_timer;

  switch (keycode) {
    case LCTL_NICOLA:
      if (record->event.pressed) {
        lctl_timer = timer_read();
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LCTL);
        if (timer_elapsed(lctl_timer) < TAPPING_TERM) {
          tap_code16(KC_LANG1);
          layer_on(4);
        }
      }
    case TO_DVORAK:
      if (record->event.pressed) {
        tap_code16(KC_LANG2);
        layer_off(4);
      }
      return false;
      HANDLE_NICOLA_KEY(KA, "ka");
      HANDLE_NICOLA_KEY(TA, "ta");
      HANDLE_NICOLA_KEY(KO, "ko");
      HANDLE_NICOLA_KEY(SA, "sa");
      HANDLE_NICOLA_KEY(RA, "ra");
      HANDLE_NICOLA_KEY(TI, "ti");
      HANDLE_NICOLA_KEY(KU, "ku");
      HANDLE_NICOLA_KEY(TU, "tu");
      HANDLE_NICOLA_KEY(SI, "si");
      HANDLE_NICOLA_KEY(TE, "te");
      HANDLE_NICOLA_KEY(KE, "ke");
      HANDLE_NICOLA_KEY(SE, "se");
      HANDLE_NICOLA_KEY(HA, "ha");
      HANDLE_NICOLA_KEY(TO, "to");
      HANDLE_NICOLA_KEY(KI, "ki");
      HANDLE_NICOLA_KEY(NN, "nn");
      HANDLE_NICOLA_KEY(HI, "hi");
      HANDLE_NICOLA_KEY(SU, "su");
      HANDLE_NICOLA_KEY(FU, "fu");
      HANDLE_NICOLA_KEY(HE, "he");
      HANDLE_NICOLA_KEY(ME, "me");
      HANDLE_NICOLA_KEY(SO, "so");
      HANDLE_NICOLA_KEY(NE, "ne");
      HANDLE_NICOLA_KEY(HO, "ho");
    default:
      return true;
  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    LGUI_T(KC_TAB), KC_QUOT  , KC_COMM  , KC_DOT   , KC_P     , KC_Y     ,                                        KC_F     , KC_G     , KC_C     , KC_R     , KC_L     , KC_SLSH  ,
    LCTL_T(KC_ESC), KC_A     , KC_O     , KC_E     , KC_U     , KC_I     ,                                        KC_D     , KC_H     , KC_T     , KC_N     , KC_S     , KC_MINS  ,
    KC_LSFT       , KC_SCLN  , KC_Q     , KC_J     , KC_K     , KC_X     ,                                        KC_B     , KC_M     , KC_W     , KC_V     , KC_Z     , RSFT_T(KC_BTN1),
       LSFT_T(KC_CAPS), KC_LALT,     LT(5,KC_BTN1), LT(1,KC_SPC), LCTL_NICOLA,                    LT(2, TO_DVORAK), RGUI_T(KC_SPC), _______ ,   _______,  KC_ENT
  ),

  [1] = LAYOUT_universal(
         KC_TILDE ,  S(KC_1) ,  S(KC_2) ,  S(KC_3) ,  S(KC_4) , S(KC_5)  ,                                       S(KC_6)   ,S(KC_7)   ,S(KC_8)   ,S(KC_9)   ,S(KC_0)   , KC_EQL   ,
         KC_LBRC  ,  KC_1    ,  KC_2    ,  KC_3    ,  KC_4    ,  KC_5    ,                                         KC_6    ,  KC_7    ,  KC_8    ,  KC_9    ,  KC_0    , KC_RBRC  ,
         _______  ,  _______ ,  KC_BTN2 ,  KC_BTN3 , KC_BTN1  , KC_LPRN  ,                                        KC_RPRN  , KC_BSLS  , _______  , _______  , _______  , _______  ,
                _______  , _______ ,      _______  , _______  , _______  ,                              _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,_______,        _______, KC_GRAVE, KC_QUOT  , KC_QUES ,                                          KC_EXLM , _______ , _______ , _______ , _______ , _______  ,
    _______  ,KC_BSLS, KC_LCBR  , KC_LBRC , KC_LPRN  , KC_LABK ,                                               KC_RABK , KC_RPRN  , KC_RBRC, KC_RCBR , KC_SLSH  , _______ ,
    _______  ,KC_SCLN, _______  , KC_UNDS , KC_MINS  , KC_PIPE ,                                               KC_EQL  , KC_PLUS, KC_MINS  , KC_ASTR , KC_SLSH, _______ ,
                  _______ , _______  ,     _______ , _______  , _______  ,                              _______  , _______  , _______       , _______  , _______
  ),
  [3] = LAYOUT_universal(
    _______  , _______  , KC_7     , KC_8    , KC_9  , _______ ,                                        _______  , _______  ,  _______ , _______  ,  _______  , _______ ,
    _______  , KC_SLSH  , KC_4     , KC_5    , KC_6  , KC_ASTR ,                                        _______  , _______  , _______  , _______  ,  _______  , _______ ,
    _______  , KC_MINS  , KC_1     , KC_2    , KC_3  , KC_PLUS ,                                        _______  , KC_LEFT  , KC_DOWN  , KC_RIGHT  , _______  , _______ ,
                  KC_0  , KC_0 ,   KC_DOT , KC_ENT  , KC_BSPC   ,                                        KC_EQL  , _______  , _______       , _______  , _______
  ),
  [4] = LAYOUT_universal(
    _______  , KC_DOT , NICOLA_KA , NICOLA_TA , NICOLA_KO , NICOLA_SA ,                                        NICOLA_RA , NICOLA_TI  ,  NICOLA_KU , NICOLA_TU  ,  KC_COMM , _______ ,
    _______  , KC_U   , NICOLA_SI   , NICOLA_TE , NICOLA_KE , NICOLA_SE ,                                NICOLA_HA , NICOLA_TO , NICOLA_KI , KC_I      ,  NICOLA_NN , _______ ,
    _______  , MID_DOT, NICOLA_HI, NICOLA_SU, NICOLA_FU, NICOLA_HE,                                      NICOLA_ME , NICOLA_SO , NICOLA_NE , NICOLA_HO ,  UC(0x30FB)   , _______ ,
    _______  , _______ ,   LT(5, KC_LGUI) , LT(1,KC_SPC)  , _______   ,                                        TO_DVORAK  , _______  , _______       , _______  , _______
  ),
  [5] = LAYOUT_universal(
    _______  , G(KC_Q)  , G(KC_W)  , G(KC_E) , G(KC_R)  , G(KC_T)  ,                                             G(KC_Y)   , G(KC_U)  , G(KC_I)    , G(KC_O)   , G(KC_P)    , _______   ,
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
