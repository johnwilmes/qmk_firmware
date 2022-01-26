#pragma once

#include "keyboard.h"

enum layers {
    _BASE    = 0,
    _FINGERS = COMBO_ONLY_FROM_LAYER,
    _LEFT_MOD,
    _RIGHT_MOD,
    _SYMBOLS,
    _BRACKETS,
    _NUMBERS,
    _HEX,
    _NAVIGATION,
    _SYSTEM,
    _MOUSE,
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
#define MY_DASH KC_MINUS
#define MY_LINE KC_UNDERSCORE
#define MY_QUOTE KC_DOUBLE_QUOTE
#define MY_PLUS KC_PLUS
#define MY_EQUAL KC_EQUAL
#define MY_NOT KC_EXCLAIM
#define MY_ANGLE KC_LEFT_ANGLE_BRACKET
#define MY_GRAVE KC_GRAVE
#define MY_HASH KC_HASH
#define MY_REGEX KC_DOLLAR
#define MY_BOOL KC_AMPERSAND
#define MY_QUESTION KC_QUESTION

#define L_LEADER KC_F18
#define R_LEADER KC_F19
#define MY_MAGIC KC_F22

#define SYS_UP KC_F14
#define SYS_DOWN KC_F15
#define SYS_LEFT KC_F16
#define SYS_RIGHT KC_F17
#define SYS_HOME KC_F20
#define SYS_END KC_F21

#define MEDIA_LEFT KC_MEDIA_PREV_TRACK
#define MEDIA KC_MEDIA_PLAY_PAUSE
#define MEDIA_RIGHT KC_MEDIA_NEXT_TRACK

#define MO_SYM MO(_SYMBOLS)
#define MO_BRKT MO(_BRACKETS)
#define MO_NUM MO(_NUMBERS)
#define MO_HEX MO(_HEX)
#define MO_NAV MO(_NAVIGATION)
#define MO_SYS MO(_SYSTEM)
#define MO_MOUSE MO(_MOUSE)

#define MY_RALT KC_LALT
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
