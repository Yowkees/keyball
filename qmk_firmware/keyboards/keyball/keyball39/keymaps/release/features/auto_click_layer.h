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
 */

////////////////////////////////////
///
/// 自動マウスレイヤーの実装 ここから
/// 参考にさせていただいたページ
/// https://zenn.dev/takashicompany/articles/69b87160cda4b9
///
////////////////////////////////////

enum ball_state {
  NONE = 0,
  WAITING,    // マウスレイヤーが有効になるのを待つ。 Wait for mouse layer to activate.
  CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる。 Mouse layer is enabled to take click input.
  CLICKING,   // クリック中。 Clicking.
  CLICKED,    // クリック直後。 Clicked.
  SWIPE,      // スワイプモードが有効になりスワイプ入力が取れる。 Swipe mode is enabled to take swipe input.
  SWIPING     // スワイプ中。 swiping.
};

enum ball_state state;  // 現在のクリック入力受付の状態 Current click input reception status
uint16_t click_timer;   // タイマー。状態に応じて時間で判定する。 Timer. Time to determine the state of the system.

uint16_t clicked_stay_time = 200;     // CLICKEDの滞在時間（千分の一秒)。その後、クリックレイヤーが無効になる。 For this number of seconds (milliseconds), the click layer is disabled if in CLICKED state.
uint16_t clickable_stay_time = 1600;  // CLICKABLEの滞在時間（千分の一秒)。その後、クリックレイヤーが無効になる。 For this number of seconds (milliseconds), the click layer is disabled if in CLICKABLE state.

const int16_t to_clickable_movement = 0;  // クリックレイヤーが有効になるしきい値
const uint16_t click_layer = 6;           // マウス入力が可能になった際に有効になるレイヤー。Layers enabled when mouse input is enabled

int16_t mouse_record_threshold = 30;  // ポインターの動きを一時的に記録するフレーム数。 Number of frames in which the pointer movement is temporarily recorded.
int16_t mouse_move_count_ratio = 5;   // ポインターの動きを再生する際の移動フレームの係数。 The coefficient of the moving frame when replaying the pointer movement.

// Modifierが絡むときの挙動が理想とは違ったので、一旦コメントアウト
// const uint16_t ignore_disable_mouse_layer_keys[] = {KC_LANG1, KC_LANG2}; // この配列で指定されたキーはマウスレイヤー中に押下してもマウスレイヤーを解除しない

int16_t mouse_movement;

// クリック用のレイヤーを有効にする。　Enable layers for clicks
void enable_click_layer(void) {
  layer_on(click_layer);
  click_timer = timer_read();
  state = CLICKABLE;
}

// クリック用のレイヤーを無効にする。 Disable layers for clicks.
void disable_click_layer(void) {
  state = NONE;
  layer_off(click_layer);
}

//
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  int16_t current_x = mouse_report.x;
  int16_t current_y = mouse_report.y;

  if (current_x != 0 || current_y != 0) {
    switch (state) {
      case CLICKABLE:
        click_timer = timer_read();
        break;

      case CLICKING:
        break;

      case WAITING:
        mouse_movement += my_abs(current_x) + my_abs(current_y);

        if (mouse_movement >= to_clickable_movement) {
          mouse_movement = 0;
          enable_click_layer();
        }
        break;

      case SWIPE:
        click_timer = timer_read();

        if (my_abs(current_x) >= SWIPE_THRESHOLD || my_abs(current_y) >= SWIPE_THRESHOLD) {
          rgblight_sethsv(HSV_PINK);
          process_swipe_gesture(current_x, current_y);
          is_swiped = true;

          if (is_repeat == false) {
            state = SWIPING;
          }
        }
        break;

      case SWIPING:
        break;

      default:
        click_timer = timer_read();
        state = WAITING;
        mouse_movement = 0;
    }
  } else {
    switch (state) {
      case CLICKING:
        break;

      case CLICKED:
        if (timer_elapsed(click_timer) > clicked_stay_time) {
          disable_click_layer();
        }
        break;
      case CLICKABLE:
        if (timer_elapsed(click_timer) > clickable_stay_time) {
          disable_click_layer();
        }
        break;

      case WAITING:
        if (timer_elapsed(click_timer) > 50) {
          mouse_movement = 0;
          state = NONE;
        }
        break;

      case SWIPE:
        rgblight_sethsv(HSV_SPRINGGREEN);
        break;

      case SWIPING:
        if (timer_elapsed(click_timer) > 300) {
          state = SWIPE;
        }
        break;

      default:
        mouse_movement = 0;
        state = NONE;
    }
  }
  mouse_report.x = current_x;
  mouse_report.y = current_y;

  return mouse_report;
}