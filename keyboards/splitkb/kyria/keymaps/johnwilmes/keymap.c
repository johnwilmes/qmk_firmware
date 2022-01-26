/* Copyright 2022 John Wilmes <jw@johnwilmes.name>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "johnwilmes.h"

/*
void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
}
*/

/**********
 * COMBOS *
 **********/

enum my_combos {
    COMBO_BACKSPACE,
    COMBO_DELETE,
    COMBO_ESCAPE,

    COMBO_ENTER,
    COMBO_TAB,
    COMBO_MAGIC,

    // Left hand mod-layer combos
    COMBO_LSHIFT,
    COMBO_LCTRL,
    COMBO_LALT,
    COMBO_LGUI,
    COMBO_SYM_SHIFT,
    COMBO_BRACKETS,
    COMBO_NUMBERS,
    COMBO_HEX,
    // Right hand mod-layer combos
    COMBO_RSHIFT,
    COMBO_RCTRL,
    COMBO_RALT,
    COMBO_RGUI,
    COMBO_NAV_SHIFT,
    COMBO_NAV_CTRL,
    COMBO_NAV_ALT,
    COMBO_NAV_GUI,
    COMBO_SYS_SHIFT,
    COMBO_SYS_CTRL,
    COMBO_SYS_ALT,
    COMBO_SYS_GUI,

