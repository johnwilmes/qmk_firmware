// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "johnwilmes.h"

#define LAYER_STATE(layer) ((layer_state_t)1 << layer)
#define DEFAULT_LAYERS LAYER_STATE(_FINGERS) | LAYER_STATE(_BASE)

layer_state_t left_mod_layers = LAYER_STATE(_LEFT_MOD) | LAYER_STATE(_SYMBOLS) | LAYER_STATE(_BRACKETS) | LAYER_STATE(_NUMBERS) | LAYER_STATE(_HEX);
layer_state_t right_mod_layers = LAYER_STATE(_RIGHT_MOD) | LAYER_STATE(_NAVIGATION) | LAYER_STATE(_SYSTEM);

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
#endif
  /*rgb_matrix_disable();*/
  default_layer_set(DEFAULT_LAYERS);
}

/********************
 * FINGER POSITIONS *
 ********************/

#undef KEY_DEF
#define KEY_DEF(name, row_nbr, col_nbr, ...) (keypos_t){.row = row_nbr, .col = col_nbr}

const keypos_t inverse_keymap[] =
{
    FOR_EACH_KEY_DEF(IDENTITY)
};

const keypos_t* get_finger_position(uint16_t finger_keycode) {
    if IS_FINGER(finger_keycode) {
        return &inverse_keymap[FINGER_INDEX(finger_keycode)];
    }
    return NULL;
}

static bool simulate_event(uint16_t finger_keycode, bool pressed) {
    const keypos_t *keypos = get_finger_position(finger_keycode);
    if (NULL == keypos) {
        return false;
    }
    keyrecord_t record = {
        .event =
            {
                .key     = *keypos,
                .time    = timer_read() | 1,
                .type    = KEY_EVENT,
                .pressed = pressed,
            },
    };
    process_record(&record);
    return true;
}


/*********************
 * COMBO DEFINITIONS *
 *********************/

#define COMBO_ENUM(name, ...) CMB_##name,
#define COMBO_DATA(name, key, ...) const uint16_t PROGMEM CMB_DATA_##name[] = {__VA_ARGS__, COMBO_END};
#define COMBO_KEY(name, key, ...) [CMB_##name] = COMBO(CMB_DATA_##name, key),

/* Store combo index enum */

#undef COMBO_DEF
#define COMBO_DEF COMBO_ENUM

enum combos {
    EACH_COMBO_DEF()
};

/* Store combo triggering keys data */
#undef COMBO_DEF
#define COMBO_DEF COMBO_DATA

EACH_COMBO_DEF()

/* Store combo_t array (combo results) */
#undef COMBO_DEF
#define COMBO_DEF COMBO_KEY

combo_t key_combos[] = {
    EACH_COMBO_DEF()
};


/****************
 * PRECOGNITION *
 ****************/

/* Precognition combos reorder the key presses to act as though they were pressed in the order listed in the combo */

 #undef COMBO_DEF
 #define COMBO_DEF(name, ...) \
    case CMB_##name:

bool is_precognition_combo(uint16_t combo_index) {
    switch (combo_index) {
        EACH_PRECOG_DEF()
        return true;
    }
    return false;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (is_precognition_combo(combo_index) && pressed) {
        const uint16_t *keys = key_combos[combo_index].keys;
        for (uint8_t i = 0;; i++) {
            uint16_t key = pgm_read_word(&keys[i]);
            if (key == COMBO_END) {
                break;
            }
            simulate_event(key, true);
        }
    }
}

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    if (is_precognition_combo(combo_index)) {
        simulate_event(keycode, false);
    }
    return false;
}

