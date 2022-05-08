# KeyballONE47

![KeyballONE47]()

A split keyboard with 47 vertically staggered keys and 34mm track ball.

* Keyboard Maintainer: [@Yowkees](https://twitter.com/Yowkees)
* Hardware Supported: KeyballONE47 PCB, ProMicro
* Hardware Availability:
  * <https://shirogane-lab.com/>

Make example for this keyboard (after setting up your build environment):

    make keyball/one47:test

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Special keycodes

Value    | Keycode    |Description
---------|------------|------------------------------------------------------------------
`0x5DA5` | `KBC_RST`  |Reset Keyball configuration
`0x5DA6` | `KBC_SAVE` |Persist Keyball configuration to EEPROM
`0x5DA7` | `CPI_I100` |Increase 100 CPI (max 12000)
`0x5DA8` | `CPI_D100` |Decrease 100 CPI (min 100)
`0x5DA9` | `CPI_I1K`  |Increase 1000 CPI (max 12000)
`0x5DAA` | `CPI_D1K`  |Decrease 1000 CPI (min 100)
`0x5DAB` | `SCRL_TO`  |Toggle scroll mode
`0x5DAC` | `SCRL_MO`  |Enable scroll mode when pressing
`0x5DAD` | `SCRL_DVI` |Increase scroll divider (max 7 = 1/128)
`0x5DAE` | `SCRL_DVD` |Decrease scroll divider (min 0 = 1/1)

*NOTE*: The values are for VIA/Remap
