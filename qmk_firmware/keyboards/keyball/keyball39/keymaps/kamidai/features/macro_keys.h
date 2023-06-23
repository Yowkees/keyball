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
  KC_TO_LAYER_0_BTN1 = KEYBALL_SAFE_RANGE,  // Remap上では 0x5DAF: レイヤー0に遷移できるBTN1
  KC_MY_BTN1,                               // Remap上では 0x5DB0
  KC_MY_BTN2,                               // Remap上では 0x5DB1
  KC_MY_BTN3,                               // Remap上では 0x5DB2
  KC_MY_BTN4,                               // Remap上では 0x5DB3
  KC_MY_BTN5,                               // Remap上では 0x5DB4
  KC_DOUBLE_CLICK_BTN1,                     // Remap上では 0x5DB5: ダブルクリックできるBTN1
};

// マクロキーの処理を行う関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  current_keycode = keycode;             // 押下されたキーコードを保存する
  bool mod_pressed = (get_mods() != 0);  // 修飾キーが押されているかを判定（0でなければ修飾キーが押されている）

  switch (keycode) {
    case KC_TO_LAYER_0_BTN1:
    case KC_MY_BTN1:
    case KC_MY_BTN2:
    case KC_MY_BTN3:
    case KC_MY_BTN4:
    case KC_MY_BTN5: {
      report_mouse_t currentReport = pointing_device_get_report();  // 現在のマウス状態を取得する

      // キーコードに基づいて、対象とするボタンを決定
      uint8_t btn = 1 << (keycode - KC_MY_BTN1);  // 対象ボタンのビット位置を設定

      if (record->event.pressed) {
        // キーダウン時
        // 対象のボタンを有効にし、状態をCLICKINGに設定
        currentReport.buttons |= btn;  // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
        state = CLICKING;
      } else {
        // キーアップ時
        // 対象のボタンを無効にし、クリックレイヤーを有効にして、状態をCLICKEDに設定
        currentReport.buttons &= ~btn;  // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
        enable_click_layer();
        state = CLICKED;

        // キーコードがKC_MY_BTN0の場合はクリックレイヤーを無効化
        if (keycode == KC_TO_LAYER_0_BTN1) {
          disable_click_layer();
        }
      }

      pointing_device_set_report(currentReport);  // マウスの状態（ボタンの押下状態）をcurrentReportの内容で更新する
      pointing_device_send();                     // 更新したマウスの状態をシステムに送信する
      return false;                               // キーのデフォルトの動作をスキップする
    }

    // altキーはデフォルトの動作を続行させる
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

    default:
      // その他のキーコードの場合
      if (record->event.pressed) {
        // キーダウン時
        disable_click_layer();  // クリックレイヤーを無効化
      }
  }

  return true;
}