bool is_combo_contiguous(uint16_t index, combo_t *combo, uint16_t keycode, keyrecord_t *record, uint8_t n_unpressed_keys) {
    if (is_precognition_combo(index)) {
        uint16_t trigger = pgm_read_word(combo->keys);
        /* If we press multiple home row mods simultaneously, we don't interrupt the precognition combo,
        *  so that the earliest keypress will participate in a combo and they will all act as mods */
        switch (trigger) {
            case L_THUMB_H:
                switch (keycode) {
                    case L_PINKY_H:
                    case L_RING_H:
                    case L_MIDDLE_H:
                    case L_INDEX_H:
                        return false;
                    default:
                        return true;
                }
            case R_THUMB_H:
                switch (keycode) {
                    case R_PINKY_H:
                    case R_RING_H:
                    case R_MIDDLE_H:
                    case R_INDEX_H:
                        return false;
                    default:
                        return true;
                }
        }
    }
    return true;
}

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    return is_precognition_combo(index);
}

extern uint8_t _get_combo_length(combo_t *combo);

bool is_combo_preferred(uint16_t combo_index1, uint16_t combo_index2, uint8_t combo_length1) {
    /* Precognition combos have highest priority, and ignore length */
    bool combo1_is_precog = is_precognition_combo(combo_index1);
    bool combo2_is_precog = is_precognition_combo(combo_index2);
    if (combo1_is_precog || combo2_is_precog) {
        if (!combo1_is_precog) {
            return false;
        }
        if (!combo2_is_precog) {
            return true;
        }
        return combo_index1 > combo_index2;
    }
    uint8_t combo_length2 = _get_combo_length(&key_combos[combo_index2]);
    if (combo_length1 > combo_length2) {
        return true;
    }
    return combo_index1 > combo_index2;
}

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    if (is_precognition_combo(combo_index)) {
        return 200;
    }
    return COMBO_TERM;
}

/*****************
 * KEY OVERRIDES *
 *****************/

#define ko_make_modded(_trigger, _replacement, _trigger_mods, _suppressed_mods, _negative_mods) \
    ((const key_override_t){                                                                    \
        .trigger_mods      = (_trigger_mods),                                                   \
        .layers            = ~0,                                                                \
        .suppressed_mods   = (_suppressed_mods),                                                \
        .options           = ko_options_default,                                                \
        .negative_mod_mask = (_negative_mods),                                                  \
        .custom_action     = NULL,                                                              \
        .context           = NULL,                                                              \
        .trigger           = (_trigger),                                                        \
        .replacement       = (_replacement),                                                    \
        .enabled           = NULL,                                                              \
    })

/* Press shift to activate a different shifted thing */
#define ko_shift_to_shift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, MOD_MASK_SHIFT, 0, 0)
/* Press shift to activate an unshifted thing */
#define ko_shift_to_unshift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, MOD_MASK_SHIFT, MOD_MASK_SHIFT, 0)
/* Don't press shift to activate a shifted thing */
#define ko_unshift_to_shift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, 0, 0, MOD_MASK_SHIFT)
/* Don't press shift to activate a different unshifted thing */
#define ko_unshift_to_unshift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, 0, MOD_MASK_SHIFT, MOD_MASK_SHIFT)

/* Shift key for symbols */
const key_override_t colon_ko      = ko_shift_to_shift(MY_DOT, KC_COLON);
const key_override_t semicolon_ko  = ko_shift_to_unshift(MY_COMMA, KC_SEMICOLON);
const key_override_t quote_ko      = ko_shift_to_unshift(MY_QUOTE, KC_QUOTE);
const key_override_t question_ko   = ko_shift_to_unshift(MY_LINE, KC_QUESTION);

const key_override_t paren_ko      = ko_shift_to_shift(MY_PAREN, KC_RIGHT_PAREN);
const key_override_t square_ko     = ko_shift_to_unshift(MY_SQUARE, KC_RIGHT_BRACKET);
const key_override_t curly_ko      = ko_shift_to_shift(MY_CURLY, KC_RIGHT_CURLY_BRACE);
const key_override_t angle_ko      = ko_shift_to_shift(MY_ANGLE, KC_RIGHT_ANGLE_BRACKET);

