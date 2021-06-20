# Keyball のカスタマイズ可能な機能

## トラックボール

### `TRACKBALL_DRIVER_DISABLE`

Keyballに付属のデフォルトのトラックボールドライバーを無効化する設定項目です。
各キーマップで独自のドライバーを用意する場合に設定することで、デフォルトドライ
バーが省略されその分ファームウェアが小さくなります。

各キーマップの config.h で設定できます。

設定例:

```c
#define TRACKBALL_DRIVER_DISABLE 100
```

### `TRACKBALL_SAMPLE_COUNT`

トラックボールでは光学センサから数回に渡って読み取った平均値をポインティングデ
バイスの移動量として送信しており、 `TRACKBALL_SAMPLE_COUNT` はその回数を指定す
る設定項目です。

各キーマップの config.h で設定できます。デフォルトは `10` で `0` 以下の値を設定
するとコンパイルエラーになります。

設定例:

```c
#define TRACKBALL_SAMPLE_COUNT 100
```

### `TRACKBALL_SCROLL_DIVIDER`

スクロールモードが有効な場合、トラックボールはトラックボールの移動量をマウスカーソルではなくスクロール量として送信しますが、送る時に移動量が小さくなるように割っており、 `TRACKBALL_SCROLL_DIVIDER` はその分母を指定する設定項目です。

各キーマップの config.h で設定できます。デフォルトは `10` で `0` 以下の値を設定
するとコンパイルエラーになります。

### `trackball_process_user()`

`trackball_process_user()` 関数を定義するとトラックボールの移動量をどのよ
うに扱うかをユーザーがカスタマイズできます。`trackball_process_user()` は
ドライバーがトラックボールの移動を検知した際に、その移動量を引数にして呼び出し
ます。ユーザーはポインティングデバイスとしてレポートを送っても良いですし、それ
以外のことをしてもかまいません。

スクロールモードが有効な場合、渡される移動量は `TRACKBALL_SCROLL_DIVIDER` を考
慮した値になります。

各キーマップの keymap.c で定義できます。

定義例: マウスカーソルに上下反転させて適用する

```c
void trackball_process_user(int8_t dx, int8_t dy) {
    report_mouse_t r = pointing_device_get_report();
    r.x = -dx;
    r.y = -dy;
    pointing_device_set_report(r);
}
```

### `bool trackball_get_scroll_mode(void)` API

トラックボールの現在のスクロールモードを取得します。

### `void trackball_set_scroll_mode(bool mode)` API

トラックボールのスクロールモードを変更します。
