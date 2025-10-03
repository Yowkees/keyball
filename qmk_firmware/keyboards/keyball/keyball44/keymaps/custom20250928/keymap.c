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

// ============================================================
// カスタムキーコード（親指用）
// ============================================================
// ※ Remap 側で Tap/Hold を設定するので、ここでは ID だけ確保
enum custom_keycodes {
    THUMB_SPACE = SAFE_RANGE,   // 左親指 中 (Space / Layer1)
    THUMB_KANA,                 // 左親指 右 (かな / Layer3)
    THUMB_BSPC,                 // 右親指 左 (Backspace / LayerX)
    THUMB_ENTER                 // 右親指 中 (Enter / Layer2)
};

// ============================================================
// コンボ設定
// ============================================================
enum combo_events {
    COMBO_JK,           // 左クリック
    COMBO_KL,           // 右クリック
    COMBO_JL,           // スクロールモード
    COMBO_UI,           // 進む
    COMBO_IO,           // 戻る
    COMBO_LTHUMB_EISU,  // 左親指コンボ: Space+Kana → 英数
    COMBO_RTHUMB_KANA   // 右親指コンボ: Bspc+Enter → かな
};

const uint16_t PROGMEM jk_combo[]      = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[]      = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jl_combo[]      = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM ui_combo[]      = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM io_combo[]      = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_lthumb_eisu[] = {THUMB_SPACE, THUMB_KANA, COMBO_END};
const uint16_t PROGMEM combo_rthumb_kana[] = {THUMB_BSPC, THUMB_ENTER, COMBO_END};

combo_t key_combos[] = {
    [COMBO_JK]           = COMBO_ACTION(jk_combo),
    [COMBO_KL]           = COMBO_ACTION(kl_combo),
    [COMBO_JL]           = COMBO_ACTION(jl_combo),
    [COMBO_UI]           = COMBO_ACTION(ui_combo),
    [COMBO_IO]           = COMBO_ACTION(io_combo),
    [COMBO_LTHUMB_EISU]  = COMBO_ACTION(combo_lthumb_eisu),
    [COMBO_RTHUMB_KANA]  = COMBO_ACTION(combo_rthumb_kana),
};

// ============================================================
// コンボ処理
// ============================================================
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case COMBO_JK:   // 左クリック
            if (pressed) register_code(KC_BTN1);
            else         unregister_code(KC_BTN1);
            break;

        case COMBO_KL:   // 右クリック
            if (pressed) register_code(KC_BTN2);
            else         unregister_code(KC_BTN2);
            break;

        case COMBO_JL:   // スクロールモード
            keyball_set_scroll_mode(pressed);
            break;

        case COMBO_UI:   // 進む
            if (pressed) {
                if (is_keyboard_left()) {
                    tap_code(KC_BTN5);   // Windows: 進む
                } else {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_RGHT);   // macOS: Cmd+→
                    unregister_mods(MOD_BIT(KC_LGUI));
                }
            }
            break;

        case COMBO_IO:   // 戻る
            if (pressed) {
                if (is_keyboard_left()) {
                    tap_code(KC_BTN4);   // Windows: 戻る
                } else {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_LEFT);   // macOS: Cmd+←
                    unregister_mods(MOD_BIT(KC_LGUI));
                }
            }
            break;

        case COMBO_LTHUMB_EISU: // 親指: Space+Kana → 英数
            if (pressed) {
                tap_code(KC_LNG2);
            }
            break;

        case COMBO_RTHUMB_KANA: // 親指: Bspc+Enter → かな
            if (pressed) {
                tap_code(KC_LNG1);
            }
            break;
    }
}

// ============================================================
// キーマップ定義
// ============================================================
// 親指部分には THUMB_* を置くことで、コンボ判定用に利用
// （Tap/Holdの実際の挙動は Remap 側で制御）
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
                  KC_LALT, KC_LGUI,     KC_NO, THUMB_SPACE,THUMB_KANA,                          THUMB_BSPC, THUMB_ENTER, RCTL_T(KC_LNG2), KC_RALT, KC_PSCR
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

  // Layer 4 (empty)
  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  // Layer 5 (empty, Precision Modeの割り当てに使う想定)
  [5] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on


// ============================================================
// レイヤ処理
// ============================================================
layer_state_t layer_state_set_user(layer_state_t state) {
    keyball_set_scroll_mode(get_highest_layer(state) == 5);
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
