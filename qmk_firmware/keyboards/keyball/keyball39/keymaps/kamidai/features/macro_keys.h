/* Copyright 2023 kamidai (@d_kamiichi)
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
 */

enum custom_keycodes {
  KC_BACK_TO_LAYER0_BTN1 = KEYBALL_SAFE_RANGE,  // (0x5DAF): レイヤー0に遷移できるBTN1
  KC_DOUBLE_CLICK_BTN1,                         // (0x5DB0): 1タップでダブルクリックできるBTN1
  KC_TRIPLE_CLICK_BTN1,                         // (0x5DB1): 1タップでトリプルクリックできるBTN1
  // KC_ALT_BTN1,                                  // (0x5DB2):
  // select_BRC,
  // CMD_SCRL,
};

// マクロキーの処理を行う関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  current_keycode = keycode;             // 押下されたキーコードを保存する
  bool mod_pressed = (get_mods() != 0);  // 修飾キーが押されているかを判定（0でなければ修飾キーが押されている）
  bool is_ctrl_tab_active = false;       //

  switch (keycode) {
    // デフォルトのマウスキーを自動クリックレイヤーで使用可能にする
    case KC_MS_BTN1:
    case KC_MS_BTN2:
    case KC_MS_BTN3:
    case KC_MS_BTN4:
    case KC_MS_BTN5: {
      if (click_layer && get_highest_layer(layer_state) == click_layer) {
        if (record->event.pressed) {
          // キーダウン時: 状態をCLICKINGに設定
          state = CLICKING;
        } else {
          // キーアップ時: クリックレイヤーを有効にして、状態をCLICKEDに設定
          enable_click_layer();
          state = CLICKED;
        }
      }
      return true;
    }

    // 以下のキーは自動クリックレイヤーで使用可能にする
    case KC_LALT:
    case KC_LSFT: {
      return true;
    }

      // 上位レイヤーから下位レイヤーへ移動できるようにする
      static uint8_t previous_layer = 0;  // 前のレイヤーを記録する変数
      static uint16_t lt_timer;           // タイマーを記録する変数

    case LT(1, KC_LANG2):
    case LT(2, KC_V):
    case S(KC_8): {
      // int16_t hlayer = get_highest_layer(layer_state);
      // if (get_highest_layer(layer_state) == 2) {
      if (record->event.pressed) {
        // キーダウン時:
        lt_timer = timer_read();                          // 現在のタイマー値を記録
        previous_layer = get_highest_layer(layer_state);  // 現在の最上位レイヤーを記録
        layer_off(previous_layer);                        // 現在のレイヤーをオフにする

        if (keycode == LT(1, KC_LANG2)) {
          layer_on(1);
        } else if (keycode == LT(2, KC_V) || keycode == S(KC_8)) {
          layer_on(2);
        }
      } else {
        // キーアップ時:
        layer_on(previous_layer);  // 前のレイヤーをオンにする
        if (keycode == LT(1, KC_LANG2)) {
          layer_off(1);
        } else if (keycode == LT(2, KC_V) || keycode == S(KC_8)) {
          layer_off(2);
        }
        if (timer_elapsed(lt_timer) < TAPPING_TERM) {
          // タッピングタイム内に放された場合はタップ動作
          if (keycode == LT(1, KC_LANG2)) {
            tap_code(KC_LANG2);
          } else if (keycode == S(KC_8)) {
            tap_code16(S(KC_8));
          }
        }
      }
      return false;
    }

      // case select_BRC: {
      //   if (record->event.pressed) {
      //     register_code16(G(KC_X));
      //     register_code(KC_LBRC);
      //     register_code(KC_ENT);
      //     register_code16(G(KC_V));
      //     register_code(KC_RBRC);
      //     register_code(KC_ENT);
      //   } else {
      //   }
      //   return false;
      // }

      // case CMD_SCRL: {
      //   if (record->event.pressed) {
      //     register_code16(G(SCRL_MO));
      //   } else {
      //     unregister_code16(G(SCRL_MO));
      //   }
      //   return false;
      // }

      // レイヤー1の間は、TABは "コントロール + タブ" になる
      if (is_ctrl_tab_active) {
        case LT(1, KC_ESC): {
          disable_click_layer();

          if (record->event.pressed) {
            // キーダウン時:
          } else {
            // キーアップ時:
            is_ctrl_tab_active = false;
            unregister_code(KC_LCTRL);
          }
          return true;
        }
      }
    // レイヤー1の間は、TABは "コントロール + タブ" になる
    case KC_TAB: {
      if (get_highest_layer(layer_state) == 1) {
        if (record->event.pressed) {
          // キーダウン時:
          is_ctrl_tab_active = true;
          register_code(KC_LCTRL);
          enable_click_layer();
        } else {
          // キーアップ時:
        }
      }
      return true;
    }

    // 以下スワイプジェスチャー
    // クリックすると state が SWIPE になり、離したら NONE になる
    case CMD_T(KC_SPACE):
    case SFT_T(KC_LANG2):
    case ALT_T(KC_F13): {
      if (record->event.pressed) {
        // キーダウン時
        state = SWIPE;
      } else {
        // キーアップ時
        clear_mods();           // すべての修飾キーの状態をクリアする
        disable_click_layer();  // クリックレイヤーを無効化する
      }

      // 複数の修飾キーが押された場合、LEDをオフにし、スワイプ状態を解除する
      if (mod_pressed) {
        rgblight_sethsv(HSV_OFF);
        state = NONE;
        return true;  // キーのデフォルトの動作を続行させる
      }

      // スワイプが行われた場合、スワイプフラグをリセット
      if (is_swiped) {
        is_swiped = false;
        return false;  // キーのデフォルトの動作をスキップする
      }

      // スワイプが行われていなかった場合、キーのデフォルトの動作を続行させる
      if (!is_swiped) {
        return true;
      }
    }

      // MOD系
      // case KC_LCMD:
      // case KC_LALT:
      //   if (record->event.pressed)
      //   {
      //     // キーダウン時
      //     state = SWIPE;
      //     register_code(keycode);
      //   }
      //   else
      //   {
      //     // キーアップ時
      //     clear_mods();
      //     disable_click_layer();
      //     is_repeat = false;
      //   }
      //   return false;

      // TAP系
      // case KC_F:
      // case KC_D:
      // case KC_S:
      // uint16_t alt_tab_timer = 0;

      // TAP系（キーリピートあり）
      // case LT(2, KC_ESC):
      //   if (record->event.pressed)
      //   {
      //     // キーダウン時
      //     state = SWIPE;
      //     tap_code(keycode);
      //   }
      //   else
      //   {
      //     // キーアップ時
      //     if (is_swiped == true)
      //     {
      //       tap_code(KC_BSPC);
      //     }
      //     disable_click_layer();
      //     is_repeat = false;
      //     is_swiped = false;
      //   }
      //   return false;

      // TAP系（フリック風）
      // case KC_S:
      //   if (record->event.pressed)
      //   {
      //     // キーダウン時
      //     state = SWIPE;
      //     tap_code(keycode);
      //   }
      //   else
      //   {
      //     // キーアップ時
      //     disable_click_layer();
      //   }
      //   return false;

    // その他のキーコードの場合
    default:
      if (record->event.pressed) {
        // キーダウン時
        disable_click_layer();  // クリックレイヤーを無効化
      }
  }
  return true;
}