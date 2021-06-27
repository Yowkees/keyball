# Keyball のカスタマイズ可能な機能

## キーマップで利用可能な Keyball の機能

### `bool keyball_get_scroll_mode(void)` API

トラックボールの現在のスクロールモードを取得します。

### `void keyball_set_scroll_mode(bool mode)` API

トラックボールのスクロールモードを変更します。

### `void keyball_process_trackball_default()` API

トラックボールイベントのデフォルトハンドラです。1つ目のトラックボールはマウスポ
インタに、2つ目のトラックボールはスクロール量に反映されます。

### `void keyball_process_trackball_user()` オーバーライド可能な関数

トラックボールの移動量方法を独自に定義できます。トラックボールの移動量をOLEDに
表示したい時などに`keyball_process_trackball_default` と合わせて利用できます。

例: `keymaps/test/keymap.c` から抜粋

```c
#ifdef OLED_DRIVER_ENABLE

static trackball_delta_t ball1, ball2;

void keyball_process_trackball_user(
        const trackball_delta_t *primary,
        const trackball_delta_t *secondary) {
    ball1 = *primary;
    ball2 = *secondary;
    keyball_process_trackball_default(primary, secondary);
}

void oledkit_render_info_user(void) {
    static char buf[22] = {0};

    // primary trackball's status
    oled_write_P(PSTR("Ball#1: "), false);
    snprintf(buf, sizeof(buf), "%d, %d", ball1.x, ball1.y);
    oled_write_ln(buf, false);

    // secondary trackball's status
    oled_write_P(PSTR("Ball#2: "), false);
    snprintf(buf, sizeof(buf), "%d, %d", ball2.x, ball2.y);
    oled_write_ln(buf, false);
}

#endif
```

## トラックボールドライバ

Keyballに搭載されているトラックボールのドライバーです。

### `TRACKBALL_MAX_NUMBER` 定数

サポート可能な最大のトラックボール数で現在は `2` です。

### `TRACKBALL_SAMPLE_COUNT`

トラックボールでは光学センサから数回に渡って読み取った平均値をポインティングデ
バイスの移動量として送信しており `TRACKBALL_SAMPLE_COUNT` はその回数を指定する
設定項目です。

各キーマップの config.h で設定できます。デフォルトは `10` で `0` 以下の値を設定
するとコンパイルエラーになります。

設定例:

```c
#define TRACKBALL_SAMPLE_COUNT 100
```

### `TRACKBALL_SCROLL_DIVIDER`

スクロールモードにおいてトラックボールの移動をスクロール量として送る際に
`TRACKBALL_SCROLL_DIVIDER` で割ることで程よいスクロール量に調整しています。

各キーマップの config.h で設定できます。デフォルトは `10` で `0` 以下の値を設定
するとコンパイルエラーになります。

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
