#include "quantum.h"

#define MAX_LEDS 48

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_RED}
);

const rgblight_segment_t PROGMEM default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM operation_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_BLUE}
);

const rgblight_segment_t PROGMEM symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_GOLD}
);

const rgblight_segment_t PROGMEM mouse_layer_vrt[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_GREEN}
);

const rgblight_segment_t PROGMEM mouse_layer_hor[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM mouse_layer_fre[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_PINK}
);

enum layer_lighting_number {
    LAYER_LIGHTING_DEFAULT = 0,
    LAYER_LIGHTING_CAPSLOCK,
    LAYER_LIGHTING_MOUSE_VRT,
    LAYER_LIGHTING_MOUSE_HOR,
    LAYER_LIGHTING_MOUSE_FRE,
    LAYER_LIGHTING_OPERATION,
    LAYER_LIGHTING_SYMBOL
};


const rgblight_segment_t* const PROGMEM light_layers[] = {
    default_layer,
    capslock_layer,
    mouse_layer_vrt,
    mouse_layer_hor,
    mouse_layer_fre,
    operation_layer,
    symbol_layer
};
