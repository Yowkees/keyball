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

static int32_t gesture_x;
static int32_t gesture_y;
static uint32_t gesture_last_motion;
static bool gesture_triggered;
static uint16_t kl_combo_timer;
static bool kl_combo_active;
static bool kl_combo_layer;

static int8_t masami_clip2int8(int16_t value) {
  return value < -127 ? -127 : value > 127 ? 127 : (int8_t)value;
}

static void reset_gesture_state(void) {
  gesture_x          = 0;
  gesture_y          = 0;
  gesture_last_motion = 0;
  gesture_triggered  = false;
}

static void send_gesture_key(int32_t x, int32_t y) {
  if (abs(x) > abs(y)) {
    tap_code16(x > 0 ? LCTL(LGUI(KC_RGHT)) : LCTL(LGUI(KC_LEFT)));
  } else {
    tap_code16(y > 0 ? KC_F5 : LGUI(KC_TAB));
  }
}

static void process_gesture_motion(keyball_motion_t *motion, bool is_left) {
  int32_t x = motion->y;
  int32_t y = motion->x;

  if (is_left) {
    x = -x;
    y = -y;
  }

  motion->x = 0;
  motion->y = 0;

  if (x == 0 && y == 0) {
    if (gesture_triggered && timer_elapsed32(gesture_last_motion) >= KEYBALL_GESTURE_IDLE_TIMEOUT) {
      reset_gesture_state();
    }
    return;
  }

  gesture_last_motion = timer_read32();
  gesture_x += x;
  gesture_y += y;

  if (!gesture_triggered && (abs(gesture_x) >= KEYBALL_GESTURE_THRESHOLD || abs(gesture_y) >= KEYBALL_GESTURE_THRESHOLD)) {
    send_gesture_key(gesture_x, gesture_y);
    gesture_triggered = true;
  }
}

void keyball_on_apply_motion_to_mouse_move(keyball_motion_t *motion, report_mouse_t *report, bool is_left) {
  if (layer_state_is(4)) {
    report->x = 0;
    report->y = 0;
    process_gesture_motion(motion, is_left);
    return;
  }

  report->x = masami_clip2int8(motion->y);
  report->y = masami_clip2int8(motion->x);
  if (is_left) {
    report->x = -report->x;
    report->y = -report->y;
  }
  motion->x = 0;
  motion->y = 0;
}

enum combo_events {
  JK_LEFT_CLICK,
  KL_RIGHT_CLICK_OR_LAYER,
  JL_MIDDLE_CLICK,
  NUM_Q_F1,
  NUM_W_F2,
  NUM_E_F3,
  NUM_R_F4,
  NUM_T_F5,
  NUM_Y_F6,
  NUM_U_F7,
  NUM_I_F8,
  NUM_O_F9,
  NUM_P_F10,
  GRV_EQL_F11,
  NUM_1_2_F12,
};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM num_q_combo[] = {KC_1, KC_Q, COMBO_END};
const uint16_t PROGMEM num_w_combo[] = {KC_2, KC_W, COMBO_END};
const uint16_t PROGMEM num_e_combo[] = {KC_3, KC_E, COMBO_END};
const uint16_t PROGMEM num_r_combo[] = {KC_4, KC_R, COMBO_END};
const uint16_t PROGMEM num_t_combo[] = {KC_5, KC_T, COMBO_END};
const uint16_t PROGMEM num_y_combo[] = {KC_6, KC_Y, COMBO_END};
const uint16_t PROGMEM num_u_combo[] = {KC_7, KC_U, COMBO_END};
const uint16_t PROGMEM num_i_combo[] = {KC_8, LT(3, KC_I), COMBO_END};
const uint16_t PROGMEM num_o_combo[] = {KC_9, KC_O, COMBO_END};
const uint16_t PROGMEM num_p_combo[] = {KC_0, KC_P, COMBO_END};
const uint16_t PROGMEM grv_eql_combo[] = {KC_GRV, KC_EQL, COMBO_END};
const uint16_t PROGMEM num_1_2_combo[] = {KC_1, KC_2, COMBO_END};

