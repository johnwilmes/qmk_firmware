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
#include "implied_mods.h"

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
}
#endif

/************
 * TAP/HOLD *
 ************/

/*
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_SPACE:
            if (1==record->event.key.row) {
                return true;
            }
            return false;
        case MY_DOT:
            if (5==record->event.key.row) {
                return true;
            }
            return false;
    }
    return false;
}
*/

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
    NULL  // Null terminate the array of overrides!
};
// clang-format on

/****************
 * IMPLIED MODS *
 ****************/

const uint16_t PROGMEM implied_mod_groups[] = {
    IMPLIED_MODS_GROUP(MOD_BIT(KC_LALT), APP_PREV, APP_NEXT, WIN_PREV, WIN_NEXT),
    0
};

/**************
 * USER HOOKS *
 **************/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods;
    if (record->event.pressed) {
        process_implied_mods_press(keycode);
        switch(keycode) {
            case BIGRAM_QU:
                mods = get_mods();
                SEND_STRING("q");
                set_mods(mods & ~MOD_MASK_SHIFT);
                SEND_STRING("u");
                set_mods(mods);
                break;
            case APP_PREV:
                tap_code16(S(KC_TAB));
                break;
            case APP_NEXT:
                tap_code(KC_TAB);
                break;
            case WIN_PREV:
                tap_code16(S(KC_GRAVE));
                break;
            case WIN_NEXT:
                tap_code(KC_GRAVE);
                break;
        }
    }
    return true;  // continue processing as usual
}

layer_state_t layer_state_set_user(layer_state_t state) {
    unregister_implied_mods();
    return state;
}



