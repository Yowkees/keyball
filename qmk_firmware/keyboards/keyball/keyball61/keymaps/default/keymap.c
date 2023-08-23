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

#include <print.h>
void matrix_init_kb(void)
{
  debug_enable = true;
  debug_matrix = true;
  debug_mouse = true;
}

#include "quantum.h"

enum custome_keycodes
{
  CKC_MAC_CMD = KEYBALL_SAFE_RANGE
};

enum layer_names
{
  _BASE,
  _WIN,
  _MAC,
  _ARROW,
  _MOUSE,
  _SET,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [_BASE] = LAYOUT(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_EQL  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LBRC  ,              KC_RBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_BSLS  ,
    KC_LCTL  , KC_LCTL  , KC_LALT  , KC_LGUI,LT(_SET,KC_LNG2),KC_SPC,LT(_ARROW,KC_LNG1),    KC_BSPC,LT(_MOUSE,KC_ENT)                                     , KC_RALT  , S(C(RCMD(KC_4)))
  ),

  [_WIN] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    KC_LCTL  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______                                   , _______  , _______
  ),

  [_MAC] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    KC_LGUI  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______                                   , _______  , _______
  ),

  [_ARROW] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  ,C(KC_UP)  , _______  , _______  ,                                  _______  , _______  , KC_UP    , _______  , _______  , _______  ,
    _______  , _______  ,C(KC_LEFT),C(KC_DOWN),C(KC_RIGHT), _______ ,                                  _______  , KC_LEFT  , KC_DOWN  , KC_RIGHT , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            KC_DEL  , _______                                   , _______  , _______
  ),

  [_MOUSE] = LAYOUT(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , _______  , _______     , _______     , _______     , _______  ,                                  _______  , _______  , _______    , _______  , _______  , KC_F12   ,
    _______  , _______  , _______     , _______     , _______     ,_______,                                  _______  , KC_BTN1    , KC_BTN2  , _______  , _______  , _______  ,
    _______  , _______  , _______     , _______     , _______     ,_______, _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______     , _______   , _______  , _______  , _______  ,             KC_DEL  , _______                                   ,  _______  , _______
  ),

  [_SET] = LAYOUT(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , KBC_RST  ,            KBC_RST  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    _______  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC                                  ,  _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state)
{
  // Auto enable scroll mode when the highest layer is 3
  keyball_set_scroll_mode(get_highest_layer(state) == _MOUSE);
  return state;
}

#ifdef OLED_ENABLE
#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
}
#endif

void pointing_device_init_user(void)
{
  // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
  set_auto_mouse_enable(true); // always required before the auto mouse feature will work
}

#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#include <tmk_core/protocol/usb_device_state.h>
#endif

uint32_t execute_os_switching(uint32_t trigger_time, void *cb_arg)
{
  detected_host_os();
  os_variant_t detected = detected_host_os();
  if (detected == OS_MACOS || detected == OS_IOS)
  {
    layer_on(_MAC);
    layer_off(_WIN);
    default_layer_set(_MAC);
    layer_move(_MAC);
    return 0;
  }
  else
  {
    layer_on(_WIN);
    layer_off(_MAC);
    default_layer_set(_WIN);
    layer_move(_WIN);
    return 0;
  }

  return 0;
}

void notify_usb_device_state_change_user(enum usb_device_state usb_device_state)
{
  // this is the USB reset event - so reset the os detection counter.
  if (USB_DEVICE_STATE_INIT == usb_device_state)
  {
    erase_wlength_data();
    // usb setup packets should be done by this time (500ms by the spec + some slack time).
    defer_exec(1000, execute_os_switching, NULL);
  }
}
