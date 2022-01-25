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
  COMBO_ESCAPE,
  COMBO_LSHIFT,
  COMBO_LCTRL,
  COMBO_LALT,
  COMBO_LGUI,
  COMBO_RSHIFT,
  COMBO_RCTRL,
  COMBO_RALT,
  COMBO_RGUI,
  COMBO_LENGTH
};

const uint16_t PROGMEM combo_backspace[] = {R_INDEX, R_INDEX_O, COMBO_END};
const uint16_t PROGMEM combo_escape[] = {L_INDEX, L_INDEX_O, COMBO_END};
const uint16_t PROGMEM combo_lshift[] = {L_THUMB_I1, L_INDEX, COMBO_END};
const uint16_t PROGMEM combo_lctrl[] = {L_THUMB_I1, L_MIDDLE, COMBO_END};
const uint16_t PROGMEM combo_lalt[] = {L_THUMB_I1, L_RING, COMBO_END};
const uint16_t PROGMEM combo_lgui[] = {L_THUMB_I1, L_PINKY, COMBO_END};
const uint16_t PROGMEM combo_rshift[] = {R_THUMB_I1, R_INDEX, COMBO_END};
const uint16_t PROGMEM combo_rctrl[] = {R_THUMB_I1, R_MIDDLE, COMBO_END};
const uint16_t PROGMEM combo_ralt[] = {R_THUMB_I1, R_RING, COMBO_END};
const uint16_t PROGMEM combo_rgui[] = {R_THUMB_I1, R_PINKY, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BACKSPACE] = COMBO(combo_backspace, KC_BSPC),
  [COMBO_ESCAPE] = COMBO(combo_escape, KC_ESC),
  [COMBO_LSHIFT] = COMBO_ACTION(combo_lshift),
  [COMBO_LCTRL] = COMBO_ACTION(combo_lctrl),
  [COMBO_LALT] = COMBO_ACTION(combo_lalt),
  [COMBO_LGUI] = COMBO_ACTION(combo_lgui),
  [COMBO_RSHIFT] = COMBO_ACTION(combo_rshift),
  [COMBO_RCTRL] = COMBO_ACTION(combo_rctrl),
  [COMBO_RALT] = COMBO_ACTION(combo_ralt),
  [COMBO_RGUI] = COMBO_ACTION(combo_rgui),
};

static uint8_t combo_mod_state = 0;

static uint8_t _get_mod(uint16_t combo_index) {
    switch (combo_index) {
        case COMBO_LSHIFT:
            return MOD_BIT(KC_LSFT);
        case COMBO_LCTRL:
            return MOD_BIT(KC_LCTL);
        case COMBO_LALT:
            return MOD_BIT(KC_LALT);
        case COMBO_LGUI:
            return MOD_BIT(KC_LGUI);
        case COMBO_RSHIFT:
            return MOD_BIT(KC_RSFT);
        case COMBO_RCTRL:
            return MOD_BIT(KC_RCTL);
        case COMBO_RALT:
            return MOD_BIT(MY_RALT);
        case COMBO_RGUI:
            return MOD_BIT(KC_RGUI);
    }
    return 0;
}

#define LEFT_HAND 1
#define RIGHT_HAND 2

static uint8_t _get_hand(uint16_t combo_index) {
    switch (combo_index) {
        case COMBO_LSHIFT:
        case COMBO_LCTRL:
        case COMBO_LALT:
        case COMBO_LGUI:
            return LEFT_HAND;
        case COMBO_RSHIFT:
        case COMBO_RCTRL:
        case COMBO_RALT:
        case COMBO_RGUI:
            return RIGHT_HAND;
    }
    return 0;

}

static uint8_t _get_layer(uint16_t combo_index) {
    return 0;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    uint8_t mod = _get_mod(combo_index);
    uint8_t layer = _get_layer(combo_index);
    if (pressed) {
        if (mod) {
            combo_mod_state |= mod;
            register_mods(mod);
            if (_get_hand(combo_index) == LEFT_HAND) {
                layer_on(_LEFT_MOD);
            } else {
                layer_on(_RIGHT_MOD);
            }
        }
        if (layer) {
            layer_on(layer);
        }
    } else {
        if (mod) {
            if (mod | combo_mod_state) {
                unregister_mods(mod);
                combo_mod_state &= ~mod;
            }
            if (_get_hand(combo_index) == LEFT_HAND) {
                layer_off(_LEFT_MOD);
            } else {
                layer_off(_RIGHT_MOD);
            }
        }
        if (layer) {
            layer_off(layer);
        }
    }
}

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    // release early by returning true
    uint8_t mod;
    switch (keycode) {
        case L_THUMB_I2:
        case L_THUMB_I1:
        case L_THUMB:
        case L_THUMB_O:
        case R_THUMB_I2:
        case R_THUMB_I1:
        case R_THUMB:
        case R_THUMB_O:
            /* Thumb releases end the combo; the release process is handled in process_combo_event
             */
            return true; // thumb releases end the combo
        default:
            mod = _get_mod(combo_index);
            if (mod) {
                unregister_mods(mod);
                combo_mod_state &= ~mod;
            }
    }
    return false;
}

