#include "quantum.h"

#define MAX_LEDS 48

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_RED}
);

const rgblight_segment_t PROGMEM layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_AZURE}
);

const rgblight_segment_t PROGMEM layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_GREEN}
);

const rgblight_segment_t PROGMEM layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, MAX_LEDS, HSV_WHITE}
);

const rgblight_segment_t* const PROGMEM light_layers[] = {
    layer_0,
    capslock_layer,
    layer_1,
    layer_2,
    layer_3
};
