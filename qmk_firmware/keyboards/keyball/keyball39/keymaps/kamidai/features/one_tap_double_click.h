/*
 * `one_tap_double_click.h`で定義された関数`handle_double_click`は、マウスボタン1（KC_MS_BTN1）が押された時にダブルクリックをシミュレートするために使用されます。
 * このコードを利用するためには、 以下のコードを適切な位置に挿入する必要があります。
 *
 * ---------------------------------------------------------------------------
 *    // handle_double_click関数はone_tap_double_click.hの中で定義されています
 *    // この関数はマウスボタン1（KC_MS_BTN1）が押されたときにダブルクリックを実行しますs
 *    // 戻り値がfalseの場合は、process_record_user関数から即座にfalseを返し、それ以降の操作をスキップします
 *    if (!handle_double_click(keycode, record)) {
 *      return false;
 *    }
 * ---------------------------------------------------------------------------
 *
 * 具体的には、以下のように`process_record_user`関数が定義されている`keymap.c`内の、`process_record_user`関数内に挿入してください。
 *
 *
 *    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 *
 *        <上記のコードここに挿入してください>
 *
 *        case KC_MY_BTN1: {
 *
 *        }
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

// ユーザーが特定のキーコードを操作したときの動作を制御する関数
bool handle_double_click(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // キーコードがマウスボタン1の場合
    case KC_MS_BTN1: {
      if (record->event.pressed) {
        // キーダウン時
        double_click_mouse_button1();  // マウスボタン1をダブルクリック
      }
      return false;  // キーのデフォルトの動作をスキップする
    }
  }
  return true;  // デフォルトの動作を実行する
}