    COMBO_LENGTH,
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_backspace[] = {R_INDEX_D, R_MIDDLE_D, COMBO_END};
const uint16_t PROGMEM combo_delete[]    = {R_MIDDLE_D, R_RING_D, COMBO_END};
const uint16_t PROGMEM combo_escape[]    = {R_INDEX_D, R_MIDDLE_D, R_RING_D, COMBO_END};
const uint16_t PROGMEM combo_enter[]     = {L_INDEX_D, L_MIDDLE_D, COMBO_END};
const uint16_t PROGMEM combo_tab[]       = {L_MIDDLE_D, L_RING_D, COMBO_END};
const uint16_t PROGMEM combo_magic[]     = {L_INDEX_D, L_MIDDLE_D, L_RING_D, COMBO_END};

const uint16_t PROGMEM combo_lshift[]    = {L_THUMB_I1, L_INDEX, COMBO_END};
const uint16_t PROGMEM combo_lctrl[]     = {L_THUMB_I1, L_MIDDLE, COMBO_END};
const uint16_t PROGMEM combo_lalt[]      = {L_THUMB_I1, L_RING, COMBO_END};
const uint16_t PROGMEM combo_lgui[]      = {L_THUMB_I1, L_PINKY, COMBO_END};
const uint16_t PROGMEM combo_sym_shift[] = {L_THUMB, L_INDEX, COMBO_END};
const uint16_t PROGMEM combo_brackets[]  = {L_THUMB, L_MIDDLE, COMBO_END};
const uint16_t PROGMEM combo_numbers[]   = {L_THUMB, L_RING, COMBO_END};
const uint16_t PROGMEM combo_hex[]       = {L_THUMB, L_PINKY, COMBO_END};
const uint16_t PROGMEM combo_rshift[]    = {R_THUMB_I1, R_INDEX, COMBO_END};
const uint16_t PROGMEM combo_rctrl[]     = {R_THUMB_I1, R_MIDDLE, COMBO_END};
const uint16_t PROGMEM combo_ralt[]      = {R_THUMB_I1, R_RING, COMBO_END};
const uint16_t PROGMEM combo_rgui[]      = {R_THUMB_I1, R_PINKY, COMBO_END};
const uint16_t PROGMEM combo_nav_shift[] = {R_THUMB, R_INDEX, COMBO_END};
const uint16_t PROGMEM combo_nav_ctrl[]  = {R_THUMB, R_MIDDLE, COMBO_END};
const uint16_t PROGMEM combo_nav_alt[]   = {R_THUMB, R_RING, COMBO_END};
const uint16_t PROGMEM combo_nav_gui[]   = {R_THUMB, R_PINKY, COMBO_END};
const uint16_t PROGMEM combo_sys_shift[] = {R_THUMB_O, R_INDEX, COMBO_END};
const uint16_t PROGMEM combo_sys_ctrl[]  = {R_THUMB_O, R_MIDDLE, COMBO_END};
const uint16_t PROGMEM combo_sys_alt[]   = {R_THUMB_O, R_RING, COMBO_END};
const uint16_t PROGMEM combo_sys_gui[]   = {R_THUMB_O, R_PINKY, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [COMBO_BACKSPACE] = COMBO(combo_backspace, KC_BSPC),
    [COMBO_DELETE] = COMBO(combo_delete, KC_DEL),
    [COMBO_ESCAPE] = COMBO(combo_escape, KC_ESC),

    [COMBO_ENTER] = COMBO(combo_enter, KC_ENTER),
    [COMBO_TAB] = COMBO(combo_tab, KC_TAB),
    [COMBO_MAGIC] = COMBO(combo_magic, MY_MAGIC),

    [COMBO_LSHIFT] = COMBO_ACTION(combo_lshift),
    [COMBO_LCTRL] = COMBO_ACTION(combo_lctrl),
    [COMBO_LALT] = COMBO_ACTION(combo_lalt),
    [COMBO_LGUI] = COMBO_ACTION(combo_lgui),
    [COMBO_SYM_SHIFT] = COMBO_ACTION(combo_sym_shift),
    [COMBO_BRACKETS] = COMBO_ACTION(combo_brackets),
    [COMBO_NUMBERS] = COMBO_ACTION(combo_numbers),
    [COMBO_HEX] = COMBO_ACTION(combo_hex),

    [COMBO_RSHIFT] = COMBO_ACTION(combo_rshift),
    [COMBO_RCTRL] = COMBO_ACTION(combo_rctrl),
    [COMBO_RALT] = COMBO_ACTION(combo_ralt),
    [COMBO_RGUI] = COMBO_ACTION(combo_rgui),
    [COMBO_NAV_SHIFT] = COMBO_ACTION(combo_nav_shift),
    [COMBO_NAV_CTRL] = COMBO_ACTION(combo_nav_ctrl),
    [COMBO_NAV_ALT] = COMBO_ACTION(combo_nav_alt),
    [COMBO_NAV_GUI] = COMBO_ACTION(combo_nav_gui),
    [COMBO_SYS_SHIFT] = COMBO_ACTION(combo_sys_shift),
    [COMBO_SYS_CTRL] = COMBO_ACTION(combo_sys_ctrl),
    [COMBO_SYS_ALT] = COMBO_ACTION(combo_sys_alt),
    [COMBO_SYS_GUI] = COMBO_ACTION(combo_sys_gui),

};
// clang-format on

static uint8_t _get_combo_mod(uint16_t combo_index) {
    switch (combo_index) {
        case COMBO_LSHIFT:
        case COMBO_SYM_SHIFT:
            return MOD_BIT(KC_LSFT);
        case COMBO_LCTRL:
            return MOD_BIT(KC_LCTL);
        case COMBO_LALT:
            return MOD_BIT(KC_LALT);
        case COMBO_LGUI:
            return MOD_BIT(KC_LGUI);

        case COMBO_RSHIFT:
        case COMBO_SYS_SHIFT:
        case COMBO_NAV_SHIFT:
            return MOD_BIT(KC_RSFT);
        case COMBO_RCTRL:
        case COMBO_SYS_CTRL:
        case COMBO_NAV_CTRL:
            return MOD_BIT(KC_RCTL);
        case COMBO_RALT:
        case COMBO_SYS_ALT:
        case COMBO_NAV_ALT:
            return MOD_BIT(MY_RALT);
        case COMBO_RGUI:
        case COMBO_SYS_GUI:
        case COMBO_NAV_GUI:
            return MOD_BIT(KC_RGUI);
    }
    return 0;
}

static uint8_t _get_combo_base_layer(uint16_t combo_index) {
    switch (combo_index) {
        case COMBO_LSHIFT:
        case COMBO_LCTRL:
        case COMBO_LALT:
        case COMBO_LGUI:
            return _LEFT_MOD;
        case COMBO_SYM_SHIFT:
        case COMBO_BRACKETS:
        case COMBO_NUMBERS:
        case COMBO_HEX:
            return _SYMBOLS;
        case COMBO_RSHIFT:
        case COMBO_RCTRL:
        case COMBO_RALT:
        case COMBO_RGUI:
            return _RIGHT_MOD;
        case COMBO_NAV_SHIFT:
        case COMBO_NAV_CTRL:
        case COMBO_NAV_ALT:
        case COMBO_NAV_GUI:
            return _NAVIGATION;
        case COMBO_SYS_SHIFT:
        case COMBO_SYS_CTRL:
        case COMBO_SYS_ALT:
        case COMBO_SYS_GUI:
            return _SYSTEM;
    }
    return 0;
}

static uint8_t _get_combo_transient_layer(uint16_t combo_index) {
    switch (combo_index) {
        case COMBO_BRACKETS:
            return _BRACKETS;
        case COMBO_NUMBERS:
            return _NUMBERS;
        case COMBO_HEX:
            return _HEX;
    }
    return 0;
}

static keypos_t _get_combo_key(uint16_t combo_index) {
    switch (combo_index) {
        case COMBO_LSHIFT:
        case COMBO_SYM_SHIFT:
            return (keypos_t){.row=1, .col=3};
        case COMBO_LCTRL:
        case COMBO_BRACKETS:
            return (keypos_t){.row=1, .col=4};
        case COMBO_LALT:
        case COMBO_NUMBERS:
            return (keypos_t){.row=1, .col=5};
        case COMBO_LGUI:
        case COMBO_HEX:
            return (keypos_t){.row=1, .col=6};

        case COMBO_RSHIFT:
        case COMBO_SYS_SHIFT:
        case COMBO_NAV_SHIFT:
            return (keypos_t){.row=5, .col=3};
        case COMBO_RCTRL:
        case COMBO_SYS_CTRL:
        case COMBO_NAV_CTRL:
            return (keypos_t){.row=5, .col=4};
        case COMBO_RALT:
        case COMBO_SYS_ALT:
        case COMBO_NAV_ALT:
            return (keypos_t){.row=5, .col=5};
        case COMBO_RGUI:
        case COMBO_SYS_GUI:
        case COMBO_NAV_GUI:
            return (keypos_t){.row=5, .col=6};
    }
    return (keypos_t){};
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    uint8_t base_layer = _get_combo_base_layer(combo_index);
    uint8_t trans_layer = _get_combo_transient_layer(combo_index);
    uint8_t mod   = _get_combo_mod(combo_index);
    if (pressed) {
        if (base_layer) {
            layer_on(base_layer);
        }
        if (mod) {
            register_mods(mod);
        }
        if (trans_layer) {
            layer_on(trans_layer);
        }
    } else {
        if (mod || trans_layer) {
            /* If we released the thumb first, the other finger is still holding a mod or MO(layer)
             * key. */
            keypos_t key = _get_combo_key(combo_index);
            update_source_layers_cache(key, layer_switch_get_layer(key));
        }
        if (base_layer) {
            layer_off(base_layer);
        }
    }
}

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    uint8_t mod;
    uint8_t trans_layer;
    switch (keycode) {
        case L_THUMB_I1:
        case L_THUMB:
        case L_THUMB_O:
        case R_THUMB_I1:
        case R_THUMB:
        case R_THUMB_O:
            /* Thumbs are used for mod-layer combos, and releasing the thumb ends the
             * combo */
            return true;
        default:
            mod = _get_combo_mod(combo_index);
            trans_layer = _get_combo_transient_layer(combo_index);
            if (mod) {
                unregister_mods(mod);
            }
            if (trans_layer) {
                layer_off(trans_layer);
            }
    }
    return false; // don't release early
}

