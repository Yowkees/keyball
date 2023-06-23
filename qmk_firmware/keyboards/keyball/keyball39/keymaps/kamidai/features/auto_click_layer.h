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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------
 *
 * 参考文献：
 * - 以下のリソースを参考にしました：
 *   https://zenn.dev/takashicompany/articles/69b87160cda4b9
 *
 */

enum ball_state {
  NONE = 0,
  WAITING,    // マウスレイヤーが有効になるのを待つ
  CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる
  CLICKING,   // クリック中
  CLICKED,    // クリック直後
  SWIPE,      // スワイプモードが有効になりスワイプ入力が取れる
  SWIPING     // スワイプ中

};

enum ball_state state;  // 現在のクリック入力受付の状態
uint16_t click_timer;   // タイマー。状態に応じて時間で判定する

uint16_t clicked_stay_time = 150;     // CLICKEDの滞在時間（千分の一秒)。その後、クリックレイヤーが無効になる
uint16_t clickable_stay_time = 1400;  // CLICKABLEの滞在時間（千分の一秒)。その後、クリックレイヤーが無効になる

const int16_t to_clickable_movement = 0;  // クリックレイヤーが有効になるしきい値
const uint16_t click_layer = 6;           // マウス入力が可能になった際に有効になるレイヤー

int16_t mouse_record_threshold = 30;  // ポインターの動きを一時的に記録するフレーム数
int16_t mouse_move_count_ratio = 5;   // ポインターの動きを再生する際の移動フレームの係数

// Modifierが絡むときの挙動が理想とは違ったので、一旦コメントアウト
// const uint16_t ignore_disable_mouse_layer_keys[] = {KC_LANG1, KC_LANG2}; // この配列で指定されたキーはマウスレイヤー中に押下してもマウスレイヤーを解除しない

int16_t mouse_movement;

// クリック用のレイヤーを有効にする
void enable_click_layer(void) {
  layer_on(click_layer);
  click_timer = timer_read();
  state = CLICKABLE;
}

// クリック用のレイヤーを無効にする
void disable_click_layer(void) {
  state = NONE;
  layer_off(click_layer);
}

// マウスレポートを受け取り、それに基づいて様々なアクションを実行する関数
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  int16_t current_x = mouse_report.x;  // 現在のマウスのX座標
  int16_t current_y = mouse_report.y;  // 現在のマウスのY座標

  // マウスが動いているかどうかチェック
  if (current_x != 0 || current_y != 0) {
    // マウスが動いたときのアクションを各状態ごとに制御する
    switch (state) {
      case WAITING:
        mouse_movement += my_abs(current_x) + my_abs(current_y);  // マウスの移動距離を加算

        // マウスの移動距離が閾値を超えた場合
        if (mouse_movement >= to_clickable_movement) {
          mouse_movement = 0;    // マウスの動きを0にリセット
          enable_click_layer();  // クリック可能状態（ state = CLICKABLE ）に遷移
        }
        break;

      case CLICKABLE:
        click_timer = timer_read();  // タイマーをリセット
        break;

      case CLICKING:
        // 状態が"クリック中"のときは何もしない
        break;

      case SWIPE:
        click_timer = timer_read();  // タイマーをリセット

        // マウスの移動が閾値を超えた場合、スワイプを処理
        if (my_abs(current_x) >= SWIPE_THRESHOLD || my_abs(current_y) >= SWIPE_THRESHOLD) {
          rgblight_sethsv(HSV_PINK);                    // LEDをピンクに変更
          process_swipe_gesture(current_x, current_y);  // スワイプジェスチャを処理
          is_swiped = true;

          // 一度のスワイプにつき、一回のジェスチャーを処理する
          if (is_repeat == false) {
            state = SWIPING;  // スワイプ中状態に遷移
          }
        }
        break;

      case SWIPING:
        // 状態が"スワイプ中"のときは何もしない
        break;

      default:
        click_timer = timer_read();  // タイマーをリセット
        state = WAITING;
        mouse_movement = 0;  // マウスの動きを0にリセット
    }
  } else {
    // マウスが動いていないとき、各状態ごとに以下のアクションに実行する
    switch (state) {
      case WAITING:
        // 一定時間が経過したら、マウスの動きを0にリセットし、状態をNONEに変更
        if (timer_elapsed(click_timer) > 50) {
          mouse_movement = 0;
          state = NONE;
        }
        break;

      case CLICKABLE:
        // クリック可能状態が一定時間持続したら、クリックレイヤーを無効化
        if (timer_elapsed(click_timer) > clickable_stay_time) {
          disable_click_layer();
        }
        break;

      case CLICKING:
        // 状態が"クリック中"のときは何もしない
        break;

      case CLICKED:
        // クリック後一定時間経過でクリックレイヤーを無効化
        if (timer_elapsed(click_timer) > clicked_stay_time) {
          disable_click_layer();
        }
        break;

      case SWIPE:
        rgblight_sethsv(HSV_SPRINGGREEN);  // LEDをスプリング・グリーンに変更
        break;

      case SWIPING:
        // 一定時間が経過したら、状態をSWIPEに変更
        if (timer_elapsed(click_timer) > 300) {
          state = SWIPE;
        }
        break;

      default:
        mouse_movement = 0;  // マウスの動きを0にリセット
        state = NONE;
    }
  }
  mouse_report.x = current_x;  // 新しいマウスのX座標をマウスレポートにセット
  mouse_report.y = current_y;  // 新しいマウスのY座標をマウスレポートにセット

  return mouse_report;  // マウスレポートを返す
}