const key_override_t tick_ko       = ko_shift_to_unshift(MY_TICK, KC_GRAVE);
const key_override_t minus_ko      = ko_shift_to_unshift(MY_SLASH, KC_MINUS);
const key_override_t equal_ko      = ko_shift_to_unshift(MY_EQUAL, KC_EQUAL);
const key_override_t tilde_ko      = ko_shift_to_shift(MY_NOT, KC_TILDE);
const key_override_t hash_ko       = ko_shift_to_shift(MY_PERCENT, KC_HASH);
const key_override_t plus_ko       = ko_shift_to_shift(MY_ASTERISK, KC_PLUS);
const key_override_t circumflex_ko = ko_shift_to_shift(MY_REGEX, KC_CIRCUMFLEX);
const key_override_t pipe_ko       = ko_shift_to_shift(MY_BOOL, KC_PIPE);
const key_override_t backslash_ko  = ko_shift_to_unshift(MY_BACKSLASH, KC_BACKSLASH);

const key_override_t *key_overrides[] = {
    &colon_ko,
    &semicolon_ko,
    &quote_ko,
    &question_ko,

    &paren_ko,
    &square_ko,
    &curly_ko,
    &angle_ko,

    &tick_ko,
    &minus_ko,
    &equal_ko,
    &tilde_ko,
    &hash_ko,
    &plus_ko,
    &circumflex_ko,
    &pipe_ko,
    &backslash_ko
};


/**************
 * RGB MATRIX *
 **************/

#define RGB_MATRIX_FAST_STEP 8
uint8_t qadd8(uint8_t a, uint8_t b) {
    unsigned int x = a + b;
    if (x > 255)
        x = 255;
    return x;
}
uint8_t qsub8(uint8_t a, uint8_t b) {
    int x = a - b;
    if (x < 0)
        x = 0;
    return x;
}

