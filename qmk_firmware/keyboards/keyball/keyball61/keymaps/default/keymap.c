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
void matrix_init_kb(void) {
  debug_enable = true;
  debug_matrix = true;
  debug_mouse = true;
}

#include "quantum.h"

enum layer_names {
  _BASE,
  _WIN,
  _MAC,
  _ARROW,
  _MOUSE,
  _SET,
};

enum custome_keycodes { CST_IME_TG = KEYBALL_SAFE_RANGE };

bool ime_mode = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [_BASE] = LAYOUT(
    QK_GESC  , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_EQL  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LBRC  ,              KC_RBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_BSLS  ,
    KC_LCTL  , KC_LGUI  , KC_LALT,LT(_SET,KC_GRV),CST_IME_TG, KC_SPC   , LT(_ARROW,KC_DEL),      KC_BSPC,LT(_ARROW,KC_ENT)                          , MO(_ARROW) , S(C(RCMD(KC_4)))
  ),

  [_WIN] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    KC_LCTL  , KC_LGUI  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______                                   , _______  , _______
  ),

  [_MAC] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    KC_LGUI  , KC_LCTL  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______                                   , _______  , _______
  ),

  [_ARROW] = LAYOUT(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , _______  , _______  ,C(KC_UP)  , _______  , _______  ,                                  _______  , _______  , KC_UP    , _______  , _______  , KC_F12  ,
    _______  , _______  ,C(KC_LEFT),C(KC_DOWN),C(KC_RIGHT), _______ ,                                  _______  , KC_LEFT  , KC_DOWN  , KC_RIGHT , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______                                   , _______  , _______
  ),

  [_MOUSE] = LAYOUT(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______     , _______     , _______     , _______  ,                                  _______  , _______  , _______    , _______  , _______  , _______   ,
    _______  , _______  , _______     , _______     , _______     ,_______,                                  _______  , KC_BTN1    , KC_BTN2  , _______  , _______  , _______  ,
    _______  , _______  , _______     , _______     , _______     ,_______, _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______     , _______   , _______  , _______  , _______  ,             _______  , _______                                   ,  _______  , _______
  ),

  [_SET] = LAYOUT(
    TG(_SET) , TG(_WIN) , TG(_MAC) , _______ , _______  , _______  ,                                  _______  , _______  , _______  , _______ , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______ , _______  , _______  ,
    _______  , _______  , SCRL_DVI  , SCRL_TO  , CPI_I1K  , CPI_I100  ,                                  _______  ,  KC_HOME  , KC_PGUP  , KC_PGDN  , KC_END , _______  ,
    _______  , _______  , SCRL_DVD , SCRL_MO ,   CPI_D1K  , CPI_D100  , _______  ,            _______  , _______  , _______  , _______  , _______   , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______    , _______  , _______  ,              _______  , _______                                  ,  _______  , _______
  )
};
// clang-format on

// clang-format off
static const char PROGMEM logos[][128] = {
  // keymap for default
  [_BASE] = {},
  [_WIN] = {
    0x00, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00,
    0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00,
    0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00,
    0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00,
    0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00,
    0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00,
    0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00,  },
  [_MAC] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x78, 0x7C, 0x3E, 0x1E, 0x9F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
    0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1E, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x0F, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00,  },
  [_ARROW] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x03, 0x0F, 0x1F, 0x3F, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
  [_MOUSE] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xFC, 0xFC, 0x0E, 0x02, 0xF0, 0xF0,
    0xF0, 0xF0, 0x06, 0x0E, 0xFC, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xE0, 0xE7, 0x0F,
    0x0F, 0xE7, 0xE0, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x0F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  },
  [_SET] = {
    0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x10, 0x30, 0x60, 0xC0, 0x78, 0x3C, 0x04, 0x04,
    0x04, 0x04, 0x3C, 0x78, 0xC0, 0x60, 0x30, 0x10, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xE0, 0x30, 0x33, 0x36, 0x1C, 0x08, 0xC0, 0xF0, 0x1C, 0x0C, 0x06, 0x02, 0x03, 0x03,
    0x03, 0x03, 0x02, 0x06, 0x0C, 0x1C, 0xF0, 0xC0, 0x08, 0x1C, 0x36, 0x33, 0x30, 0xF0, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x0C, 0xCC, 0x6C, 0x38, 0x10, 0x03, 0x0F, 0x38, 0x30, 0x60, 0x40, 0xC0, 0xC0,
    0xC0, 0xC0, 0x40, 0x60, 0x30, 0x18, 0x0F, 0x03, 0x10, 0x38, 0x6C, 0xCC, 0x0C, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x08, 0x0C, 0x06, 0x03, 0x1E, 0x3C, 0x20, 0x20,
    0x20, 0x20, 0x3C, 0x1E, 0x03, 0x06, 0x0C, 0x08, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,  },
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(remove_auto_mouse_layer(state, true))) {
  case _ARROW:
    // Auto enable scroll mode when the highest layer is 3
    // remove_auto_mouse_target must be called to adjust state *before* setting enable
    state = remove_auto_mouse_layer(state, false);
    set_auto_mouse_enable(false);
    keyball_set_scroll_mode(true);
    break;
  default:
    set_auto_mouse_enable(true);
    keyball_set_scroll_mode(false);
    break;
  }

  return state;
}

void pointing_device_init_user(void) {
  set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
  set_auto_mouse_enable(true); // always required before the auto mouse feature will work
}

#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
#include <tmk_core/protocol/usb_device_state.h>

#include "os_detection.h"
#endif

uint32_t execute_os_switching(uint32_t trigger_time, void *cb_arg) {
  detected_host_os();
  os_variant_t detected = detected_host_os();
  if (detected == OS_MACOS || detected == OS_IOS) {
    layer_on(_MAC);
    layer_off(_WIN);
    default_layer_set(_MAC);
    layer_move(_MAC);
    return 0;
  } else {
    layer_on(_WIN);
    layer_off(_MAC);
    default_layer_set(_WIN);
    layer_move(_WIN);
    return 0;
  }

  return 0;
}

void notify_usb_device_state_change_user(
    enum usb_device_state usb_device_state) {
  // this is the USB reset event - so reset the os detection counter.
  if (USB_DEVICE_STATE_INIT == usb_device_state) {
    erase_wlength_data();
    // usb setup packets should be done by this time (500ms by the spec + some slack time).
    defer_exec(1000, execute_os_switching, NULL);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    case CST_IME_TG:
      if (ime_mode) {
        register_code(KC_LNG1);
        unregister_code(KC_LNG1);
        ime_mode = !ime_mode;
      } else {
        register_code(KC_LNG2);
        unregister_code(KC_LNG2);
        ime_mode = !ime_mode;
      }
      return false;
    }
  }
  return true;
};

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    uint16_t layer_num = get_highest_layer(layer_state);
    oled_write_raw_P(logos[layer_num], sizeof(logos[layer_num]));
    oled_set_cursor(0, 4);
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    return false;
  } else {
    uint16_t layer_num = get_highest_layer(layer_state);

    oled_write_raw_P(logos[layer_num], sizeof(logos[layer_num]));
    return false;
  }
}
#endif
