# Keyball39 ファームウェア

[@d_kamiichi](https://twitter.com/d_kamiichi)の開発した Keyball39 のファームウェアです。

https://user-images.githubusercontent.com/34639637/219548230-d1c8ee17-b649-48c8-97f4-8877bc62a3bd.mp4

<br>

トラックボールを動かすとクリックレイヤーに自動で切り替わり、LED が点灯します（デフォルトでは 7 番目...index6 のレイヤーです）。

## 主な機能

1. トラックボール検知で自動でクリックレイヤーへ（0.8 秒でレイヤー 0 に戻ります）
2. ↑ の間だけ LED を点灯（RGB_TOG をオンの状態にしてください）
3. スクロールは keyball 純正のものを使用可能
4. Remap 対応

※自動クリックレイヤー部分のコードは takashicompany さんの[こちら](https://zenn.dev/takashicompany/articles/69b87160cda4b9)を参考にさせていただいております。

## ファームウェアの書き込み

QMK のビルド環境がない方は以下の手順で当ファームウェアの書き込んでください。

1. ファイルを[こちら](https://github.com/kamiichi99/keyball/blob/main/builded-firmware/20230217/Scroll_mode_in_layer3_keyball_keyball39_kamidai.hex)からダウンロードする
2. [Pro Micro Web Updater](https://sekigon-gonnoc.github.io/promicro-web-updater/index.html)や[QMK Toolbox](https://kbd.dailycraft.jp/claw44/buildguide/10_firmware/toolbox/)でファームウェアを Pro Micro に書き込む

## Remap でのマウスキーの書き込みについて

- 当ファームウェアは [Remap](https://remap-keys.app/configure) に対応しております。
- レイヤー数は 7 となります。
- マウスボタンは以下のものを使用してください。

| キーコード   | Remap 上での表記 | 説明                                       |
| :----------- | :--------------- | :----------------------------------------- |
| `KC_MY_BTN1` | `0x5DAF`         | 主に左クリックが設定されていることが多い。 |
| `KC_MY_BTN2` | `0x5DB0`         | 主に右クリックが設定されていることが多い。 |
| `KC_MY_BTN3` | `0x5DB1`         | OS や PC の設定に依存。                    |

## こちらの Keyball 公式キーも使用可能です

- レイヤー３でスクロールモードになります。（別レイヤーに変えたい場合は keyball_set_scroll_mode の引数を変更してください。）
- USB ケーブルは左右どちらに差しても使用できます。ただしキーマップは USB ケーブルを差した側の ProMicro へ書き込まれるため、初めて差し替えた場合にはキーマップを見直してください。

| キーコード | Remap 上での表記 | 説明                                                             |
| :--------- | :--------------- | :--------------------------------------------------------------- |
| `KBC_RST`  | `0x5DA5`         | Keyball 設定のリセット                                           |
| `KBC_SAVE` | `0x5DA6`         | 現在の Keyball 設定を EEPROM に保存します                        |
| `CPI_I100` | `0x5DA7`         | CPI を 100 増加させます(最大:12000)                              |
| `CPI_D100` | `0x5DA8`         | CPI を 100 減少させます(最小:100)                                |
| `CPI_I1K`  | `0x5DA9`         | CPI を 1000 増加させます(最大:12000)                             |
| `CPI_D1K`  | `0x5DAA`         | CPI を 1000 減少させます(最小:100)                               |
| `SCRL_TO`  | `0x5DAB`         | タップごとにスクロールモードの ON/OFF を切り替えます             |
| `SCRL_MO`  | `0x5DAC`         | キーを押している間、スクロールモードになります                   |
| `SCRL_DVI` | `0x5DAD`         | スクロール除数を１つ上げます(max D7 = 1/128)← 最もスクロール遅い |
| `SCRL_DVD` | `0x5DAE`         | スクロール除数を１つ下げます(min D0 = 1/1)← 最もスクロール速い   |

※

## その他

- 当ファームウェア、ソースコードを使用したことでの不利益や故障などは責任は負いかねます。
- 質問や不具合等のご連絡は[Twitter](https://twitter.com/d_kamiichi)よりお願いします。
