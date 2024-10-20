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
  SFT_T_G_KC_A,                                 // (0x5DB2):
  SFT_T_S_KC_SCOLON,                            // (0x5DB3):
  COMBO_BRC,                                    // (0x5DB5):
  COMBO_select_BRC,                             // (0x5DB5):
  COMBO_S9_S0,                                  // (0x5DB5):
  COMBO_select_S9_S0,                           // (0x5DB5):
  COMBO_S_BRC,                                  // (0x5DB5):
  COMBO_select_S_BRC,                           // (0x5DB5):
  COMBO_sumitsuki_BRC,                          // (0x5DB5):
  COMBO_select_sumitsuki_BRC,                   // (0x5DB5):
  COMBO_MINUS_SPACE,                            // (0x5DB5):
  // CUSTOM_LT1_LEFT,                                    //
  // CUSTOM_LT1_LEFT,                                    //
  // CUSTOM_S9,                                    //
  // CUSTOM_S0,                                    //
  // KC_ALT_BTN1,                                  //
  // select_BRC,
  // CMD_SCRL,
};

// マクロキーの処理を行う関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  current_keycode = keycode;             // 押下されたキーコードを保存する
  bool mod_pressed = (get_mods() != 0);  // 修飾キーが押されているかを判定（0でなければ修飾キーが押されている）

  static bool is_gui_active = false;
  static bool is_ctrl_active = false;

  static bool is_lt1_pressed = false;  // レイヤー1の状態を追跡する変数
  static bool is_lt2_pressed = false;  // レイヤー2の状態を追跡する変数
  static bool is_lt3_pressed = false;  // レイヤー3の状態を追跡する変数

  // static bool is_eisuu = false;  // レイヤー1の状態を追跡する変数
  static bool is_kana = false;  // レイヤー1の状態を追跡する変数

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

      // レイヤー1の間は、TABは "command + タブ" になる
      // レイヤー3の間は、TABは "control + タブ" になる
    case KC_TAB: {
      if (record->event.pressed) {
        is_gui_active = true;

        if (get_highest_layer(layer_state) == 1) {
          // キーダウン時:
          register_code(KC_LGUI);
          is_gui_active = true;
          // tap_code(KC_TAB);
          enable_click_layer();
        } else if (get_highest_layer(layer_state) == 3) {
          // キーダウン時:
          register_code(KC_LCTRL);
          is_ctrl_active = true;
          // tap_code(KC_TAB);
          enable_click_layer();
        }
      }
      return true;
    }

      // 上位レイヤーから下位レイヤーへ移動できるようにする
      //   case LT(1, KC_LANG2):
      //   case LT(1, KC_LANG1):
      //   case LT(2, KC_V):
      //   case S(KC_8): {
      //     // int16_t hlayer = get_highest_layer(layer_state);
      //     // if (get_highest_layer(layer_state) == 2) {
      //     if (record->event.pressed) {
      //       // キーダウン時:
      //       lt_timer = timer_read();                          // 現在のタイマー値を記録
      //       previous_layer = get_highest_layer(layer_state);  // 現在の最上位レイヤーを記録
      //       layer_off(previous_layer);                        // 現在のレイヤーをオフにする

      //       if (keycode == LT(1, KC_LANG2) || keycode == LT(1, KC_LANG1)) {
      //         layer_on(1);
      //       } else if (keycode == LT(2, KC_V) || keycode == S(KC_8)) {
      //         layer_on(2);
      //       }
      //     } else {
      //       // キーアップ時:
      //       layer_on(previous_layer);  // 前のレイヤーをオンにする
      //       if (keycode == LT(1, KC_LANG2) || keycode == LT(1, KC_LANG1)) {
      //         layer_off(1);
      //       } else if (keycode == LT(2, KC_V) || keycode == S(KC_8)) {
      //         layer_off(2);
      //       }
      //       if (timer_elapsed(lt_timer) < TAPPING_TERM) {
      //         // タッピングタイム内に放された場合はタップ動作
      //         if (keycode == LT(1, KC_LANG2)) {
      //           tap_code(KC_LANG2);
      //         } else if (keycode == LT(1, KC_LANG1)) {
      //           tap_code(KC_LANG1);
      //         } else if (keycode == LT(2, KC_V)) {
      //           tap_code(KC_V);
      //         } else if (keycode == S(KC_8)) {
      //           tap_code16(S(KC_8));
      //         }
      //       }

      //     }
      //   }
      //     return false;
      // }

      static bool is_lt1_lang2_pressed = false;  // LT(1, KC_LANG2)の状態を追跡
      static bool is_lt1_lang1_pressed = false;  // LT(1, KC_LANG1)の状態を追跡

      // 上位レイヤーから下位レイヤーへ移動できるようにする
    case LT(1, KC_LANG2):  // レイヤー1へのキー
    case LT(1, KC_LANG1):  // レイヤー1へのキー
      if (record->event.pressed) {
        click_timer = timer_read();
        is_lt1_pressed = true;
        if (keycode == LT(1, KC_LANG2)) {
          is_lt1_lang2_pressed = true;
        } else if (keycode == LT(1, KC_LANG1)) {
          is_lt1_lang1_pressed = true;
        }
        layer_on(1);  // レイヤー1をオンにする
        disable_click_layer();

        if (is_lt2_pressed) {
          layer_off(2);  // LT2が既に押されていればレイヤー2をオフにする
        } else if (is_lt3_pressed) {
          layer_off(3);  // LT3が既に押されていればレイヤー3をオフにする
        }
      } else {
        is_lt1_pressed = false;
        if (keycode == LT(1, KC_LANG2)) {
          is_lt1_lang2_pressed = false;
        } else if (keycode == LT(1, KC_LANG1)) {
          is_lt1_lang1_pressed = false;
        }
        if (!is_lt1_lang2_pressed && !is_lt1_lang1_pressed) {
          layer_off(1);
        }
        if (is_lt2_pressed) {
          layer_on(2);  // LT2が押されていればレイヤー2をオンにする
        } else if (is_lt3_pressed) {
          layer_on(3);  // LT3が押されていればレイヤー3をオンにする
        }

        if (timer_elapsed(click_timer) < TAPPING_TERM) {
          // タッピングタイム内に放された場合はタップ動作
          if (keycode == LT(1, KC_LANG2)) {
            tap_code(KC_LANG2);
            // is_eisuu = true;
            is_kana = false;
          } else if (keycode == LT(1, KC_LANG1)) {
            tap_code(KC_LANG1);
            is_kana = true;
          }
        }

        if (is_gui_active) {
          unregister_code(KC_LGUI);
          is_gui_active = false;
        }
      }
      return false;

    case LT(2, KC_V):  // レイヤー2へのキー
    case S(KC_DOT):    // レイヤー2へのキー
      if (record->event.pressed) {
        click_timer = timer_read();
        is_lt2_pressed = true;
        layer_on(2);  // レイヤー2をオンにする
        disable_click_layer();

        if (is_lt1_pressed) {
          layer_off(1);  // LT1が既に押されていればレイヤー1をオフにする
        } else if (is_lt3_pressed) {
          layer_off(3);  // LT3が既に押されていればレイヤー3をオフにする
        }
      } else {
        is_lt2_pressed = false;
        layer_off(2);  // LTが押されていなければレイヤー2をオフにする

        if (is_lt1_pressed) {
          layer_on(1);  // LT1が押されていればレイヤー1をオンにする
        } else if (is_lt3_pressed) {
          layer_on(3);  // LT1が押されていればレイヤー1をオンにする
        }

        if (timer_elapsed(click_timer) < TAPPING_TERM) {
          // タッピングタイム内に放された場合はタップ動作
          if (keycode == LT(2, KC_V)) {
            tap_code(KC_V);
          } else if (keycode == S(KC_DOT)) {
            tap_code16(S(KC_DOT));
          }
        }
      }
      return false;

    case LT(3, KC_ESC):  // レイヤー3へのキー
      if (record->event.pressed) {
        click_timer = timer_read();
        is_lt3_pressed = true;
        layer_on(3);  // レイヤー3をオンにする
        disable_click_layer();

        if (is_lt1_pressed) {
          layer_off(1);  // LT1が既に押されていればレイヤー1をオフにする
        } else if (is_lt2_pressed) {
          layer_off(2);  // LT2が既に押されていればレイヤー2をオフにする
        }
      } else {
        is_lt3_pressed = false;
        layer_off(3);  // LT3をオフにする

        if (is_lt1_pressed) {
          layer_on(1);  // LT1が押されていればレイヤー1をオンにする
        } else if (is_lt2_pressed) {
          layer_on(2);  // LT2が押されていればレイヤー2をオンにする
        }

        if (timer_elapsed(click_timer) < TAPPING_TERM) {
          // タッピングタイム内に放された場合はタップ動作
          tap_code(KC_ESC);
        }

        if (is_ctrl_active) {
          unregister_code(KC_LCTRL);
          is_ctrl_active = false;
        }
      }
      return false;

      // SFT_Tのカスタムキーコード
    case SFT_T_G_KC_A:
    case SFT_T_S_KC_SCOLON:
      if (record->event.pressed) {
        // キーが押されたとき
        click_timer = timer_read();
        register_code(KC_LSFT);
      } else {
        // キーが放されたとき
        unregister_code(KC_LSFT);

        if (timer_elapsed(click_timer) < TAPPING_TERM) {
          // タッピングタイム内に放された場合はタップ動作
          if (keycode == SFT_T_G_KC_A) {
            tap_code16(G(KC_A));
          }
          if (keycode == SFT_T_S_KC_SCOLON) {
            tap_code16(S(KC_SCOLON));
          }
        }
      }
      return false;

      // コンボ
    case COMBO_MINUS_SPACE:
      if (record->event.pressed) {
        tap_code(KC_LANG2);  //
        tap_code(KC_MINUS);  // -　を送信
        tap_code(KC_SPACE);  //  スペース を送信
        tap_code(KC_LANG1);  //
      }
      return false;

    case COMBO_BRC:
    case COMBO_select_BRC:
    case COMBO_S9_S0:
    case COMBO_select_S9_S0:
    case COMBO_S_BRC:
    case COMBO_select_S_BRC:
    case COMBO_sumitsuki_BRC:
    case COMBO_select_sumitsuki_BRC:
      if (record->event.pressed) {
        // 選択バージョン
        if (keycode == COMBO_select_BRC || keycode == COMBO_select_S9_S0 || keycode == COMBO_select_S_BRC || keycode == COMBO_select_sumitsuki_BRC) {
          tap_code16(G(KC_X));  // カット
        }

        // if (keycode == COMBO_BRC || keycode == COMBO_S9_S0 || keycode == COMBO_S_BRC || keycode == COMBO_sumitsuki_BRC) {
        if (keycode == COMBO_BRC || keycode == COMBO_select_BRC) {
          tap_code(KC_LBRC);  // 「　を送信
          tap_code(KC_RBRC);  //  」 を送信
        } else if (keycode == COMBO_S9_S0 || keycode == COMBO_select_S9_S0) {
          tap_code16(S(KC_9));  // （　を送信
          tap_code16(S(KC_0));  //  ） を送信
        } else if (keycode == COMBO_S_BRC || keycode == COMBO_select_S_BRC) {
          tap_code16(S(KC_LBRC));  // 『　を送信
          tap_code16(S(KC_RBRC));  //  』 を送信
        } else if (keycode == COMBO_sumitsuki_BRC || keycode == COMBO_select_sumitsuki_BRC) {
          tap_code16(A(KC_9));  // 　を送信
          tap_code16(A(KC_0));  //  ） を送信
        }
        // かなの場合にKC_ENTを送信
        if (is_kana) {
          tap_code(KC_ENT);
        }
        // KC_LEFT を送信
        tap_code(KC_LEFT);
        // }

        // 選択バージョン
        if (keycode == COMBO_select_BRC || keycode == COMBO_select_S9_S0 || keycode == COMBO_select_S_BRC || keycode == COMBO_select_sumitsuki_BRC) {
          tap_code16(G(KC_V));  // ペースト
          wait_ms(130);         // 0.1秒（1300ミリ秒）待機
          tap_code(KC_RIGHT);
        }

        // KC_RIGHT を送信
        // if (keycode == COMBO_select_BRC || keycode == COMBO_select_S9_S0) {
        //   wait_ms(100);  // 1秒（1000ミリ秒）待機
        //   tap_code(KC_RIGHT);
        // }

        // if (keycode == COMBO_select_BRC) {
        //   if (keycode == COMBO_select_BRC) {
        //     tap_code16(G(KC_X));  // カット
        //     tap_code(KC_LBRC);    // 「　を送信

        //     // かなの場合にKC_ENTを送信
        //     if (is_kana) {
        //       tap_code(KC_ENT);
        //     }

        //     tap_code16(G(KC_V));  // ペースト
        //     wait_ms(1000);        // 1秒（1000ミリ秒）待機

        //     tap_code(KC_RBRC);  //  」 を送信

        //     // かなの場合にKC_ENTを送信
        //     if (is_kana) {
        //       tap_code(KC_ENT);
        //     }
        //   }
        // }
      }
      return false;

      // karabinerでのコンボ用
      // case CUSTOM_S9:
      //   if (record->event.pressed) {
      //     register_code(KC_LSFT);
      //     register_code(KC_9);
      //   } else {
      //     unregister_code(KC_9);
      //     unregister_code(KC_LSFT);
      //   }
      //   return false;
      // case CUSTOM_S0:
      //   if (record->event.pressed) {
      //     register_code(KC_LSFT);
      //     register_code(KC_0);
      //   } else {
      //     unregister_code(KC_0);
      //     unregister_code(KC_LSFT);
      //   }
      //   return false;

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