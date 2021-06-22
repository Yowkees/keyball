# Keyball のカスタマイズ可能な機能

## トラックボールドライバ

Keyballに搭載されているトラックボールのドライバーです。

### `TRACKBALL_DRIVER_DISABLE`

Keyballに付属のデフォルトのトラックボールドライバーを無効化する設定項目です。
各キーマップで独自のドライバーを用意する場合に設定することで、デフォルトドライ
バーが省略されその分ファームウェアが小さくなります。

各キーマップの config.h で設定できます。

設定例:

```c
#define TRACKBALL_DRIVER_DISABLE
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

## OLED Kit

OLED KitはKeyballのキーマップがOLEDにロゴなどの各種情報を表示するのを容易にする
ためのライブラリです。キーマップの rules.mk に `OLED_DRIVER_ENABLE = yes` を追
加すれば自動的に利用されますが、キーマップで表示内容をカスタマイズすることもで
きます。

表示内容をカスタマイズするには keymap.c 等に以下の2つを追加してください。

1. `#include "oledkit.h"`
2. `void oledkit_render_info_user(void)` を定義する

`oledkit_render_info_user()` はプライマリ(USBケーブルが接続されている)側のキー
ボードに情報を表示する際にコールバックされる関数です。レイヤー状態などの各種情
報を `oled_write_*()` を用いてプライマリ側のOLEDに描画することができます。

例: keymaps/default/keymap.c より抜粋

```c
#ifdef OLED_DRIVER_ENABLE

void oledkit_render_info_user(void) {
    const char *n;
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            n = PSTR("Default");
            break;
        case _RAISE:
            n = PSTR("Raise");
            break;
        case _LOWER:
            n = PSTR("Lower");
            break;
        case _BALL:
            n = PSTR("Adjust");
            break;
        default:
            n = PSTR("Undefined");
            break;
    }
    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln_P(n, false);
}

#endif
```

この例は現在アクティブなレイヤー名を表示するという、OLEDの良くある利用方法で
す。

以下では OLED Kit の設定項目を解説します。

### `OLEDKIT_DISABLE` define マクロ

OLED Kitを無効化する設定項目です。各キーマップでOLED Kitを使いたくない場合、す
なわちOLED表示を完全に自身でコントロールしたい場合に設定してください。

各キーマップの config.h で設定できます。

設定例:

```c
#define OLEDKIT_DISABLE
```

### `oledkit_render_info_user()` オーバーライド可能関数

`oledkit_render_info_user()` 関数を定義するとプライマリ側のOLEDに表示する内容を
カスタマイズできます。デフォルトではロゴを表示するようになっています。

各キーマップの keymap.c で定義できます。

設定例は上述してあります。

### `oledkit_render_logo_user()` オーバーライド可能関数

`oledkit_render_logo_user` 関数を定義するとセカンダリ(USBケーブルが接続されてい
ない)側のOLEDに表示する内容をカスタマイズできます。デフォルトではロゴを表示する
ようになっています。ただしキーボードとしての主要な情報はほぼプライマリ側に集約
されているため、アクティブなレイヤーやタイプしたキーなどの情報を表示することは
できません。

各キーマップの keymap.c で定義できます。
