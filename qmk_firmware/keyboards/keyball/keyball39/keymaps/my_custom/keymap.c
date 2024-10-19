/*
 * Copyright 2022 @Yowkees
 * Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)
 * Copyright 2023 kamidai (@d_kamiichi)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------
 *
 * 参考文献：
 * - リポジトリ：
 *   https://github.com/kamiichi99/keyball/tree/main/qmk_firmware/keyboards/keyball/keyball39/keymaps/kamidai
 *
 * - keyballの販売ページ
 *   https://shirogane-lab.com/collections/all
 *
 * コード表：
 * - 公式ファームウェアのキーコード：
 *   KBC_RST(0x5DA5): Keyball 設定のリセット
 *   KBC_SAVE(0x5DA6): 現在の Keyball 設定を EEPROM に保存します
 *   CPI_I100(0x5DA7): CPI を 100 増加させます(最大:12000)
 *   CPI_D100(0x5DA8): CPI を 100 減少させます(最小:100)
 *   CPI_I1K(0x5DA9): CPI を 1000 増加させます(最大:12000)
 *   CPI_D1K(0x5DAA): CPI を 1000 減少させます(最小:100)
 *   SCRL_TO(0x5DAB): タップごとにスクロールモードの ON/OFF を切り替えます
 *   SCRL_MO(0x5DAC): キーを押している間、スクロールモードになります
 *   SCRL_DVI(0x5DAD): スクロール除数を１つ上げます(max D7 = 1/128)← 最もスクロール遅い
 *   SCRL_DVD(0x5DAE): スクロール除数を１つ下げます(min D0 = 1/1)← 最もスクロール速い
 *
 * - オリジナルのキーコード：
 *   KC_BACK_TO_LAYER0_BTN1(0x5DAF): レイヤー0に遷移できるBTN1
 *   KC_DOUBLE_CLICK_BTN1(0x5DB0): 1タップでダブルクリックできるBTN1
 *   KC_TRIPLE_CLICK_BTN1(0x5DB1): 1タップでトリプルクリックできるBTN1
 */

#include QMK_KEYBOARD_H
#include "quantum.h"




// キーボードに保存する用のユーザーコンフィグ
typedef union {
    uint32_t raw;
    struct {
        int16_t to_clickable_movement;  // クリックレイヤーが有効になるしきい値
    };
} user_config_t;

user_config_t user_config;

// インクルード順の関係で一旦ここで処理
void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.to_clickable_movement = 25;
    eeconfig_update_user(user_config.raw);
}

#include "utils/functions.h"
#include "features/swipe_gesture.h"
#include "features/auto_click_layer.h"
 // #include "features/back_to_layer0_btn1.h"
 // #include "features/one_tap_multi_click.h"
#include "features/macro_keys.h"

// 容量オーバーのため不使用（VIAをOFFにすれば、使用可能）
// #include "features/overrides.h"
#include "features/combo.h"

#include "features/my_custom_rpc.h"