combo_t key_combos[] = {
  [JK_LEFT_CLICK] = COMBO(jk_combo, KC_BTN1),
  [KL_RIGHT_CLICK_OR_LAYER] = COMBO_ACTION(kl_combo),
  [JL_MIDDLE_CLICK] = COMBO(jl_combo, KC_BTN3),
  [NUM_Q_F1] = COMBO(num_q_combo, KC_F1),
  [NUM_W_F2] = COMBO(num_w_combo, KC_F2),
  [NUM_E_F3] = COMBO(num_e_combo, KC_F3),
  [NUM_R_F4] = COMBO(num_r_combo, KC_F4),
  [NUM_T_F5] = COMBO(num_t_combo, KC_F5),
  [NUM_Y_F6] = COMBO(num_y_combo, KC_F6),
  [NUM_U_F7] = COMBO(num_u_combo, KC_F7),
  [NUM_I_F8] = COMBO(num_i_combo, KC_F8),
  [NUM_O_F9] = COMBO(num_o_combo, KC_F9),
  [NUM_P_F10] = COMBO(num_p_combo, KC_F10),
  [GRV_EQL_F11] = COMBO(grv_eql_combo, KC_F11),
  [NUM_1_2_F12] = COMBO(num_1_2_combo, KC_F12),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  if (combo_index != KL_RIGHT_CLICK_OR_LAYER) {
    return;
  }

  if (pressed) {
    kl_combo_timer = timer_read();
    kl_combo_active = true;
    kl_combo_layer = false;
  } else if (kl_combo_active) {
    if (!kl_combo_layer) {
      tap_code(KC_BTN2);
    }
    layer_off(4);
    kl_combo_active = false;
    kl_combo_layer = false;
  }
}

void matrix_scan_user(void) {
  if (kl_combo_active && !kl_combo_layer && timer_elapsed(kl_combo_timer) >= TAPPING_TERM) {
    layer_on(4);
    kl_combo_layer = true;
  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC       , KC_1     , KC_2     , KC_3     , KC_4           , KC_5           ,                             KC_6   , KC_7 , KC_8      , KC_9  , KC_0         , KC_EQL ,
    KC_TAB       , KC_Q     , KC_W     , KC_E     , KC_R           , KC_T           ,                             KC_Y   , KC_U , LT(3,KC_I), KC_O  , KC_P         , KC_GRV ,
    MEH_T(KC_ENT), KC_A     , KC_S     , KC_D     , KC_F           , KC_G           ,                             KC_H   , KC_J , KC_K      , KC_L  , LT(2,KC_SCLN), KC_QUOT,
    KC_LSFT      , KC_Z     , KC_X     , KC_C     , KC_V           , KC_B           , LSG(KC_S)   , KC_MINS     , KC_N   , KC_M , KC_COMM   , KC_DOT, KC_SLSH      , KC_BSLS,
    KC_LCTL      , KC_LGUI  , KC_LALT  , KC_DEL   , LSFT_T(KC_LNG2), LCTL_T(KC_LNG1), LT(1,KC_SPC), LT(1,KC_ENT), KC_BSPC, KC_NO, KC_NO     , KC_NO , KC_LBRC      , KC_RBRC
  ),

  [1] = LAYOUT_universal(
    KC_TRNS  , KC_F1      , KC_F2    , KC_F3    , KC_F4    , KC_F5     ,                                 KC_F6  , KC_7  , KC_8   , KC_9   , KC_TRNS, KC_TRNS,
    KC_TRNS  , KC_PGUP    , KC_HOME  , KC_UP    , KC_END   , KC_PGDN   ,                                 KC_F2  , KC_4  , KC_5   , KC_6   , KC_PLUS, KC_TRNS,
    KC_TRNS  , C(KC_LEFT) , KC_LEFT  , KC_DOWN  , KC_RGHT  , C(KC_RGHT),                                 KC_DQUO, KC_1  , KC_2   , KC_3   , KC_TRNS, KC_TRNS,
    KC_TRNS  , RCS(KC_TAB), S(KC_TAB), KC_ESC   , KC_TAB   , C(KC_TAB) , KC_TRNS  ,           KC_TRNS  , KC_UNDS, KC_0  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS  , KC_TRNS    , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS   , KC_TRNS  ,           KC_TRNS  , KC_TRNS, KC_NO , KC_NO  , KC_NO  , KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT_universal(
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                 KC_NO  , KC_NO   , KC_NO   , KC_NO   , KC_NO  , KC_NO,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                 KC_NO  , KC_BTN4 , MO(3)   , KC_BTN5 , KC_NO  , KC_NO,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                 KC_NO  , KC_BTN1 , KC_BTN3 , KC_BTN2 , KC_NO  , KC_NO,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,           KC_NO    , KC_NO  , KC_WH_L , KC_NO   , KC_WH_R , KC_NO  , KC_NO,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,           KC_TRNS  , KC_TRNS, KC_NO   , KC_NO   , KC_NO   , KC_NO  , KC_NO
  ),

  [3] = LAYOUT_universal(
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                  KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                  KC_TRNS  , KC_TRNS  , KC_NO   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                  KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,           KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,           KC_TRNS  , KC_TRNS  , KC_NO   , KC_NO   , KC_NO   , KC_TRNS  , KC_TRNS
  ),

  [4] = LAYOUT_universal(
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                  KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                  KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                                  KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,           KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,           KC_TRNS  , KC_TRNS  , KC_NO   , KC_NO   , KC_NO   , KC_TRNS  , KC_TRNS
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t highest_layer = get_highest_layer(state);

  if (highest_layer != 4) {
        reset_gesture_state();
    }
  keyball_set_scroll_mode(highest_layer == 3);
  if (highest_layer == 3) {
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_FREE);
  }
    return state;
}
