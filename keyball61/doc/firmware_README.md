# Keyball61 firmwares README

## Description in English

This archive includes firmwares for Keyball61.

Included variations of firmware are below:

* `default` - base version for customization
* `test` - used for testing during assembly
* `via` - Recommended version that can use [Remap][remap]

The recommended usage of these firmwares is:

1.  Please use `test` version during assemble the keyboard.
    It is designed to help verifying that the soldering of diodes and switch
    sockets is correct, and easy to check the operation of RGB LED.
2.  After confirming the operation, rewrite it with `via` version.

## 日本語の説明

このアーカイブには Keyball61 のファームウェアが含まれています。

含まれているファームウェアのバリエーションは以下の通りです:

* `default` - カスタマイズの基礎となる版
* `test` - 組立時のテストに用いる版
* `via` - [Remap][remap] で利用できる、推奨版

推奨する使い方は次の通りです:

1.  キーボードを組み立てる際は `test` を使ってください。
    ダイオードやスイッチソケットのハンダ付けが正しいか確認できる他、
    RGB LEDの動作確認が容易になるように構成してあります。
2.  動作確認が取れたあとは `via` に書き換えて利用してください。

## Fixed keymap for `test`

This keymap does not use any layers or QMK function keys to make it easier to test.

```
KC_ESC   KC_1     KC_2     KC_3     KC_4     KC_5                            KC_6     KC_7     KC_8     KC_9     KC_0     KC_MINS
KC_GRV   KC_Q     KC_W     KC_E     KC_R     KC_T                            KC_Y     KC_U     KC_I     KC_O     KC_P     KC_EQL
KC_LCTL  KC_A     KC_S     KC_D     KC_F     KC_G                            KC_H     KC_J     KC_K     KC_L     KC_SCLN  KC_QUOT
KC_LSFT  KC_Z     KC_X     KC_C     KC_V     KC_B     KC_LBRC       KC_RBRC  KC_N     KC_M     KC_COMM  KC_DOT   KC_SLSH  KC_RSFT
KC_LGUI  KC_APP  (KC_HOME  KC_END   KC_LALT) KC_SPC   KC_TAB        KC_BSPC  KC_ENT  (KC_RALT  KC_PGUP  KC_PGDN) KC_BSLS  KC_RGUI
```

The area enclosed in parentheses may be replaced by a trackball.

<https://config.qmk.fm/#/test> is useful for testing keys.

[remap]:https://remap-keys.app/
