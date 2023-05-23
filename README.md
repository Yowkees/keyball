# BLE Micro Pro Keyball61

![Keyball61](https://raw.githubusercontent.com/Yowkees/keyball/f24aaa449eee3eb635794630aac0181600e94af0/keyball61/doc/rev1/images/kb61_001.jpg)

A split keyboard with 61 vertically staggered keys and 34mm track ball with [BLE Micro Pro](https://sekigon-gonnoc.github.io/BLE-Micro-Pro/#/).

* Keyboard firmware Maintainer: [@codehex](https://twitter.com/codehex)
* Original Keyboard Maintainer: [@Yowkees](https://twitter.com/Yowkees)
* Hardware Supported: Keyball61 PCB, BLE Micro Pro
* Hardware Availability:
  * <https://shirogane-lab.com/>

### Keyamaps

Keyball61 provides some keymaps as default:

* `test` - Test for building/soldering Keyball61 (w/ right trackball)
* `default` - Template for customized keymap (w/ right trackball)
* `bmp` - Template for customized keymap (w/ right trackball and BLE Micro Pro custom keys)

## How to build firmware

1. Check out this repository.

    ```console
    $ git clone https://github.com/Code-Hex/ble-micro-pro-keyball61.git keyball
    ```

2. Check out [sekigon-gonnoc/qmk_firmware](https://github.com/sekigon-gonnoc/qmk_firmware) repository in another place.

    ```console
    $ git clone https://github.com/sekigon-gonnoc/qmk_firmware.git --depth 1 --recurse-submodules --shallow-submodules -b bmp-0.11.3 qmk
    ```

    Currently BLE Micro Pro Keyball firmwares are verified to compile with bmp-0.11.3

3. Create a symbolic link to this `keyball/` directory from [sekigon-gonnoc/qmk_firmware]'s `keyboards/` directory.

    ```console
    $ ls
    keyball/ qmk/

    $ cd qmk/keyboards
    $ ln -s ../../keyball/qmk_firmware/keyboards/keyball keyball
    $ ls keyball/
    drivers/  keyball61/  lib/  readme.md
    $ cd ..
    ```

4. `make` your Keyball firmwares.

    ```console
    $ make -j8 SKIP_GIT=yes keyball/keyball61:default
    ```

## How to create your keymap

You should make keymap on https://sekigon-gonnoc.github.io/qmk_configurator

Using `./layouts/KEYMAP.JSN` file as a base will likely make configuration easier.

## Special keycodes

Value    | Keycode    |Description
---------|------------|------------------------------------------------------------------
`0x5D62` | `KBC_RST`  |Reset Keyball configuration
`0x5D63` | `KBC_SAVE` |Persist Keyball configuration to EEPROM
`0x5D64` | `CPI_I100` |Increase 100 CPI (max 12000)
`0x5D65` | `CPI_D100` |Decrease 100 CPI (min 100)
`0x5D66` | `CPI_I1K`  |Increase 1000 CPI (max 12000)
`0x5D67` | `CPI_D1K`  |Decrease 1000 CPI (min 100)
`0x5D68` | `SCRL_TO`  |Toggle scroll mode
`0x5D69` | `SCRL_MO`  |Enable scroll mode when pressing
`0x5D6A` | `SCRL_DVI` |Increase scroll divider (max 7 = 1/128)
`0x5D6B` | `SCRL_DVD` |Decrease scroll divider (min 0 = 1/1)

*NOTE*: The values are for Remap