void keyboard_post_init_user(void) {
    if (eeconfig_is_enabled()) {
        user_config.raw = eeconfig_read_user();
    }

    init_rpc();
}


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // keymap for default
    [0] = LAYOUT_universal(
      KC_Q            , KC_W    , KC_E     , KC_R         , KC_T          ,                                KC_Y         , KC_U   , KC_I     , KC_O          , KC_P,
      SFT_T(KC_A)     , KC_S    , KC_D     , KC_F         , KC_G          ,                                KC_H         , KC_J   , KC_K     , SFT_T(KC_L)   , LT(4,KC_TAB),
      CTL_T(KC_Z)     , KC_X    , KC_C     , KC_V         , KC_B          ,                                KC_N         , KC_M   , KC_COMMA , LT(3,KC_DOT)  , LT(4,KC_COLN),
      LT(3,KC_LNG2)  , KC_LGUI , KC_LALT  , LT(1,KC_TAB) , LT(2,KC_SPACE), CTL_T(KC_ESC),        KC_BSPC, ALT_T(KC_ENT), _______, _______  , _______       , LT(3,KC_LNG1)
    ),

    [1] = LAYOUT_universal(
      S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                 KC_INS   , KC_7    , KC_8     , KC_9     , KC_MINUS ,
      KC_LSFT  , S(KC_6)  , S(KC_8)  , S(KC_7)  , _______  ,                                 _______  , KC_4    , KC_5     , KC_6     , KC_EQUAL ,
      _______  , _______  , _______  , _______  , _______  ,                                 _______  , KC_1    , KC_2     , KC_3     , KC_KP_ENTER,
      _______  , _______  , _______  , _______  , _______  , _______  ,             KC_DEL , KC_0     ,_______  , _______  , _______  , _______
    ),

    [2] = LAYOUT_universal(
      KC_F2    , KC_F3       , LGUI(KC_UP)  , KC_F4        , KC_F5  ,                        KC_F10     , KC_F11   , KC_UP     , KC_F12      , KC_GRAVE,
      KC_LSFT  , LSG(KC_LEFT), LGUI(KC_DOWN), LSG(KC_RIGHT), _______,                        _______    , KC_LEFT  , KC_DOWN   , KC_RIGHT    , KC_EQUAL,
      KC_LCTL  , _______     , _______      , _______      , _______,                        LCA(KC_F11), KC_HOME  , KC_PAGE_UP, KC_PAGE_DOWN, KC_END  ,
      _______  , _______     , _______      , _______      , _______, _______,      _______, _______    , _______  , _______   , _______     , _______
    ),

    [3] = LAYOUT_universal(
      _______    ,  KC_QUOTE  , S(KC_QUOTE), _______    , _______  ,                            _______  , S(KC_LBRC), S(KC_RBRC), LSG(KC_S), KC_PSCR,
      MKC_CLKTH_I, MKC_CLKTH_D, CPI_I100   , CPI_D100   , KBC_SAVE ,                            _______  , S(KC_9)   , S(KC_0)   , _______  , KC_BSLS,
      _______    , _______    , SCRL_DVI   , SCRL_DVD   , _______  ,                            _______  , KC_LBRC   , KC_RBRC   , _______  , KC_SLASH,
      _______    , _______    , _______    , _______    , _______  , _______  ,      _______  , _______  , _______   , _______   , _______  , _______
    ),

    [4] = LAYOUT_universal(
      _______  , _______  , _______  , _______  , _______  ,                             _______   , _______   , KC_MS_BTN3  , _______  , _______  ,
      _______  , _______  , _______  , _______  , _______  ,                             _______   , KC_MS_BTN1, KC_MS_BTN2  , SCRL_MO  , _______  ,
      _______  , _______  , _______  , _______  , _______  ,                             _______   , _______   , _______     , _______  , _______  ,
      _______  , _______  , _______  , _______  , _______  , _______  ,      KC_MS_BTN4, KC_MS_BTN5, _______   , _______     , _______  , _______
    ),

    [5] = LAYOUT_universal(
      _______  , _______  , _______  , _______  , _______  ,                            _______  , SCRL_DVI , CPI_I100 , _______  , RGB_TOG  ,
      _______  , _______  , _______  , _______  , _______  ,                            SCRL_DVD , CPI_D100 , _______  , _______  , _______  ,
      _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
      _______  , _______  , _______  , _______  , _______  , _______  ,       _______ , KBC_RST  , _______  , _______  , _______  , _______
    ),

    [6] = LAYOUT_universal(
      _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  ,KC_MS_BTN3, _______  , _______  ,
      KC_LALT  , KC_LSFT  , _______  ,KC_MS_BTN1, _______ ,                             _______  ,KC_MS_BTN1,KC_MS_BTN2, SCRL_MO  , _______  ,
      _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
      _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // レイヤーが1または2の場合、スクロールモードが有効になる
    // keyball_set_scroll_mode(get_highest_layer(state) == 1 || get_highest_layer(state) == 2);

    // レイヤーが2の場合、スクロールモードが有効になる
    keyball_set_scroll_mode(get_highest_layer(state) == 2);

    // keyball_set_scroll_mode(get_highest_layer(state) == 1);

#if RGBLIGHT_ENABLE
    // レイヤーとLEDを連動させる
    switch (get_highest_layer(state)) {
    case click_layer:
        rgblight_sethsv(HSV_WHITE);
        break;
    case 1:
        rgblight_sethsv(HSV_RED);
        break;
    case 2:
        rgblight_sethsv(HSV_YELLOW);
        break;
    case 3:
        rgblight_sethsv(HSV_GREEN);
        break;

    default:
        rgblight_sethsv(HSV_OFF);
    }
#endif

    return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

/**
 * バッファサイズ指定付きu8文字列変換
 * バッファサイズは4が最大です。それ以上の数値を指定しないでください。
 */
const char* get_u8_str_with_buf_size(uint8_t curr_num, size_t buf_size) {
    static char    curr_pad = ' ';
    static char    buf[4] = { 0 };
    static uint8_t last_num = 0xFF;
    static size_t  last_buf_size = 0xFF;
    static char    last_pad = '\0';
    if (last_num == curr_num && last_pad == curr_pad && last_buf_size == buf_size) {
        return buf;
    }
    last_num = curr_num;
    last_pad = curr_pad;
    last_buf_size = buf_size;
    return get_numeric_str(buf, buf_size, curr_num, curr_pad);
}

#define OLED_INFO_COMPACT 1

// オートマウスレイヤーのステート表示
void oled_render_stateinfo(void) {
#if OLED_INFO_COMPACT
    // <state>を表示
    switch (state) {
    case WAITING:
        oled_write_ln_P(PSTR(" WAIT"), false);
        break;
    case CLICKABLE:
        oled_write_ln_P(PSTR(" CKBLE"), false);
        break;
    case CLICKING:
        oled_write_ln_P(PSTR(" CKING"), false);
        break;
    case CLICKED:
        oled_write_ln_P(PSTR(" CKED"), false);
        break;
    case SWIPE:
        oled_write_ln_P(PSTR(" SWP"), false);
        break;
    case SWIPING:
        oled_write_ln_P(PSTR(" SWPING"), false);
        break;
    case NONE:
        oled_write_ln_P(PSTR(" NONE"), false);
        break;
    }
#else
    // <state>を表示
    switch (state) {
    case WAITING:
        oled_write_ln_P(PSTR("  WAITING"), false);
        break;
    case CLICKABLE:
        oled_write_ln_P(PSTR("  CLICKABLE"), false);
        break;
    case CLICKING:
        oled_write_ln_P(PSTR("  CLICKING"), false);
        break;
    case CLICKED:
        oled_write_ln_P(PSTR("  CLICKED"), false);
        break;
    case SWIPE:
        oled_write_ln_P(PSTR("  SWIPE"), false);
        break;
    case SWIPING:
        oled_write_ln_P(PSTR("  SWIPING"), false);
        break;
    case NONE:
        oled_write_ln_P(PSTR("  NONE"), false);
        break;
    }
#endif
}

// プライマリ側のOLED表示
void oledkit_render_info_user(void) {
    // デバッグ用に変数を表示する
    // oled_write_P(PSTR("Debug:"), false);
    // oled_write(get_u8_str(xxx, ' '), false);

    keyball_oled_render_keyinfo();   // キー情報を表示
    keyball_oled_render_ballinfo();  // トラックボール情報を表示

    // <Layer>を表示する
#if OLED_INFO_COMPACT
    oled_write_P(PSTR("Lyr:"), false);
    oled_write(get_u8_str_with_buf_size(get_highest_layer(layer_state), 2), false);
#else
    oled_write_P(PSTR("Layer:"), false);
    oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);
#endif

    // <マウス移動量 / クリックレイヤーしきい値>を表示
    oled_write_P(PSTR(" MV:"), false);
#if OLED_INFO_COMPACT
    oled_write(get_u8_str_with_buf_size(mouse_movement, 3), false);
#else
    oled_write(get_u8_str(mouse_movement, ' '), false);
#endif
    oled_write_P(PSTR("/"), false);
#if OLED_INFO_COMPACT
    oled_write(get_u8_str_with_buf_size(user_config.to_clickable_movement, 3), false);
#else
    oled_write(get_u8_str(user_config.to_clickable_movement, ' '), false);
#endif

    oled_render_stateinfo();
}

#if 0
void oledkit_render_logo_user(void) {
    oled_render_stateinfo();
}
#endif


#endif

