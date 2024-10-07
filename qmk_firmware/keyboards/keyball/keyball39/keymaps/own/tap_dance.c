#include "quantum.h"
#include "layer.h"
#include "tap_dance.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// set LANG1 and enable auto shift
static td_tap_t lang2_ctl_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void lang2_ctl_finished (tap_dance_state_t *state, void *user_data) {
    lang2_ctl_state.state = cur_dance(state);
    switch (lang2_ctl_state.state) {
        case TD_SINGLE_TAP:
            autoshift_enable();
            register_code(KC_LNG2);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LCTL);
            break;
        default: break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void lang2_ctl_reset (tap_dance_state_t *state, void *user_data) {
    switch (lang2_ctl_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_LNG2);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LCTL);
            break;
        default:
            break;
    }
    lang2_ctl_state.state = TD_NONE;
}

// set LANG2 and disable auto shift
static td_tap_t lang1_mouse_layer_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void lang1_mouse_layer_finished (tap_dance_state_t *state, void *user_data) {
    lang1_mouse_layer_state.state = cur_dance(state);
    switch (lang1_mouse_layer_state.state) {
        case TD_SINGLE_TAP:
            autoshift_disable();
            register_code(KC_LNG1);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_MOUSE_LAYER);
            break;
        default: break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void lang1_mouse_layer_reset (tap_dance_state_t *state, void *user_data) {
    switch (lang1_mouse_layer_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_LNG1);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_MOUSE_LAYER);
            break;
        default:
            break;
    }
    lang1_mouse_layer_state.state = TD_NONE;
}

static td_tap_t cw_alt_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void cw_alt_finished (tap_dance_state_t *state, void *user_data) {
    cw_alt_state.state = cur_dance(state);
    switch (cw_alt_state.state) {
        case TD_SINGLE_TAP:
            caps_word_on();
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        default: break;
    }
}

void cw_alt_reset (tap_dance_state_t *state, void *user_data) {
    switch (cw_alt_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
        default:
            break;
    }
    cw_alt_state.state = TD_NONE;
}
