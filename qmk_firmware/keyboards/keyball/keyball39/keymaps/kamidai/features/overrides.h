/* Copyright 2023 kamidai (@d_kamiichi)
 *
 * 参考ページ
 * 公式：https://docs.qmk.fm/#/ja/feature_key_overrides
 * 翻訳：https://github.com/qmk/qmk_firmware/blob/daa6ba4a11e6e02ec141e57324907066457afd64/docs/ja/feature_key_overrides.md
 * その他：https://qiita.com/shela/items/9e5bd102a95a15d1b00c
 *
 * 注意：rules.mk で KEY_OVERRIDE_ENABLE = yes が必要です！
 */

// シフトキー + バックスペース で deleteキー
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);
// const key_override_t hiragana_nn_override = ko_make_basic(KC_Z, KC_N, KC_I);

// 使用する全てのキーオーバーライドをグローバルに定義
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    // &hiragana_nn_override,
    NULL  // オーバーライドの配列は Null で終了
};