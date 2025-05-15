RGBLIGHT_ENABLE = yes

OLED_ENABLE = yes

VIA_ENABLE = yes

COMBO_ENABLE = yes	# コンボキー有効化 ref:https://note.com/mamelog0103/n/n5a51fcd24f26

# ファーム容量削減 ref:https://zenn.dev/koron/articles/98324ab760e83a
# qmk_firmware\keyboards\keyball\keyball39\rules.mk で有効になっているものもある
LTO_ENABLE = yes	# リンク最適化