/**********
 * LAYERS *
 **********/


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
       XXXXXXX, KC_Z, KC_F, KC_M  , KC_P    ,  KC_V     ,                                               KC_Q    , MY_DASH, MY_LINE, KC_SEMICOLON, KC_J, XXXXXXX,
       XXXXXXX, KC_R, KC_S, KC_N  , KC_T    ,  KC_G     ,                                               MY_QUOTE, KC_A   , KC_E   , KC_I        , KC_H, XXXXXXX,
       XXXXXXX, KC_W, KC_C, KC_L  , KC_D    ,  KC_B     , XXXXXXX , XXXXXXX   ,   XXXXXXX   , XXXXXXX , KC_X    , KC_U   , KC_O   , KC_Y        , KC_K, XXXXXXX,
                           XXXXXXX, MO_MOUSE,  MY_SPACE , L_LEADER, LAYER_LOCK,   LAYER_LOCK, R_LEADER, MY_DOT  , XXXXXXX, XXXXXXX
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
    [_LEFT_MOD] = LAYOUT(
      _______, _______, _______, MO_BRKT, MO_NUM , MO_HEX ,                                        _______, _______, _______, _______, _______, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, MO_SYM , MO_SYMS,KC_SPACE, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
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
      _______, _______, _______, _______, _______, _______,                                        MO_SYS1, MO_SYS2, MO_SYS3, MO_SYS4, MO_SYS5, _______,
      _______, _______, _______, _______, _______, _______,                                        _______, KC_RSFT, KC_RCTL, MY_RALT, KC_RGUI, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, MO_NAV , MO_NAVS, MO_NAVC, MO_NAVA, MO_NAVG, _______,
                                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
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
     _______,_______,_______,_______,_______,_______,                                      _______ , _______, _______ , _______, _______    , _______,
     _______,_______,_______,_______,_______,_______,                                      _______ , MY_PLUS, MY_EQUAL, MY_NOT , MY_ANGLE   , _______,
     _______,_______,_______,_______,_______,_______,_______,_______,     _______,_______, MY_GRAVE, MY_HASH, MY_REGEX, MY_BOOL, MY_QUESTION, _______,
                             _______,_______,_______,_______,_______,     _______,_______, _______ , _______, _______
    ),

    /* Brackets implemented using separate layer rather than key-overrides like the other symbols,
     * because we want to retain ability to modify with CTRL using one-shot mods when needed */
    [_BRACKETS] = LAYOUT(
     _______,_______,_______,_______,_______,_______,                                     _______, _______, _______, _______, _______ , _______,
     _______,_______,_______,_______,_______,_______,                                     _______, KC_LPRN, KC_LBRC, KC_LCBR, MY_ANGLE, _______,
     _______,_______,_______,_______,_______,_______,_______,_______,     _______,_______,_______, KC_RPRN, KC_RBRC, KC_RCBR, KC_RABK , _______,
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
       _______,_______,_______,_______,_______,_______,                                    _______, KC_4  , KC_5  , KC_6, _______, _______,
       _______,_______,_______,_______,_______,_______,                                     KC_E  , KC_0  , KC_1  , KC_2, KC_3   , _______,
       _______,_______,_______,_______,_______,_______,_______,_______,    _______,_______, KC_X  , KC_7  , KC_8  , KC_9, _______, _______,
                               _______,_______,_______,_______,_______,    _______,_______,_______,_______,_______
    ),
    [_HEX] = LAYOUT(
       _______,_______,_______,_______,_______,_______,                                    _______,_______,_______,_______,_______,_______,
       _______,_______,_______,_______,_______,_______,                                    KC_E   , KC_A  , KC_B  , KC_C  ,_______,_______,
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
    [_NAVIGATION] = LAYOUT(
     _______, KC_F5, KC_PAGE_UP, KC_UP  , KC_PAGE_DOWN, KC_F2  ,                                     _______,_______,_______,_______,_______,_______,
     _______, KC_F4, KC_LEFT   , KC_DOWN, KC_RIGHT    , KC_F1  ,                                     _______,_______,_______,_______,_______,_______,
     _______, KC_F6, KC_HOME   , KC_F7  , KC_END      , KC_F3  ,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                 _______, _______     , _______,_______,_______,     _______,_______,_______,_______,_______
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
    [_SYSTEM1] = LAYOUT(
     _______, XXXXXXX    , NOTIFICATIONS, OVERVIEW_UP  , MESSAGES  , XXXXXXX,                                     _______,_______,_______,_______,_______,_______,
     _______, LOCK_SCREEN, MAXIMIZE     , OVERVIEW_DOWN, FULLSCREEN, SYS_RUN,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX    , MEDIA_PREV   , MEDIA_PLAY   , MEDIA_NEXT, XXXXXXX,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                        _______      , _______   , _______,_______,_______,     _______,_______,_______,_______,_______
     ),

    [_SYSTEM2] = LAYOUT(
     _______, XXXXXXX, TAB_PREV, APP_PREV, TAB_NEXT, XXXXXXX ,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX, WIN_PREV, APP_NEXT, WIN_NEXT, TERMINAL,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX, VOL_DOWN, VOL_MUTE, VOL_UP  , XXXXXXX ,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                 _______ , _______ , _______ ,_______,_______,     _______,_______,_______,_______,_______
    ),

    [_SYSTEM3] = LAYOUT(
     _______, XXXXXXX  , XXXXXXX     , WORKSPACE_PREV, XXXXXXX     , XXXXXXX,                                     _______,_______,_______,_______,_______,_______,
     _______, SYS_CLOSE, XXXXXXX     , WORKSPACE_NEXT, XXXXXXX     , BROWSER,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX  , PRINT_SELECT, PRINT_WINDOW  , PRINT_SCREEN, XXXXXXX,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                       _______       , _______     , _______,_______,_______,     _______,_______,_______,_______,_______
    ),

    [_SYSTEM4] = LAYOUT(
     _______, XXXXXXX, TAB_MOVE_PREV, WS_MOVE_PREV, TAB_MOVE_NEXT, XXXXXXX  ,                                     _______,_______,_______,_______,_______,_______,
     _______, C_A_DEL, MON_MOVE_PREV, WS_MOVE_NEXT, MON_MOVE_NEXT, PASSWORDS,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX, SAVE_SELECT  , SAVE_WINDOW , SAVE_SCREEN  , XXXXXXX  ,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                      _______     , _______      , _______  ,_______,_______,     _______,_______,_______,_______,_______
    ),

    [_SYSTEM5] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     _______,_______,_______,_______,_______,_______,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______,_______,     _______,_______,_______,_______,_______,_______,_______,_______,
                                _______, _______, _______,_______,_______,     _______,_______,_______,_______,_______
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
