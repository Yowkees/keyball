# Keyball61 / SparkFun RP2040 置換設定変更手順書

<div style="font-size: 14px; color: #555; margin-bottom: 20px;">
作成日: 2026年8月27日 | 対象キーボード: Keyball61 (Rev1) | 対象マイコン: SparkFun Pro Micro - RP2040
</div>

本手順書は、Keyball61の標準コントローラー（Pro Micro / ATmega32U4）を、**SparkFun Pro Micro - RP2040**に置き換えるためのQMK Firmware設定手順です。
A4用紙に印刷して手元で確認しながら作業できるように、ファイル単位で「変更前（Before）」と「変更後（After）」をページごとに整理しています。

---

### ■ 物理ピン・GPIO対応表（印刷用リファレンス）
QMKファームウェア内、またはコンバータ（`sparkfun_rp2040` / `rp2040_ce`）によってマッピングされる、主要なPro MicroピンとRP2040（GPIO）の物理対応表です。

| 機能 / 用途 | 元の Pro Micro ピン (AVR) | SparkFun RP2040 物理ピン名 | QMK指定GPIOピン名 |
| :--- | :--- | :--- | :--- |
| **分割シリアル通信** | `D2` | `RX / RXI` | `GP1` |
| **OLED (SDA)** | `D1` | `SDA` | `GP2` (または GP20) |
| **OLED (SCL)** | `D0` | `SCL` | `GP3` (または GP21) |
| **PMW3360 CSピン** | `B0` | `TX / TXO` | `GP0` |
| **PMW3360 SCK** | `B1` | `D15 (SCLK)` | `GP6` |
| **PMW3360 MOSI** | `B2` | `D16 (MOSI)` | `GP7` |
| **PMW3360 MISO** | `B3` | `D17 (MISO)` | `GP4` |

---
<!-- ページ改行 -->
<div style="page-break-after: always;"></div>

## 【ファイル 1】`rules.mk` の変更
* **役割**: コンパイル時にコントローラーのアーキテクチャをAVRからARM（RP2040）へと変換し、不要なAVR用の設定を無効化します。
* **保存場所**: `qmk_firmware/keyboards/keyball/keyball61/rules.mk`

### 変更前 / 変更後

#### ◀ 変更前 (Before - ATmega32U4用)
```make
# MCU options
MCU = atmega32u4
BOOTLOADER = caterina

# AVR-specific configurations
LTO_ENABLE = yes
BOOTLOADER_SIZE = 512
```

#### ▶ 変更後 (After - SparkFun RP2040用)
```make
# SparkFun RP2040への自動ハードウェアコンバート指定
CONVERT_TO = sparkfun_rp2040

# AVR用の容量削減オプションやブートローダサイズ指定は不要なためコメントアウト（または削除）
# LTO_ENABLE = yes
# BOOTLOADER_SIZE = 512

# RP2040(ARM)移行時に必要なChibiOS用の設定追加
# keyballの分割通信用シリアルドライバ
SERIAL_DRIVER = vendor
```

---
<!-- ページ改行 -->
<div style="page-break-after: always;"></div>

## 【ファイル 2】`config.h` の変更
* **役割**: 分割通信用ピン、ブート検知、およびトラックボールセンサー（PMW3360）用SPIピンをRP2040のGPIO仕様に合わせて再定義します。
* **保存場所**: `qmk_firmware/keyboards/keyball/keyball61/config.h` (または `keymaps/` 配下の個別フォルダ内)

### 変更前 / 変更後

#### ◀ 変更前 (Before - ATmega32U4用)
```c
#pragma once

// 分割通信ピン（AVR物理ピン）
#define SOFT_SERIAL_PIN D2

// トラックボール(PMW3360)用のSPI CSピン指定（AVR物理ピン）
#define PMW3360_CS_PIN B0
```

