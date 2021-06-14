#include QMK_KEYBOARD_H

#include "paw3204.h"
#include "pointing_device.h"
#include "../optical_sensor/optical_sensor.h"

extern keymap_config_t keymap_config;

//extern uint8_t is_master;

bool isScrollMode;

enum keymap_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  KC_MBTN1,
  KC_MBTN2,
  KC_MBTN3,
  KC_SCRL
};

// common
#define KC_ KC_TRNS
#define KC_XXXX KC_NO
#define KC_RST RESET
#define KC_VD KC__VOLDOWN
#define KC_VU KC__VOLUP

// layer
#define KC_L_SPC LT(_LOWER, KC_SPC)
#define KC_R_ENT LT(_RAISE, KC_ENT)

// shift_t
#define KC_S_EN LSFT_T(KC_LANG2)
#define KC_S_JA LSFT_T(KC_LANG1)

// original
#define KC_A_JA LT(_ADJUST, KC_LANG1)   // cmd or adjust 
#define KC_AL_CP MT(MOD_LALT, KC_CAPS)  // alt or caps lock
#define KC_G_BS MT(MOD_LGUI, KC_BSPC)   // command or back space
#define KC_G_DEL MT(MOD_LGUI, KC_DEL)   // command or delete
#define KC_A_BS LT(_ADJUST, KC_BSPC)    // adjust or back space
#define KC_A_DEL LT(_ADJUST, KC_DEL)    // adjust or delete

// cmd_t
#define KC_G_F LCMD_T(KC_F)
#define KC_G_J RCMD_T(KC_J)

// ctl_t
#define KC_C_G LCTL_T(KC_G)
#define KC_C_H RCTL_T(KC_H)

// alt_t
#define KC_A_D ALT_T(KC_D)
#define KC_A_K ALT_T(KC_K)

// cmd+shift_t
#define KC_GS_S SCMD_T(KC_S)
#define KC_GS_L SCMD_T(KC_L)

//
#define KC_MISS C(KC_UP)

#define TAPPING_LAYER_TERM 230
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_GS_S:
      return TAPPING_LAYER_TERM;
    case KC_GS_L:
      return TAPPING_LAYER_TERM;
    case KC_A_D:
      return TAPPING_LAYER_TERM;
    case KC_A_K:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc( \
  //,-----+-----+-----+-----+-----+-----.           ,-----+-----+-----+-----+-----+-----.
       Q  ,  W  ,  E  ,  R  ,  T  ,LBRC             ,  Y  ,  U  ,  I  ,  O  ,  P  , ESC ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
       A  ,  S  ,  D  ,  F  ,  G  ,RBRC             ,  H  ,  J  ,  K  ,  L  , MINS, SCLN,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
       Z  ,  X  ,  C  ,  V  ,  B  ,MBTN2            ,  N  ,  M  , COMM, DOT , SLSH, BSLS,
  //|-----+-----+-----+-----+-----+-----|           \-----+-----+-----+-----+-----+-----'
      LCTL,AL_CP,    G_BS,L_SPC,S_EN ,A_JA       ,MBTN1,R_ENT,G_DEL,    EXLM, TAB , PSCR
  //`-----+-----+  +-----+-----+-----+----'       `----+-----+-----+  +-----+-----+-----'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----+-----+-----+-----+-----+-----.           ,-----+-----+-----+-----+-----+-----.
     BSLS ,  7  ,  8  ,  9  ,PLUS ,LPRN             , F6  , F7  , F8  , F9  , F10 , F11 ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     ASTR ,  4  ,  5  ,  6  , DOT ,RPRN             ,     ,LEFT , UP  ,RGHT ,     , F12 ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     SLSH ,  1  ,  2  ,  3  , EQL ,MBTN3            ,     ,     ,DOWN ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----|           \-----+-----+-----+-----+-----+-----'
          ,  0  ,    ENT ,     , SPC ,            ,MBTN3, A_BS,     ,       ,     ,     
  //`-----+-----+  +-----+-----+-----+----'       `----+-----+-----+  +-----+-----+-----'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----+-----+-----+-----+-----+-----.           ,-----+-----+-----+-----+-----+-----.
      F1  , F2  , F3  , F4  , F5  ,LPRN             , F6  , F7  , F8  , F9  , F10 , F11 ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     HASH ,EXLM ,AMPR ,PIPE , AT  ,RPRN             ,     ,MBTN1, PGUP,MBTN2,MBTN3, F12 ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
      GRV , DQT ,QUOT ,CIRC ,TILD ,MBTN3            ,     ,     , PGDN,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----|           \-----+-----+-----+-----+-----+-----'
          ,PERC ,        ,A_DEL,     ,            ,MBTN2,    ,     ,       ,     ,     
  //`-----+-----+  +-----+-----+-----+----'       `----+-----+-----+  +-----+-----+-----'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.          ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+          +--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  //|--------+--------+    +-------+--------+--------+--------|  |-------+--------+--------+    +--------+--------+--------|
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};

  switch (keycode) {
    case KC_MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_MBTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN3;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_SCRL:
      if (record->event.pressed) {
        isScrollMode = true;
        dprint("scroll ON\n");
      }
      else {
        isScrollMode = false;
        dprint("scroll OFF\n");
      }
      return false;
  }
  return true;
}

