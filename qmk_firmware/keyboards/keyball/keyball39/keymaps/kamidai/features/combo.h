/* Copyright 2023 kamidai (@d_kamiichi)
 *
 * 参考ページ
 * 公式：https://docs.qmk.fm/#/ja/feature_combo?id=%e3%82%b3%e3%83%b3%e3%83%9c
 *
 * 注意： 以下の設定が必要です
 * rules.mk: COMBO_ENABLE = yes
 * config.h: #define COMBO_COUNT 2（=実際に設定するコンボ数）
 */

enum combos {
  COMBO_F14,
  COMBO_F15
};

// const uint16_t PROGMEM f14_combo[] = {KC_DOWN, KC_I, COMBO_END};
// const uint16_t PROGMEM f15_combo[] = {G(KC_C), KC_UP, COMBO_END};
// const uint16_t PROGMEM combo_layer_1[] = {KC_F, KC_D, COMBO_END};
// const uint16_t PROGMEM combo_layer_2[] = {KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM combo_layer_3[] = {KC_D, KC_S, COMBO_END};
// const uint16_t PROGMEM combo_layer_3[] = {KC_S, KC_A, COMBO_END};

const uint16_t PROGMEM combo_BRC[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo_select_BRC[] = {KC_LBRC, S(KC_EQUAL), COMBO_END};

const uint16_t PROGMEM combo_S9_S0[] = {S(KC_9), S(KC_0), COMBO_END};
const uint16_t PROGMEM combo_select_S9_S0[] = {S(KC_9), KC_MINUS, COMBO_END};

const uint16_t PROGMEM combo_S_BRC[] = {S(KC_LBRC), S(KC_RBRC), COMBO_END};
const uint16_t PROGMEM combo_select_S_BRC[] = {S(KC_LBRC), KC_RBRC, COMBO_END};

const uint16_t PROGMEM combo_sumitsuki_BRC[] = {SFT_T(KC_GRAVE), KC_LBRC, COMBO_END};
const uint16_t PROGMEM combo_select_sumitsuki_BRC[] = {SFT_T(KC_GRAVE), S(KC_0), COMBO_END};

const uint16_t PROGMEM combo_MINUS_SPACE[] = {KC_RBRC, S(KC_EQUAL), COMBO_END};

combo_t key_combos[] = {
    // [COMBO_F14] = COMBO(f14_combo, KC_F14),
    // [COMBO_F15] = COMBO(f15_combo, KC_F15)
    // COMBO(combo_layer_1, MO(3)),
    // COMBO(combo_layer_2, MO(3)),
    // COMBO(combo_layer_3, MO(2)),

    COMBO(combo_BRC, COMBO_BRC),
    COMBO(combo_select_BRC, COMBO_select_BRC),

    COMBO(combo_S9_S0, COMBO_S9_S0),
    COMBO(combo_select_S9_S0, COMBO_select_S9_S0),

    COMBO(combo_S_BRC, COMBO_S_BRC),
    COMBO(combo_select_S_BRC, COMBO_select_S_BRC),

    COMBO(combo_sumitsuki_BRC, COMBO_sumitsuki_BRC),
    COMBO(combo_select_sumitsuki_BRC, COMBO_select_sumitsuki_BRC),

    COMBO(combo_MINUS_SPACE, COMBO_MINUS_SPACE),

};