bool get_combo_is_contiguous(uint16_t combo_index, combo_t *combo) {
    if (_get_combo_mod(combo_index) | _get_combo_transient_layer(combo_index)) {
        return false;
    }
    return true;
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
const key_override_t comma_ko      = ko_shift_to_unshift(MY_DOT, KC_COMMA);
const key_override_t quote_ko      = ko_shift_to_unshift(MY_QUOTE, KC_QUOTE);
const key_override_t backslash_ko  = ko_shift_to_unshift(MY_LINE, KC_BACKSLASH);
const key_override_t slash_ko      = ko_shift_to_unshift(MY_DASH, KC_SLASH);
const key_override_t asterisk_ko   = ko_shift_to_shift(MY_PLUS, KC_ASTERISK);
const key_override_t equal_ko      = ko_shift_to_unshift(MY_EQUAL, KC_EQUAL);
const key_override_t tilde_ko      = ko_shift_to_shift(MY_NOT, KC_TILDE);
const key_override_t angle_ko      = ko_shift_to_shift(MY_ANGLE, KC_RIGHT_ANGLE_BRACKET);
const key_override_t grave_ko      = ko_shift_to_unshift(MY_GRAVE, KC_GRAVE);
const key_override_t percent_ko    = ko_shift_to_shift(MY_HASH, KC_PERCENT);
const key_override_t circumflex_ko = ko_shift_to_shift(MY_REGEX, KC_CIRCUMFLEX);
const key_override_t pipe_ko       = ko_shift_to_shift(MY_BOOL, KC_PIPE);
const key_override_t at_ko         = ko_shift_to_shift(MY_QUESTION, KC_AT);

/* Extra bracket overrides */
const key_override_t paren_ko  = ko_shift_to_shift(KC_LPRN, KC_RPRN);
const key_override_t square_ko = ko_shift_to_unshift(KC_LBRC, KC_RBRC);
const key_override_t curly_ko  = ko_shift_to_shift(KC_LCBR, KC_RCBR);

/* Shift key for media */
const key_override_t voldown_ko = ko_shift_to_unshift(MEDIA_LEFT, KC_AUDIO_VOL_DOWN);
const key_override_t mute_ko    = ko_shift_to_unshift(MEDIA, KC_AUDIO_MUTE);
const key_override_t volup_ko   = ko_shift_to_unshift(MEDIA_RIGHT, KC_AUDIO_VOL_UP);


// clang-format off
const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_ko,
    &quote_ko,
    &backslash_ko,
    &slash_ko,
    &asterisk_ko,
    &equal_ko,
    &tilde_ko,
    &angle_ko,
    &grave_ko,
    &percent_ko,
    &circumflex_ko,
    &pipe_ko,
    &at_ko,
    &paren_ko,
    &square_ko,
    &curly_ko,
    &voldown_ko,
    &mute_ko,
    &volup_ko,
    NULL  // Null terminate the array of overrides!
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;  // continue processing as usual
}


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  Z   |  F   |  M   |  P   |  V   |                              |  K   | -  / | _  \ | ;  : |  J   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  R   |  S   |  N   |  T   |  G   |                              | "  ' |  A   |  E   |  I   |  H   |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  W   |  C   |  L   |  D   |  B   | LOCK |      |  |      | LOCK |  X   |  U   |  O   |  Y   |  Q   |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |ENTER |SPACE |ROCKET|  | MAGIC| .  ! | ,  ? |      |      |
 *                      |      |      |  SYM |      |  SYS |  |  NAV |      |  NUM |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
       XXXXXXX, KC_Z, KC_F,  KC_M ,   KC_P  ,    KC_V  ,                                                   KC_K ,  MY_DASH, MY_LINE, KC_SEMICOLON, KC_J, XXXXXXX,
       XXXXXXX, KC_R, KC_S,  KC_N ,   KC_T  ,    KC_G  ,                                                MY_QUOTE,    KC_A ,   KC_E ,     KC_I    , KC_H, XXXXXXX,
       XXXXXXX, KC_W, KC_C,  KC_L ,   KC_D  ,    KC_B  , LAYER_LOCK,  XXXXXXX,      XXXXXXX, LAYER_LOCK,   KC_X ,    KC_U ,   KC_O ,     KC_Y    , KC_Q, XXXXXXX,
                           XXXXXXX, MO_MOUSE, KC_SPACE ,   MO_SYM  , L_LEADER,     R_LEADER,   MO_NAV  ,  MY_DOT,   MO_SYS, XXXXXXX
    ),

