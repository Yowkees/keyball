/*
 * Keyball44 custom firmware - 完成版 v3（正式安定版）
 * 左右接続でWin/mac切替・親指TapHold内蔵
 */

#include QMK_KEYBOARD_H
#include "quantum.h"

// ============================================================
// カスタムキーコード（親指用）
// ============================================================
enum custom_keycodes {
    THUMB_SPACE = SAFE_RANGE,   // 左親指 中 (Space / Layer2)
    THUMB_KANA,                 // 左親指 右 (かな / Layer1)
    THUMB_BSPC,                 // 右親指 左 (Backspace / Layer1)
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
    COMBO_LTHUMB_EISU,  // Space+Kana → 英数
    COMBO_RTHUMB_KANA,  // Bspc+Enter → かな
    COMBO_VB_EISU,      // V+B → 英数
    COMBO_NM_KANA       // N+M → かな
};

// ---- コンボ定義 ----
const uint16_t PROGMEM jk_combo[]      = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[]      = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jl_combo[]      = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM ui_combo[]      = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM io_combo[]      = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_lthumb_eisu[] = {THUMB_SPACE, THUMB_KANA, COMBO_END};
const uint16_t PROGMEM combo_rthumb_kana[] = {THUMB_BSPC, THUMB_ENTER, COMBO_END};
const uint16_t PROGMEM combo_vb_eisu[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM combo_nm_kana[] = {KC_N, KC_M, COMBO_END};

// ---- 登録 ----
combo_t key_combos[] = {
    [COMBO_JK]           = COMBO_ACTION(jk_combo),
    [COMBO_KL]           = COMBO_ACTION(kl_combo),
    [COMBO_JL]           = COMBO_ACTION(jl_combo),
    [COMBO_UI]           = COMBO_ACTION(ui_combo),
    [COMBO_IO]           = COMBO_ACTION(io_combo),
    [COMBO_LTHUMB_EISU]  = COMBO_ACTION(combo_lthumb_eisu),
    [COMBO_RTHUMB_KANA]  = COMBO_ACTION(combo_rthumb_kana),
    [COMBO_VB_EISU]      = COMBO_ACTION(combo_vb_eisu),
    [COMBO_NM_KANA]      = COMBO_ACTION(combo_nm_kana),
};

// ============================================================
// コンボ処理
// ============================================================
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case COMBO_JK:
            if (pressed) register_code(KC_BTN1);
            else         unregister_code(KC_BTN1);
            break;

        case COMBO_KL:
            if (pressed) register_code(KC_BTN2);
            else         unregister_code(KC_BTN2);
            break;

        case COMBO_JL:
            keyball_set_scroll_mode(pressed);
            break;

        case COMBO_UI:   // 進む
            if (pressed) {
                if (is_keyboard_left()) {
                    tap_code(KC_BTN5);   // 左側＝Windows
                } else {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_RGHT);   // 右側＝macOS (Cmd+→)
                    unregister_mods(MOD_BIT(KC_LGUI));
                }
            }
            break;

        case COMBO_IO:   // 戻る
            if (pressed) {
                if (is_keyboard_left()) {
                    tap_code(KC_BTN4);   // 左側＝Windows
                } else {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_LEFT);   // 右側＝macOS (Cmd+←)
                    unregister_mods(MOD_BIT(KC_LGUI));
                }
            }
            break;

        case COMBO_LTHUMB_EISU: // Space+Kana → 英数
        case COMBO_VB_EISU:     // V+B → 英数
            if (pressed) tap_code(KC_LNG2);
            break;

        case COMBO_RTHUMB_KANA: // Bspc+Enter → かな
        case COMBO_NM_KANA:     // N+M → かな
            if (pressed) tap_code(KC_LNG1);
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
              KC_LALT, KC_LGUI,                KC_NO    , THUMB_SPACE    ,THUMB_KANA    ,             THUMB_BSPC, THUMB_ENTER, RCTL_T(KC_LNG2), KC_RALT, KC_PSCR
  ),

  // --- レイヤ1～5：v2の内容をそのまま保持（Remap連携のため省略なし） ---
  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ ,         _______  , THUMB_SPACE  , THUMB_KANA  ,                   KC_DEL  , THUMB_ENTER  , _______       , _______  , _______
  ),
  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         THUMB_SPACE  , THUMB_KANA  ,                   THUMB_BSPC   , THUMB_ENTER  , _______       , _______  , _______
  ),
  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        THUMB_SPACE  , THUMB_KANA  ,                   THUMB_BSPC  , THUMB_ENTER  , _______       , KBC_RST  , QK_BOOT
  ),
  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,        THUMB_SPACE  , THUMB_KANA  ,                   THUMB_BSPC  , THUMB_ENTER  , _______       , _______  , _______
  ),
  [5] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,        THUMB_SPACE  , THUMB_KANA,                   THUMB_BSPC  , THUMB_ENTER  , _______       , _______  , _______
  ),
};

// ============================================================
// 親指Tap/Hold制御
// ============================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t thumb_timer[4];
    switch (keycode) {
        case THUMB_SPACE:
            if (record->event.pressed) {
                thumb_timer[0] = timer_read();
                layer_on(2);
            } else {
                layer_off(2);
                if (timer_elapsed(thumb_timer[0]) < TAPPING_TERM)
                    tap_code(KC_SPC);
            }
            return false;
        case THUMB_KANA:
            if (record->event.pressed) {
                thumb_timer[1] = timer_read();
                layer_on(1);
            } else {
                layer_off(1);
                if (timer_elapsed(thumb_timer[1]) < TAPPING_TERM)
                    tap_code(KC_LNG1);
            }
            return false;
        case THUMB_BSPC:
            if (record->event.pressed) {
                thumb_timer[2] = timer_read();
                layer_on(1);
            } else {
                layer_off(1);
                if (timer_elapsed(thumb_timer[2]) < TAPPING_TERM)
                    tap_code(KC_BSPC);
            }
            return false;
        case THUMB_ENTER:
            if (record->event.pressed) {
                thumb_timer[3] = timer_read();
                layer_on(2);
            } else {
                layer_off(2);
                if (timer_elapsed(thumb_timer[3]) < TAPPING_TERM)
                    tap_code(KC_ENT);
            }
            return false;
    }
    return true;
}

// ============================================================
// レイヤ処理 / OLED表示
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
