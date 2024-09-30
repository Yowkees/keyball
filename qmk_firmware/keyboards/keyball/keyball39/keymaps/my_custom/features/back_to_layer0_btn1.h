/*
 * 当ファイルは、`KC_BACK_TO_LAYER0_BTN1`が押された時に即座にlayer0へ戻るために使用されます。
 * この機能を利用するためには、下記のコードブロックを対象ファイル（keymap.cなど）のprocess_record_user関数の内に挿入する必要があります。
 *
 ````````````````````````````````````````````````````````````````
    bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      switch (keycode) {

        // 挿入ここから

        case KC_BACK_TO_LAYER0_BTN1: {
          if (record->event.pressed) {
            // キーダウン時: 状態をCLICKINGに設定
            click_mouse_button1();  // マウスのボタン1をクリック
            state = CLICKING;
          } else {
            // キーアップ時: 状態をCLICKEDに設定
            release_mouse_button1();  // マウスのボタン1をリリース
            enable_click_layer();
            state = CLICKED;

            // クリックレイヤーを無効化
            disable_click_layer();
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