/* Symbol Layers
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      |  -/  |  _\  |  ;:  |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              |  "'  |  +*( |  ==[ |  !~{ |  <>< |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |  ``  |  #%) |  $^] |  &|} |  ?@> |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
     _______,_______,_______,_______,_______,_______,                                       _______, _______,  _______, _______,   _______  , _______,
     _______, MO_HEX, MO_NUM,MO_BRKT,KC_LSFT,_______,                                       _______, MY_PLUS, MY_EQUAL,  MY_NOT,   MY_ANGLE , _______,
     _______,OS_LGUI,OS_LALT,OS_LCTL,OS_LSFT,_______,_______,_______,     _______,_______, MY_GRAVE, MY_HASH, MY_REGEX, MY_BOOL, MY_QUESTION, _______,
                             _______,_______,_______,_______,_______,     _______,_______,  _______, _______,   _______
    ),

    /* Brackets implemented using separate layer rather than key-overrides like the other symbols,
     * because we want to retain ability to modify with CTRL using one-shot mods when needed */
    [_BRACKETS] = LAYOUT(
     _______,_______,_______,_______,_______,_______,                                     _______, _______, _______, _______,  _______, _______,
     _______, MO_HEX, MO_NUM,MO_BRKT,KC_LSFT,_______,                                     _______, KC_LPRN, KC_LBRC, KC_LCBR, MY_ANGLE, _______,
     _______,OS_LGUI,OS_LALT,OS_LCTL,OS_LSFT,_______,_______,_______,     _______,_______,_______, KC_RPRN, KC_RBRC, KC_RCBR,  KC_RABK, _______,
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
    [_NUMBERS] = LAYOUT(
       _______,_______,_______,_______,_______,_______,                                  _______, KC_4, KC_5, KC_6, _______, _______,
       _______, MO_HEX, MO_NUM,MO_BRKT,KC_LSFT,_______,                                     KC_E, KC_0, KC_1, KC_2, KC_3   , _______,
       _______,OS_LGUI,OS_LALT,OS_LCTL,OS_LSFT,_______,_______,_______,    _______,_______, KC_X, KC_7, KC_8, KC_9, _______, _______,
                               _______,_______,_______,_______,_______,    _______,_______,_______,_______,_______
    ),
    [_HEX] = LAYOUT(
       _______,_______,_______,_______,_______,_______,                                    _______,_______,_______,_______,_______,_______,
       _______, MO_HEX, MO_NUM,MO_BRKT,KC_LSFT,_______,                                      KC_E ,  KC_A ,  KC_B ,  KC_C ,_______,_______,
       _______,OS_LGUI,OS_LALT,OS_LCTL,OS_LSFT,_______,_______,_______,    _______,_______,_______,  KC_D ,  KC_E ,  KC_F ,_______,_______,
                               _______,_______,_______,_______,_______,    _______,_______,_______,_______,_______
    ),
/* Nav Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  F5  | HOME |  UP  | END  |  F1  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  F6  | LEFT | DOWN |RIGHT |  F2  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  F7  | PGUP |  F4  | PGDN |  F3  |      |      |  |      |      |      |      |      |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NAVIGATION] = LAYOUT(
     _______, KC_F5,  KC_HOME  ,   KC_UP  ,    KC_END   ,  KC_F1,                                     _______,_______,_______,_______,_______,_______,
     _______, KC_F6,  KC_LEFT  ,  KC_DOWN ,   KC_RIGHT  ,  KC_F2,                                     _______,KC_RSFT,KC_RCTL,MY_RALT,KC_RGUI,_______,
     _______, KC_F7, KC_PAGE_UP,   KC_F4  , KC_PAGE_DOWN,  KC_F3,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                   _______,   _______   ,_______,_______,_______,     _______,_______,_______,_______,_______
    ),

/* System and media layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  F11 |S_HOME|SYS_UP| S_END|  F8  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  F12 |S_LEFT|S_DOWN|SRIGHT|  F9  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  F13 |M_LEFT| MEDIA|MRIGHT|  F10 |      |      |  |      |      |      |      |      |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYSTEM] = LAYOUT(
     _______, KC_F11,  SYS_HOME ,  SYS_UP ,   SYS_END  , KC_F8 ,                                     _______,_______,_______,_______,_______,_______,
     _______, KC_F12,  SYS_LEFT , SYS_DOWN,  SYS_RIGHT , KC_F9 ,                                     _______,KC_RSFT,KC_RCTL,MY_RALT,KC_RGUI,_______,
     _______, KC_F13, MEDIA_LEFT,   MEDIA , MEDIA_RIGHT, KC_F10,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                   _______,   _______  ,_______,_______,_______,     _______,_______,_______,_______,_______
    ),

/*
 * Fingers/Combo layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   _OU  |  _U  |  _U  |  _U  |  _U  |  _OU |                              |  _OU |  _U  |  _U  |  _U  |  _U  |  _OU   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   _O   |L_PINK|L_RING|L_MID |L_INDX|  _O  |                              |  _O  |R_INDX|R_MID |R_RING|R_PINK|  _O    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   _OD  |  _D  |  _D  |  _D  |  _D  |  _OD |  _U  |  _OU |  |  _OU |  _U  |  _OD |  _D  |  _D  |  _D  |  _D  |  _OD   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  _I3 |  _I2 |  _I1 |L_THUM|  _O  |  |  _O  |R_THUM|  _I1 |  _I2 |  _I3 |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    #define FINGERS_MACRO(...) [_FINGERS] = LAYOUT(__VA_ARGS__),
    #include "fingers.def"
    #undef FINGERS_MACRO

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
    [_LEFT_MOD] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                        _______, _______, _______, _______, _______, _______,
      _______, OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
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
    [_RIGHT_MOD] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                        _______, KC_RSFT, KC_RCTL, MY_RALT, KC_RGUI, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
    ),

/*
 * Mouse Layer
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
    [_MOUSE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
