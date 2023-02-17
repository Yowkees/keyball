# Keyball39 ファームウェア

[@d_kamiichi](https://twitter.com/d_kamiichi)の開発した Keyball39 のファームウェアです。

トラックボールを動かした際に、自動クリックレイヤーレイヤー(デフォルトでは 7 番目...index6 のレイヤー)が有効になります。

## 主な機能

1. トラックボール検知で自動でクリックレイヤーへ（0.8 秒でレイヤー 0 に戻ります）
2. ↑ の間だけ LED を点灯（RGB_TOG をオンの状態にしてください）
3. スクロールは keyball 純正のものを使用可能

※自動クリックレイヤー部分のコードは takashicompany さんの[こちら](https://zenn.dev/takashicompany/articles/69b87160cda4b9)を参考にさせていただいております。

## ファームウェアの書き込み

QMK のビルド環境がない方は以下の手順で当ファームウェアの書き込んでください。

1. ファイルを[こちら](https://github.com/kamiichi99/keyball/blob/main/builded-firmware/20230217/Scroll_mode_in_layer3_keyball_keyball39_kamidai.hex)からダウンロードする
2. [Pro Micro Web Updater](https://sekigon-gonnoc.github.io/promicro-web-updater/index.html)や[QMK Toolbox](https://kbd.dailycraft.jp/claw44/buildguide/10_firmware/toolbox/)でファームウェアを Pro Micro に書き込む

## Remap でのマウスキーの書き込みについて

当ファームウェアは Remap に対応しております。  
レイヤー数は 7 となります。

| キー           | Code(hex) | 説明                                       |
| :------------- | :-------- | :----------------------------------------- |
| マウスボタン 1 | 0x5DAF    | 主に左クリックが設定されていることが多い。 |
| マウスボタン 2 | 0x5DB0    | 主に右クリックが設定されていることが多い。 |
| マウスボタン 3 | 0x5DB1    | OS や PC の設定に依存。                    |

## その他

- 当ファームウェア、ソースコードを使用したことでの不利益や故障などは責任は負いかねます。
