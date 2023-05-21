# MCU name
MCU_FAMILY = NRF52
MCU_SERIES = NRF52840
MCU_LDSCRIPT = nrf52840_ao
MCU = cortex-m4

# Bootloader selection
BOOTLOADER = caterina

# Link Time Optimization required for size.
LTO_ENABLE = yes

# Build Options
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug. Should be enabled for BLE Micro Pro
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
MOUSE_SHARED_EP = no        # Should be disabled for BLE Micro Pro
COMBO_ENABLE = yes          # Should be enabled for BLE Micro Pro

# Keyball61 is duplex matrix, uses custom matrix.
CUSTOM_MATRIX = yes # for BLE Micro Pro
SRC += matrix.c

# Keyball61 is split keyboard.
SPLIT_KEYBOARD = yes

# Optical sensor driver for trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
SRC += drivers/pmw3360/pmw3360.c
# QUANTUM_LIB_SRC += spi_master.c # Optical sensor use SPI to communicate

# This is unnecessary for processing KC_MS_BTN*.
MOUSEKEY_ENABLE = no

# Enabled only one of RGBLIGHT and RGB_MATRIX if necessary.
RGBLIGHT_ENABLE = no        # Enable RGBLIGHT
RGBLIGHT_DRIVER = WS2812
RGB_MATRIX_ENABLE = no      # Enable RGB_MATRIX (not work yet)
RGB_MATRIX_DRIVER = WS2812

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

# To support OLED
OLED_ENABLE = no                # Please Enable this in each keymaps.
SRC += lib/oledkit/oledkit.c    # OLED utility for Keyball series.

# Include common library
SRC += lib/keyball/keyball.c

# Disable other features to squeeze firmware size
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no

# Support bmp keyboard configuration
SRC += lib/bmp/keyboard.c