bool get_combo_is_contiguous(uint16_t combo_index, combo_t *combo) {
    if (_get_mod(combo_index)) {
        return false;
    }
    return true;
}

/*****************
 * KEY OVERRIDES *
 *****************/

#define ko_make_modded(_trigger, _replacement, _trigger_mods, _suppressed_mods, _negative_mods) \
    ((const key_override_t){                          \
        .trigger_mods          = (_trigger_mods),    \
        .layers                 = ~0,                 \
        .suppressed_mods        = (_suppressed_mods), \
        .options = ko_options_default,                \
        .negative_mod_mask      = (_negative_mods),   \
        .custom_action          = NULL,               \
        .context                = NULL,               \
        .trigger                = (_trigger),         \
        .replacement            = (_replacement),     \
        .enabled                = NULL,               \
     })

/* Press shift to activate a different shifted thing */
#define ko_shift_to_shift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, MOD_MASK_SHIFT, 0, 0)
/* Press shift to activate an unshifted thing */
#define ko_shift_to_unshift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, MOD_MASK_SHIFT, MOD_MASK_SHIFT, 0)
/* Don't press shift to activate a shifted thing */
#define ko_unshift_to_shift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, 0, 0, MOD_MASK_SHIFT)
/* Don't press shift to activate a different unshifted thing */
#define ko_unshift_to_unshift(_trigger, _replacement) ko_make_modded(_trigger, _replacement, 0, MOD_MASK_SHIFT, MOD_MASK_SHIFT)

const key_override_t exclaim_ko = ko_shift_to_shift(MY_DOT, KC_EXCLAIM);
const key_override_t question_ko = ko_shift_to_shift(MY_COMMA, KC_QUESTION);
//const key_override_t line_ko = ko_unshift_to_shift(MY_LINE, KC_UNDERSCORE);
const key_override_t backslash_ko = ko_shift_to_unshift(MY_LINE, KC_BACKSLASH);
//const key_override_t dash_ko = ko_unshift_to_unshift(MY_DASH, KC_MINUS);
const key_override_t slash_ko = ko_shift_to_unshift(MY_DASH, KC_SLASH);
//const key_override_t percent_ko = ko_unshift_to_shift(MY_PERCENT, KC_PERCENT);
//const key_override_t plus_ko = ko_unshift_to_shift(MY_PLUS, KC_PLUS);
const key_override_t times_ko = ko_shift_to_shift(MY_PLUS, KC_ASTERISK);
const key_override_t equals_ko = ko_shift_to_unshift(MY_EQUAL, KC_EQUAL);
const key_override_t pipe_ko = ko_shift_to_shift(MY_BOOL, KC_PIPE);
const key_override_t circumflex_ko = ko_shift_to_shift(MY_REGEX, KC_CIRCUMFLEX);
const key_override_t at_ko = ko_shift_to_shift(MY_HASH, KC_AT);
const key_override_t paren_ko = ko_shift_to_shift(MY_PAREN, KC_RIGHT_PAREN);
const key_override_t square_ko = ko_shift_to_unshift(MY_SQUARE, KC_RIGHT_BRACKET);
const key_override_t curly_ko = ko_shift_to_shift(MY_CURLY, KC_RIGHT_CURLY_BRACE);
const key_override_t angle_ko = ko_shift_to_shift(MY_ANGLE, KC_RIGHT_ANGLE_BRACKET);

