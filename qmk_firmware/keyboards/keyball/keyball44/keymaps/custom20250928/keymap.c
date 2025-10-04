#include QMK_KEYBOARD_H
#include "quantum.h"

// ============================================================
// コンボ設定
// ============================================================
enum combo_events {
    COMBO_JK,           // 左クリック
    COMBO_KL,           // 右クリック
    COMBO_JL,           // スクロールモード
    COMBO_UI,           // 進む
    COMBO_IO,           // 戻る
    COMBO_LTHUMB_EISU,  // 親指コンボ: Space+かな → 英数
    COMBO_RTHUMB_KANA   // 親指コンボ: Bspc+Enter → かな
};

const uint16_t PROGMEM jk_combo[]          = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[]          = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jl_combo[]          = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM ui_combo[]          = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM io_combo[]          = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_lthumb_eisu[] = {KC_SPC, KC_LNG1, COMBO_END}; // Space + かな
const uint16_t PROGMEM combo_rthumb_kana[] = {KC_BSPC, KC_ENT, COMBO_END};  // Bspc + Enter

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

        case COMBO_LTHUMB_EISU: // 親指: Space+かな → 英数
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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT, KC_LGUI, KC_NO, KC_SPC, KC_LNG1,                    KC_BSPC, KC_ENT, RCTL_T(KC_LNG2), KC_RALT, KC_PSCR
  ),
  // 他のレイヤーは省略（以前のコードと同じ）
};

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
