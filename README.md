# 概要

個人設定用に最適化したリポジトリです。
keyball39,44をmac OSに特化した設定になります。

# 機能

コードの差分は以下から以下から確認出来ます。

<https://github.com/Yowkees/keyball/compare/main...kajiiiro:keyball:main>

公式との機能差分は以下です。

- 必要なファイルのみに変更
- 必要なテスト、ビルド等のみが実行されるように変更
- レイヤーを7つに増加
  - `AUTO_MOUSE_DEFAULT_LAYER` を設定
- スクロールレイヤーの廃止
  - `layer_state_set_user` の削除
- トラックパッドと動作を合わせるためにスクロールを反転
  - `keyball_on_apply_motion_to_mouse_scroll` 関数の `r->h, r->v` に設定する値の符号を反転
- 自動マウスレイヤー切り替えをデフォルトonに設定
  - `pointing_device_init_user` 関数内で `set_auto_mouse_enable` の呼び出し
- その他の微調整
  - スクロール感度
