# To support trackball.
POINTING_DEVICE_ENABLE = yes

# To support OLED
OLED_DRIVER_ENABLE = yes

# Use custom/modified transport driver for split to negotiate trackball.
SPLIT_TRANSPORT = custom
SRC += transport.c
# settings extracted from common_features.mk for SPLIT_TRANSPORT.
OPT_DEFS += -DSERIAL_DRIVER_BITBANG
QUANTUM_LIB_SRC += serial.c