const key_override_t **key_overrides = (const key_override_t *[]){
    &exclaim_ko,
    &question_ko,
    &backslash_ko,
    &slash_ko,
    &times_ko,
    &equals_ko,
    &pipe_ko,
    &circumflex_ko,
    &at_ko,
    &paren_ko,
    &square_ko,
    &curly_ko,
    &angle_ko,
    NULL // Null terminate the array of overrides!
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true; // continue processing as usual
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  W   |  F   |  M   |  P   |  V   |                              |  K   | -  / | _  \ | ;  : |  J   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |ESCAPE|  R   |  S   |  N   |  T   |  G   |                              | '  " |  A   |  E   |  I   |  H   | TAB  |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  X   |  C   |  L   |  D   |  B   | LOCK |      |  |      | LOCK |  Z   |  U   |  O   |  Y   |  Q   |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |ENTER |SPACE |ROCKET|  | MAGIC| .  ! | ,  ? |      |      |
 *                      |      |      |  SYM |      |  SYS |  |  NAV |      |  NUM |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
       XXXXXXX, KC_W, KC_F,  KC_M ,   KC_P ,    KC_V  ,                                                    KC_K  , MY_DASH, MY_LINE, KC_SEMICOLON, KC_J, XXXXXXX,
       XXXXXXX, KC_R, KC_S,  KC_N ,   KC_T ,    KC_G  ,                                                  KC_QUOTE,   KC_A ,   KC_E ,     KC_I    , KC_H, XXXXXXX,
       XXXXXXX, KC_X, KC_C,  KC_L ,   KC_D ,    KC_B  , LAYER_LOCK,   XXXXXXX,      XXXXXXX, LAYER_LOCK,    KC_Z ,   KC_U ,   KC_O ,     KC_Y    , KC_Q, XXXXXXX,
                           XXXXXXX,  KC_TAB, KC_SPACE ,  SYM_ENTER, NUM_ROCKET,   NAV_MAGIC,   MY_COMMA,   MY_DOT, LYR_SYS, XXXXXXX
    ),

/* Symbol Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |  %   |      |      |      | `  ~ |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              |      | +  * |  =   | &  | | $  ^ |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      | <  > | (  ) | [  ] | {  } | #  @ |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
     _______,_______,_______,_______,_______,_______,                                     MY_PERCENT,  _______,   _______,  _______, KC_GRAVE, _______,
     _______,KC_LGUI,KC_LALT,KC_LCTL,KC_LSFT,_______,                                        _______,  MY_PLUS,  MY_EQUAL,  MY_BOOL, MY_REGEX, _______,
     _______,_______,_______,_______,_______,_______,_______,_______,     _______,_______,  MY_ANGLE, MY_PAREN, MY_SQUARE, MY_CURLY,  MY_HASH, _______,
                             _______,_______,_______,_______,_______,     _______,_______,   _______,  _______,   _______
    ),

/* Number Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  A   |  6   |  5   |  4   |  D   |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  B   |  3   |  2   |  1   |  0   |  E   |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  C   |  9   |  8   |  7   |  F   |      |      |  |      |      |      |      |      |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NUMBERS] = LAYOUT(
       _______,_______,_______,_______,_______,_______,                                     KC_D, KC_4, KC_5, KC_6, KC_A, _______,
       _______,KC_LGUI,KC_LALT,KC_LCTL,KC_LSFT,_______,                                     KC_E, KC_0, KC_1, KC_2, KC_3, KC_B,
       _______,_______,_______,_______,_______,_______,_______,_______,    _______,_______, KC_F, KC_7, KC_8, KC_9, KC_C, _______,
                               _______,_______,_______,_______,_______,    _______,_______,_______,_______,_______
    ),

/* Nav Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  F4  | HOME |  UP  | END  |  F1  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  F7  |  F5  | LEFT | DOWN |RIGHT |  F2  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  F6  | PGUP |INSERT| PGDN |  F3  |      |      |  |      |      |      |      |      |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NAVIGATION] = LAYOUT(
     _______, KC_F5,  KC_HOME  ,   KC_UP  ,    KC_END   ,  KC_F1,                                     _______,_______,_______,_______,_______,_______,
      KC_F8 , KC_F6,  KC_LEFT  ,  KC_DOWN ,   KC_RIGHT  ,  KC_F2,                                     _______,KC_RSFT,KC_RCTL,MY_RALT,KC_RGUI,_______,
     _______, KC_F7, KC_PAGE_UP,   KC_F4  , KC_PAGE_DOWN,  KC_F3,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                   _______,   _______   ,_______,_______,_______,     _______,_______,_______,_______,_______
    ),

/* System and media layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              | F10  | F11  |VOL_UP| F12  | F13  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              |PLY/PS|M_PREV|VOL_DN|M_NEXT| F14  | F15  |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      | F16  | F17  | F18  | F19  | F20  |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYSTEM] = LAYOUT(
     _______,KC_F13,       KC_F12      ,KC_AUDIO_VOL_UP  ,          KC_F11   ,      KC_F10       ,                                 _______,_______,_______,_______,_______,_______,
     KC_F15, KC_F14,KC_MEDIA_PREV_TRACK,KC_AUDIO_VOL_DOWN,KC_MEDIA_NEXT_TRACK,KC_MEDIA_PLAY_PAUSE,                                 _______,KC_RSFT,KC_RCTL,MY_RALT,KC_RGUI,_______,
     _______,KC_F20,       KC_F19      ,     KC_F18      ,          KC_F17   ,      KC_F16       ,_______,_______, _______,_______,_______,_______,_______,_______,_______,_______,
                                                                          _______,_______,_______,_______,_______, _______,_______,_______,_______,_______
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
      _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
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