uint8_t get_mods_as_left(void) {
    return (get_mods() | (get_mods() >> 4)) & ((1 << 4)-1);
}

 void process_rgb_step(bool up) {
    uint8_t mods = get_mods();
    if (mods & MOD_MASK_GUI) {
        if (up) {
            rgb_matrix_step_noeeprom();
        } else {
            rgb_matrix_step_reverse_noeeprom();
        }
        return;
    }

    bool fast = mods & MOD_MASK_SHIFT;
    hsv_t hsv = rgb_matrix_get_hsv();
    hsv_t diff = {};

    if (!(mods & (MOD_MASK_CTRL | MOD_MASK_ALT))) {
        diff.v = fast ? RGB_MATRIX_FAST_STEP : 1;
    }
    if (mods & MOD_MASK_CTRL) {
        diff.h = fast ? RGB_MATRIX_FAST_STEP : 1;
    }
    if (mods & MOD_MASK_ALT) {
        diff.s = fast ? RGB_MATRIX_FAST_STEP : 1;
    }

    if (up) {
        rgb_matrix_sethsv_noeeprom(
            hsv.h + diff.h, /* hue intentionally overflows */
            qadd8(hsv.s, diff.s),
            qadd8(hsv.v, diff.v)
        );
    } else {
        rgb_matrix_sethsv_noeeprom(
            hsv.h - diff.h, /* hue intentionally overflows */
            qsub8(hsv.s, diff.s),
            qsub8(hsv.v, diff.v)
        );
    }
 }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uprintf("KL: kc: %s, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", get_keycode_string(keycode), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    if (record->event.pressed) {
        switch (keycode) {
            case MY_RGB_T:
                rgb_matrix_toggle_noeeprom();
                break;
            case MY_RGB_D:
                process_rgb_step(false);
                break;
            case MY_RGB_U:
                process_rgb_step(true);
                break;
            case EEPROM_FLUSH:
                eeconfig_force_flush_rgb_matrix();
                break;
        }
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    uprintf("KL: encoder %u %s\n", index, clockwise ? "clockwise" : "counter-clockwise");
    if (clockwise) {
        simulate_event(ENC_CW, true);
        simulate_event(ENC_CW, false);
    } else {
        simulate_event(ENC_CCW, true);
        simulate_event(ENC_CCW, false);
    }
    return false;
}


/**********
 * LAYERS *
 **********/


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Fingers layer
 *
 *                                                  ,--------------------.
 * ,-------------------------------------------.    | _CCW |ENC_B |  _CW |    ,-------------------------------------------.
 * |   _OU  |  _U  |  _U  |  _U  |  _U  |  _OU |    `--------------------'    |  _OU |  _U  |  _U  |  _U  |  _U  |  _OU   |
 * |--------+------+------+------+------+------|------.                ,------|------+------+------+------+------+--------|
 * |   _O   |L_PINK|L_RING|L_MID |L_INDX|  _O  |L_ENC |                |R_ENC |  _O  |R_INDX|R_MID |R_RING|R_PINK|  _O    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   _OD  |  _D  |  _D  |  _D  |  _D  |  _OD |  _U  |  _OU |  |  _OU |  _U  |  _OD |  _D  |  _D  |  _D  |  _D  |  _OD   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  _I3 |  _I2 |  _I1 |L_THUM|  _O  |  |  _O  |R_THUM|  _I1 |  _I2 |  _I3 |
 *                        `----------------------------------'  `----------------------------------'
 *
 */
#undef KEY_DEF
#define KEY_DEF(key, ...) key
    [_FINGERS] = FOR_EACH_KEY_DEF(MY_LAYOUT),

/* Base Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  Z   |  F   |  M   |  P   |  V   |                              |  Q   | ,  ; | .  : | "  ' |  J   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  R   |  S   |  N   |  T   |  G   |                              | _  ? |  A   |  E   |  I   |  H   |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  W   |  C   |  L   |  D   |  B   |      |      |  |      |      |  X   |  O   |  U   |  Y   |  K   |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      | MOD  | SPC  | SYM  |      |  |      |  NAV | BSPC | MOD  |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_BASE] = MY_LAYOUT(
       _______, KC_Z, KC_F, KC_M  , KC_P    ,  KC_V         ,    MY_VOLD , MY_MUTE, MY_VOLU,                 KC_Q    , MY_COMMA, MY_DOT , MY_QUOTE, KC_J, _______,
       _______, KC_R, KC_S, KC_N  , KC_T    ,  KC_G         ,                                                MY_LINE , KC_A    , KC_E   , KC_I    , KC_H, _______,
       _______, KC_W, KC_C, KC_L  , KC_D    ,  KC_B         , _______ , _______,   _______, _______ , KC_X    , KC_O    , KC_U   , KC_Y    , KC_K, _______,
                           _______, MO_LMOD,  KC_SPC , MO_SYM, _______,   _______, MO_NAV, KC_BSPC, MO_RMOD , _______
    ),

/*
 * Left Mod Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LEFT_MOD] = MY_LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX , XXXXXXX     ,      _______, _______, _______,      _______, _______, _______, _______, _______, _______,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,   XXXXXXX,                                           _______, _______, _______, _______, _______, _______,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX     , _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______     , _______, _______,    _______, XXXXXXX, _______, XXXXXXX, _______
    ),


/*
 * Right Mod Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RIGHT_MOD] = MY_LAYOUT(
      _______, _______, _______, _______, _______, _______,       _______, _______, _______,       XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, _______, _______, _______, _______, _______,                                        XXXXXXX, KC_RSFT, KC_RCTL, MY_RALT, KC_RGUI, XXXXXXX,
      _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, XXXXXXX, _______, XXXXXXX, _______,    _______, _______, _______ , _______, _______
    ),

/* Symbol Layers
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              | @@   | ,;   | .:   | "'   | ``   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              | _?   | /- ()| == []| !~ {}| <> <>|      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      | %#   | *+   | $^   | &|   | \\   |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = MY_LAYOUT(
     XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX , XXXXXXX,       MY_RGB_D, MY_RGB_T, MY_RGB_U,       MY_AT     , _______    , _______ , _______, MY_TICK     , _______,
     XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,   XXXXXXX,                                        _______   , MY_SLASH   , MY_EQUAL, MY_NOT , MY_ANGLE    , _______,
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , MO_NUM, XXXXXXX,_______,_______,     _______,_______, MY_PERCENT, MY_ASTERISK, MY_REGEX, MY_BOOL, MY_BACKSLASH, _______,
                             _______,_______,_______,_______,_______,     _______,XXXXXXX, MO_BRKT   , XXXXXXX    , _______
    ),


    [_BRACKETS] = MY_LAYOUT(
     _______,_______,_______,_______,_______,_______,       _______, _______, _______,       _______, _______ , _______  , _______ , _______ , _______,
     _______,_______,_______,_______,_______,_______,                                       _______, MY_PAREN, MY_SQUARE, MY_CURLY, MY_ANGLE, _______,
     _______,_______,_______,_______,_______,_______,_______,_______,     _______,_______,_______, _______ , _______  , _______ , _______ , _______,
                             _______,_______,_______,_______,_______,     _______,_______,_______, _______, _______
    ),

/* Number Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      |  4   |  5   |  6   |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              |  E   |  0 A |  1 B |  2 C |  3   |      |
 * |------+------+------+------+------+------+------+------.  ,------+------|------+------+------+------+------+------+
 * |      |      |      |      |      |      |      |      |  |      |      |  X   |  7 D |  8 E |  9 F |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NUMBERS] = MY_LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX , XXXXXXX,       _______, _______, _______,        _______, KC_4  , KC_5  , KC_6, _______, _______,
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,   XXXXXXX,                                        KC_E  , KC_0  , KC_1  , KC_2, KC_3   , _______,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX,_______,_______,    _______,_______, KC_X  , KC_7  , KC_8  , KC_9, _______, _______,
                               _______,_______,_______,_______,_______,    _______,XXXXXXX,MO_HEX,XXXXXXX,_______
    ),
    [_HEX] = MY_LAYOUT(
       _______,_______,_______,_______,_______,_______,       _______,_______,_______,         _______,_______,_______,_______,_______,_______,
       _______,_______,_______,_______,_______,_______,                                        KC_E   , KC_A  , KC_B  , KC_C  ,_______,_______,
       _______,_______,_______,_______,_______,_______,_______,_______,    _______,_______,_______, KC_D  , KC_E  , KC_F  ,_______,_______,
                               _______,_______,_______,_______,_______,    _______,_______,_______,_______,_______
    ),
/* Nav Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  F5  | PGUP |  UP  | PGDN |  F2  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  F4  | LEFT | DOWN | RIGHT|  F1  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  F6  | HOME |  F7  | END  |  F3  |      |      |  |      |      |      |      |      |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NAVIGATION] = MY_LAYOUT(
     _______, KC_F5, KC_PAGE_UP, KC_UP  , KC_PAGE_DOWN, KC_F2  ,      _______,_______,_______,       _______,_______,_______,_______,_______,_______,
     _______, KC_F4, KC_LEFT   , KC_DOWN, KC_RIGHT    , KC_F1  ,                                     _______,_______,_______,_______,_______,_______,
     _______, KC_F6, KC_HOME   , KC_F7  , KC_END      , KC_F3  ,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                 _______, XXXXXXX     , MO_SYS,XXXXXXX,_______,     _______,_______,_______,_______,_______
    ),

/* System (Nav) Layer(s)
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |S_HOME|SYS_UP| S_END|      |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |S_EXIT|S_LEFT|S_DOWN|SRIGHT|S_OPEN|                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |      |S_PGUP| S_ALT|S_PGDN|      |      |      |  |      |      |      |      |      |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYSTEM] = MY_LAYOUT(
     _______, XXXXXXX    , NOTIFICATIONS, OVERVIEW_UP  , MESSAGES  , XXXXXXX,      _______,_______,_______,       _______,_______,_______,_______,_______,_______,
     _______, LOCK_SCREEN, MAXIMIZE     , OVERVIEW_DOWN, FULLSCREEN, SYS_RUN,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX    , MEDIA_PREV   , MEDIA_PLAY   , MEDIA_NEXT, XXXXXXX,_______,_______,   _______,_______,_______,_______,_______,_______,_______,_______,
                                        _______      , _______   , _______,_______,_______,     _______,_______,_______,_______,_______
     ),


// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|------.                ,------|------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |                |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,     _______, _______, _______,      _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
// clang-format on