#### ▶ 変更後 (After - SparkFun RP2040用)
```c
#pragma once

// 1. RP2040のシリアルピン配置に変更（Pro Micro D2に対応するGP1を割り当て）
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP1

// 2. 分割キーボードのブート側自動検出（RP2040必須設定）
#define SPLIT_USB_DETECT

// 3. トラックボール(PMW3360)用CSピン（Pro Micro B0に対応するGP0を割り当て）
#undef PMW3360_CS_PIN
#define PMW3360_CS_PIN GP0

// 4. SparkFun RP2040の標準SPIピン定義（トラックボール通信を安定させるためのピンロック）
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP6
#define SPI_MOSI_PIN GP7
#define SPI_MISO_PIN GP4
```

---
<!-- page-break -->
<div style="page-break-after: always;"></div>

## 【新規ファイル 3】`halconf.h` の新規作成
* **役割**: ChibiOS（RP2040を動かすシステム）に対し、I2CやSPI、SERIALなどのハードウェアドライバを有効化する設定です。
* **保存場所**: `qmk_firmware/keyboards/keyball/keyball61/halconf.h` に**新規にファイルを作成**して保存します。

### 新規ファイル記述内容

#### ▶ 記述内容 (After - 新規作成)
```c
#pragma once

// OLED（液晶）、トラックボール、左右通信用の各周辺機能を有効化します
#define HAL_USE_I2C TRUE
#define HAL_USE_SPI TRUE
#define HAL_USE_SERIAL TRUE

#include_next <halconf.h>
```

---
<!-- ページ改行 -->
<div style="page-break-after: always;"></div>

## 【新規ファイル 4】`mcuconf.h` の新規作成
* **役割**: `halconf.h` で有効化した各種ドライバ（SPI, I2C等）が、RP2040の内部ペリフェラル（I2C0, SPI0等）のどれを使用するかを具体的に指定します。
* **保存場所**: `qmk_firmware/keyboards/keyball/keyball61/mcuconf.h` に**新規にファイルを作成**して保存します。

### 新規ファイル記述内容

#### ▶ 記述内容 (After - 新規作成)
```c
#pragma once

// ChibiOSの設定をオーバーライド
#include_next <mcuconf.h>

// 1. OLED表示用：I2C 0番バスを使用可能に設定
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

// 2. トラックボール用：SPI 0番バスを使用可能に設定
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE

// 3. 分割シリアル通信用：UART 0番（PIO/UART）を使用可能に設定
#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0 TRUE
```

---
<!-- ページ改行 -->
<div style="page-break-after: always;"></div>

## 【手順 5】コンパイル ＆ ファームウェア書き込み

QMKファームウェアの変更完了後、ビルドを行ってSparkFun RP2040へと書き込みます。

### 1. コンパイルコマンドの実行
QMK CLI環境（QMK MSYS等）で以下のコマンドを実行してビルドを行います。
```bash
qmk compile -kb keyball/keyball61 -km default
```
* **ポイント**: 成功すると、`.hex`（AVR用）ではなく、`.uf2`（RP2040用）という拡張子のファームウェアが生成されます。
* 出力先例: `qmk_firmware/.build/keyball_keyball61_default_sparkfun_rp2040.uf2`

### 2. ファームウェアの書き込み（フラッシュ）
1. 左右のKeyball61を繋ぐTRRSケーブルは**絶対に抜いた状態**にしてください。
2. PCにUSBケーブルで左手側、または右手側のSparkFun RP2040を接続します。
3. SparkFun RP2040ボード上の**「BOOTボタン」を押しながら「RST(リセット)ボタン」をカチッと押し、その後BOOTボタンを離します。**
4. パソコンに **`RPI-RP2`** という名前のUSB外付けドライブ（ストレージ）がマウントされます。
5. 生成された `.uf2` ファイルを、この `RPI-RP2` ドライブのルートにそのままドラッグ＆ドロップ（コピー）します。
6. コピーが完了すると自動的にドライブがアンマウントされ、キーボードが再起動して動作可能になります。
7. **もう片方の手側**も同様にPCへ単体接続し、同じ `.uf2` ファイルを書き込みます。
8. 両方の書き込みが完了したら、一度USBを抜き、TRRSケーブルで左右を接続した上で、片方のUSBからPCに接続して動作テストを行ってください。
