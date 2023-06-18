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

enum custom_keycodes
{
  KC_MY_BTN0 = KEYBALL_SAFE_RANGE, // Remap上では 0x5DAF（レイヤー0に遷移できるBTN1）
  KC_MY_BTN1,                      // Remap上では 0x5DB0
  KC_MY_BTN2,                      // Remap上では 0x5DB1
  KC_MY_BTN3,                      // Remap上では 0x5DB2
};

// マクロキーを設定
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  current_keycode = keycode;

  switch (keycode)
  {
  case KC_MY_BTN0:
  case KC_MY_BTN1:
  case KC_MY_BTN2:
  case KC_MY_BTN3:
  {
    report_mouse_t currentReport = pointing_device_get_report();

    // どこのビットを対象にするか。 Which bits are to be targeted?
    uint8_t btn = 1 << (keycode - KC_MY_BTN1);

    if (record->event.pressed)
    {
      // キーダウン時
      // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
      // Bit OR compares bits in the same position on the left and right sides of the operator and sets them to "1" if either of both bits is "1".
      currentReport.buttons |= btn;
      state = CLICKING;
    }
    else
    {
      // キーアップ時
      // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
      // Bit AND compares the bits in the same position on the left and right sides of the operator and sets them to "1" only if both bits are "1" together.
      currentReport.buttons &= ~btn;
      enable_click_layer();
      state = CLICKED;

      if (keycode == KC_MY_BTN0)
      {
        disable_click_layer();
      }
    }

    pointing_device_set_report(currentReport);
    pointing_device_send();
    return false;
  }

    // 自動クリックレイヤーでLang1とLang2を押せるようにする
    // case KC_LANG1:
    // case KC_LANG2:
    // {
    //   if (state == CLICKABLE)
    //   {
    //     if (record->event.pressed)
    //     {
    //       // キーダウン時
    //       enable_click_layer();
    //       return true;
    //     }
    //     else
    //     {
    //       // キーアップ時
    //       disable_click_layer();
    //     }
    //   }
    // }

    // 右shiftホールド中はスクロールモードにする
    // case RSFT_T(KC_LANG1):
    //   if (record->event.pressed)
    //   {
    //     // キーダウン時
    //     disable_click_layer();
    //     keyball_set_scroll_mode(true);
    //   }
    //   else
    //   {
    //     // キーアップ時
    //     keyball_set_scroll_mode(false);
    //   }
    //   return true;

    // クリックすると state が SWIPE になり、離したら NONE になる
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

  // モッドタップ系
  case LCMD_T(KC_SPACE):
  case LSFT_T(KC_LANG2):
  case LCTL_T(KC_F13):
    // case KC_LALT:
    if (record->event.pressed)
    {
      // キーダウン時
      state = SWIPE;
    }
    else
    {
      // キーアップ時
      clear_mods();
      disable_click_layer();
    }

    if (is_swiped == true)
    {
      is_swiped = false;
      return false;
    }
    if (is_swiped == false)
    {
      return true;
    }

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

    // f13
    // case LCTL_T(KC_F13):
    //   if (record->event.pressed)
    //   {
    //     // キーが押されたとき
    //     register_mods(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI); // Control, Shift, Option, そして Command を押す
    //     register_code(KC_C);                                      // C を押す
    //   }
    //   else
    //   {
    //     // キーが離されたとき
    //     unregister_code(KC_C);                                      // C を離す
    //     unregister_mods(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI); // Control, Shift, Option, そして Command を離す
    //   }
    //   return false; // このキーの他の全ての処理をスキップする

  default:
    if (record->event.pressed)
    {
      // キーダウン時
      disable_click_layer();
    }
  }

  return true;
}