/*
 * 当ファイルは、`KC_DOUBLE_CLICK_BTN1`または`KC_TRIPLE_CLICK_BTN1`が押された時にダブルクリック/トリプルクリックをシミュレートするために使用されます。
 * この機能を利用するためには、下記のコードブロックを対象ファイル（keymap.cなど）のprocess_record_user関数の内に挿入する必要があります。
 *
 ````````````````````````````````````````````````````````````````
    bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      switch (keycode) {

        // 挿入ここから

        case KC_DOUBLE_CLICK_BTN1:
        case KC_TRIPLE_CLICK_BTN1: {
          if (record->event.pressed) {
            // キーダウン時
            // `KC_DOUBLE_CLICK_BTN1`の場合
            if (keycode == KC_DOUBLE_CLICK_BTN1) {
              double_click_mouse_button1();  // マウスボタン1をダブルクリック
            }
            // `KC_TRIPLE_CLICK_BTN1`の場合
            if (keycode == KC_TRIPLE_CLICK_BTN1) {
              triple_click_mouse_button1();  // マウスボタン1をトリプルクリック
            }
          } else {
            if (click_layer && get_highest_layer(layer_state) == click_layer) {
              // キーアップ時: クリックレイヤーを有効にして、状態をCLICKEDに設定
              enable_click_layer();
              state = CLICKED;
            }
          }
          return false;  // キーのデフォルトの動作をスキップする
        }

        // 挿入ここまで

        default: {
        }
      }
    }
 ````````````````````````````````````````````````````````````````
 */

// マウスのボタン1の状態を設定し、マウスデバイスに新しい状態を送信する関数
void update_mouse_button1(bool pressed) {
  // 現在のマウスの状態を取得する
  report_mouse_t currentReport = pointing_device_get_report();

  if (pressed) {
    currentReport.buttons |= MOUSE_BTN1;  // ボタン1を押下状態に設定する
  } else {
    currentReport.buttons &= ~MOUSE_BTN1;  // ボタン1をリリース状態に設定する
  }

  pointing_device_set_report(currentReport);  // 新しい状態をマウスデバイスに設定する
  pointing_device_send();                     // マウスデバイスに新しい状態を送信する
}

// マウスのボタン1をクリックする関数
void click_mouse_button1(void) {
  update_mouse_button1(true);
}

// マウスのボタン1をリリースする関数
void release_mouse_button1(void) {
  update_mouse_button1(false);
}

// マウスのボタン1をクリックし、指定された時間（ミリ秒）待つ関数
void click_and_wait_mouse_button1(uint16_t wait_time) {
  click_mouse_button1();    // マウスのボタン1をクリック
  wait_ms(wait_time);       // 待機する
  release_mouse_button1();  // マウスのボタン1をリリース
  wait_ms(wait_time);       // 待機する
}

// マウスのボタン1をダブルクリックする関数
void double_click_mouse_button1(void) {
  for (int i = 0; i < 2; i++) {
    click_and_wait_mouse_button1(50);
  }
}

// マウスのボタン1をダブルクリックする関数
void triple_click_mouse_button1(void) {
  for (int i = 0; i < 3; i++) {
    click_and_wait_mouse_button1(50);
  }
}