#define CLAMP_HID(value) value < -127 ? -127 : value > 127 ? 127 : value

void matrix_init_user(void) {
	if (is_keyboard_master()){
		init_paw3204();
		optical_sensor_init();
	}
//    setPinInputHigh(D3);
}

void keyboard_post_init_user() {
    debug_enable = true;
    debug_mouse = true;
}

void matrix_scan_user(void) {
    if (!is_keyboard_master())
        return;
    static int  cnt;
    static bool paw_ready;
//    static int  tb_layer;

    report_mouse_t mouse_rep = pointing_device_get_report();
	report_optical_sensor_t sensor_report = optical_sensor_get_report();

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }

/*        if (readPin(D3) == 1) {
            if (tb_layer == 0) {
                dprint("tb layer on\n");
                layer_on(_TB);
                tb_layer = 1;
            }
        } else {
            if (tb_layer == 1) {
                layer_off(_TB);
                dprint("tb layer off\n");
                tb_layer = 0;
            }
        }*/
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;
        int8_t r_x, r_y;
        int8_t degree = 45;

		int16_t raw_x = - sensor_report.x;
		int16_t raw_y = - sensor_report.y;
    	if(raw_x*raw_x >= 225) raw_x*=2;
		if(raw_y*raw_y >= 225) raw_y*=2;
    	if(raw_x>0) raw_x = raw_x / 8 + 1;
    	if(raw_y>0) raw_y = raw_y / 8 + 1;
    	if(raw_x<0) raw_x = raw_x / 8 - 1;
    	if(raw_y<0) raw_y = raw_y / 8 - 1;
		int8_t clamped_x = CLAMP_HID(raw_x);
		int8_t clamped_y = CLAMP_HID(raw_y);
    	
    	mouse_rep.x = -clamped_x;
        mouse_rep.y = clamped_y;

//        if (isScrollMode) {
            if (cnt % 5 == 0) {
            	read_paw3204(&stat, &x, &y);
                r_x =  x * cos(degree) + y * sin(degree);
                r_y = -x * sin(degree) + y * cos(degree);
                mouse_rep.v = -r_y/10;
                mouse_rep.h = r_x/10;
            }else{
            	mouse_rep.v = 0;
                mouse_rep.h = 0;
            }
/*        } else {
            mouse_rep.x = r_x;
            mouse_rep.y = r_y;
        }*/

        if (stat & 0x80 || mouse_rep.x!=0 || mouse_rep.y!=0) {
			pointing_device_set_report(mouse_rep);
        	if(mouse_rep.x!=0 || mouse_rep.y!=0) dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }
    }
}

/*
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        isScrollMode = true;
        break;
    default:
        isScrollMode = false;
        break;
    }
  return state;
}
*/
