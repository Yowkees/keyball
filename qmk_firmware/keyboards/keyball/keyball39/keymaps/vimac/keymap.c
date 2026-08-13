/*
Keyball39 keymap "vimac"
  HHKB(US) 出身 / macOS / US配列 / Vim / プログラミング用途

  物理配列（トラックボール = 右手）
    最下段+親指の並びは LAYOUT_universal の引数順で
      L30 L31 L32 L33 L34 L35 | R35 R34 (R33 R32 R31) R30
    のうち、R33/R32/R31 は Keyball39 には存在しない（ダミー）。

      L30 L31 L32 = 左最下段（小指/薬指/中指）
      L33 L34 L35 = 左親指（外 → 内）
      R35 R34     = 右親指（内 → 外）
      R30         = 右最下段（小指）
*/

#include QMK_KEYBOARD_H
#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // ------------------------------------------------------------------
  // Layer 0 : ベース
  //   Cmd と Ctrl を親指に置き、左手の全文字キーと衝突させない。
  //   Shift は左最下段（右手文字用）と右親指（左手文字用）に分散。
  // ------------------------------------------------------------------
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                          KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                          KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                          KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LSFT  , KC_LALT  , KC_TAB   , KC_LCTL  , LGUI_T(KC_LNG1), LT(1,KC_SPC),  LT(2,KC_ENT), RSFT_T(KC_BSPC), XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_ESC
  ),

  // ------------------------------------------------------------------
  // Layer 1 : 記号（左親指 内側ホールド）
  //   3キー同時押しを避けるため、記号は全て単押しで出す。
  //   括弧は右手に縦分割： () 上段 / {} ホーム段 / [] 下段
  // ------------------------------------------------------------------
  [1] = LAYOUT_universal(
    KC_EXLM  , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC  ,                          KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_LPRN  , KC_RPRN  ,
    KC_GRV   , KC_BSLS  , KC_PIPE  , KC_QUOT  , KC_DQUO  ,                          KC_COLN  , KC_MINS  , KC_EQL   , KC_LCBR  , KC_RCBR  ,
    KC_LABK  , KC_RABK  , KC_QUES  , XXXXXXX  , SCRL_MO  ,                          KC_UNDS  , KC_PLUS  , KC_TILD  , KC_LBRC  , KC_RBRC  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,   _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_BTN1
  ),

  // ------------------------------------------------------------------
  // Layer 2 : 数字・ナビゲーション（右親指 内側ホールド）
  //   左手にテンキー、右手ホーム段に矢印を横一列（Vim の hjkl 相当）。
  //   Opt+←→ / Cmd+←→ を合成キーで持つことで Layer0 の Opt 依存を減らす。
  // ------------------------------------------------------------------
  [2] = LAYOUT_universal(
    XXXXXXX  , KC_7     , KC_8     , KC_9     , KC_0     ,                          KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , KC_DEL   ,
    XXXXXXX  , KC_4     , KC_5     , KC_6     , KC_MINS  ,                          KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , MO(3)    ,
    KC_DOT   , KC_1     , KC_2     , KC_3     , KC_EQL   ,                       A(KC_LEFT), A(KC_RGHT), G(KC_LEFT), G(KC_RGHT), KC_BTN3 ,
    _______  , _______  , _______  , _______  , _______  , _______  ,   _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_BTN2
  ),

  // ------------------------------------------------------------------
  // Layer 3 : Keyball 設定・ファンクション（Layer2 上の MO(3)）
  //   調整後は必ず KBC_SAVE を押すこと（押さないと再接続で元に戻る）。
  // ------------------------------------------------------------------
  [3] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                          AML_TO   , CPI_D1K  , CPI_I1K  , XXXXXXX  , KBC_SAVE ,
    KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,                          SCRL_DVD , SCRL_DVI , XXXXXXX  , XXXXXXX  , KBC_RST  ,
    KC_F11   , KC_F12   , EE_CLR   , XXXXXXX  , XXXXXXX  ,                          SSNP_VRT , SSNP_FRE , XXXXXXX  , XXXXXXX  , QK_BOOT  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,   _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______
  ),
};
// clang-format on

// ----------------------------------------------------------------------
// Esc を押したら必ず IME を切る
//
//   カスタムキーコードを新設せず KC_ESC 自体に副作用を持たせている。
//   こうすると Remap 側では「ただの Esc」として扱えるので、
//   後からキー配置を変えてもこの挙動が維持される。
//
//   Vim でノーマルモードへ戻る動作と英数化が常に一致するため、
//   日本語コメントを書いた直後に h が「あ」になる事故が起きない。
// ----------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_ESC && record->event.pressed) {
        tap_code(KC_LNG2);  // 英数
    }
    return true;
}

// ----------------------------------------------------------------------
// レイヤー切り替え時の処理
//
//   スクロールは SCRL_MO（Layer1 の左人差し指）で明示的に起動するので、
//   公式の keyball_set_scroll_mode(get_highest_layer(state) == 3) は使わない。
//   横スクロールは Shift で代替できるため縦方向に固定する。
// ----------------------------------------------------------------------
layer_state_t layer_state_set_user(layer_state_t state) {
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    // 記号レイヤー滞在中は AML を切る（打鍵中の誤発火を防ぐ）
    if (get_highest_layer(remove_auto_mouse_layer(state, true)) == 1) {
        state = remove_auto_mouse_layer(state, false);
        set_auto_mouse_enable(false);
    } else {
        set_auto_mouse_enable(true);
    }
#endif

    return state;
}

// ----------------------------------------------------------------------
// OLED
// ----------------------------------------------------------------------
#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}

#endif
