#pragma once

#include "keyboard.h"

enum layers {
    _BASE = 0,
    _FINGERS = COMBO_ONLY_FROM_LAYER,
    _SYMBOLS,
    _NUMBERS,
    _NAVIGATION,
    _SYSTEM,
    _LEFT_MOD,
    _RIGHT_MOD,
};

enum my_keycodes {
    FINGERS_START = SAFE_RANGE,
    #define FINGERS_MACRO(...) __VA_ARGS__,
    #include "fingers.def"
    #undef FINGERS_MACRO
    FINGERS_END,

    LAYER_LOCK,
};

/* ADDITIONAL KEYS */

#define MY_DOT KC_DOT
#define MY_COMMA KC_COMMA
#define MY_DASH KC_MINUS
#define MY_LINE KC_UNDERSCORE
#define MY_PERCENT KC_PERCENT
#define MY_PLUS KC_PLUS
#define MY_EQUAL KC_EQUAL
#define MY_BOOL KC_AMPERSAND
#define MY_REGEX KC_DOLLAR
#define MY_HASH KC_HASH
#define MY_PAREN KC_LEFT_PAREN
#define MY_SQUARE KC_LEFT_BRACKET
#define MY_CURLY KC_LEFT_CURLY_BRACE
#define MY_ANGLE KC_LEFT_ANGLE_BRACKET

#define MY_RALT KC_LALT

#define MY_ROCKET KC_F23
#define MY_MAGIC KC_F24

#define NUM_ROCKET LT(_NUMBERS, MY_ROCKET)
#define SYM_ENTER  LT(_SYMBOLS, KC_ENTER)

#define NAV_MAGIC  LT(_NAVIGATION, MY_MAGIC)
#define LYR_SYS       MO(_SYSTEM)
