#include "quantum.h"

#define MAX_LEDS 48

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_RED}
);

const rgblight_segment_t PROGMEM default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM operation_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_AZURE}
);

const rgblight_segment_t PROGMEM symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_CORAL}
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

namespace LAYER_LIGHTING{
    enum layer_lighting_number {
        DEFAULT = 0,
        CAPSLOCK,
        MOUSE_VRT,
        MOUSE_HOR,
        MOUSE_FRE
        OPERATION,
        SYMBOL,
    };
}


const rgblight_segment_t* const PROGMEM light_layers[] = {
    default_layer,
    capslock_layer,
    mouse_layer_vrt,
    mouse_layer_hor,
    mouse_layer_fre,
    operation_layer,
    symbol_layer
};
