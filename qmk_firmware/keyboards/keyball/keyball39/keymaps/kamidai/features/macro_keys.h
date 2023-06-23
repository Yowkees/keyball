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
 */

enum custom_keycodes {
  KC_BACK_TO_LAYER0_BTN1 = KEYBALL_SAFE_RANGE,  // (0x5DAF): レイヤー0に遷移できるBTN1
  KC_DOUBLE_CLICK_BTN1,                         // (0x5DB0): 1タップでダブルクリックできるBTN1
  KC_TRIPLE_CLICK_BTN1,                         // (0x5DB1): 1タップでトリプルクリックできるBTN1
};

// マクロキーの処理を行う関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  current_keycode = keycode;             // 押下されたキーコードを保存する
  bool mod_pressed = (get_mods() != 0);  // 修飾キーが押されているかを判定（0でなければ修飾キーが押されている）

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
    // case SCRL_MO:
    case ALT_T(KC_F13): {
      return true;
    }

    // 以下スワイプジェスチャー
    // クリックすると state が SWIPE になり、離したら NONE になる
    // モッドタップ系
    case CMD_T(KC_SPACE):
    case SFT_T(KC_LANG2):
    case CTL_T(KC_F14): {
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