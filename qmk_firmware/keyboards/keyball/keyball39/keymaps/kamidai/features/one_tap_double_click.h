/*
 * 当ファイルは、`KC_DOUBLE_CLICK_BTN1`が押された時にダブルクリックをシミュレートするために使用されます。
 * この機能を利用するためには、下記のコードを適切な位置に挿入する必要があります。
 *
 ````````````````````````````````````````````````````````````````
    case KC_DOUBLE_CLICK_BTN1: {
      if (record->event.pressed) {
        // キーダウン時
        double_click_mouse_button1();  // マウスボタン1をダブルクリック
      }
      return false;  // キーのデフォルトの動作をスキップする
    }
 ````````````````````````````````````````````````````````````````
 *
 * 挿入例: 対象ファイル（例：keymap.c）のprocess_record_user関数の内
 *
 *    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 *      switch (keycode) {
 *
 *        <上記のコードをここに挿入してください>
 *
 *        default: {
 *        }
 *      }
 *    }
 */

// マウスのボタン1をクリックする関数
void click_mouse_button1(void) {
  // 現在のマウスの状態を取得する
  report_mouse_t currentReport = pointing_device_get_report();

  // ボタン1を押下状態に設定する
  currentReport.buttons |= MOUSE_BTN1;

  // 新しい状態をマウスデバイスに設定する
  pointing_device_set_report(currentReport);

  // マウスデバイスに新しい状態を送信する
  pointing_device_send();
}

// マウスのボタン1をリリースする関数
void release_mouse_button1(void) {
  // 現在のマウスの状態を取得する
  report_mouse_t currentReport = pointing_device_get_report();

  // ボタン1をリリース状態に設定する
  currentReport.buttons &= ~MOUSE_BTN1;

  // 新しい状態をマウスデバイスに設定する
  pointing_device_set_report(currentReport);

  // マウスデバイスに新しい状態を送信する
  pointing_device_send();
}

// マウスのボタン1をダブルクリックする関数
void double_click_mouse_button1(void) {
  // 1回目のクリック
  click_mouse_button1();    // マウスのボタン1をクリック
  wait_ms(50);              // 50ミリ秒待機する
  release_mouse_button1();  // マウスのボタン1をリリース

  // 50ミリ秒待機する
  wait_ms(50);

  // 2回目のクリック
  click_mouse_button1();    // マウスのボタン1を再度クリック
  wait_ms(50);              // 50ミリ秒待機する
  release_mouse_button1();  // マウスのボタン1を再度リリース
}
