#pragma once

#include "macros.h"

enum layers {
    _FINGERS = COMBO_ONLY_FROM_LAYER,
    _BASE,
    _LEFT_MOD,
    _RIGHT_MOD,
    _SYMBOLS,
    _NUMBERS,
    _HEX,
    _NAVIGATION,
    _MOUSE,
};

#undef KEY_DEF
#define KEY_DEF(name, ...) name

enum my_keycodes {
    FINGERS_START = SAFE_RANGE,
    FOR_EACH_KEY_DEF(IDENTITY),
    FINGERS_END,

    APP_PREV,
    APP_NEXT,
    WIN_PREV,
    WIN_NEXT,

    MY_RGB_T,
    MY_RGB_U,
    MY_RGB_D,
    EEPROM_FLUSH,

};

#define FINGER_INDEX(f) f-(FINGERS_START+1)
#define IS_FINGER(f) (f > FINGERS_START && f < FINGERS_END)

/* ADDITIONAL KEYS */

#define MY_RALT KC_LALT

/* SYMBOLS - usually these have shift overrides */

#define MY_REGEX KC_CIRCUMFLEX // ^ $
#define MY_COMMA KC_COMMA // , ;
#define MY_DOT KC_DOT // . :
/* #define KC_QUOTE // ' " unchanged */
#define MY_TICK KC_GRAVE // ` ?

#define MY_ANGLE KC_LEFT_ANGLE_BRACKET // < >
#define MY_PAREN KC_LEFT_PAREN // ( )
#define MY_SQUARE KC_LEFT_BRACKET // [ ]
#define MY_CURLY KC_LEFT_CURLY_BRACE // { }
#define PERC_HASH KC_PERCENT // % #

#define MY_BOOL KC_AMPERSAND // & |
#define MY_NOT KC_EXCLAIM // ! ~
#define MY_EQUAL KC_EQUAL // = =
#define TIMES_PLUS KC_ASTERISK // * +
/* #define KC_AT // @ unchanged */

/* other symbols: /\-_ are from combos */

#define MY_MUTE KC_MUTE
#define MY_VOLU KC_VOLU
#define MY_VOLD KC_VOLD


/* LAYER SWITCHING */
#define MO_LMOD MO(_LEFT_MOD)
#define MO_RMOD MO(_RIGHT_MOD)
#define MO_SYM MO(_SYMBOLS)
#define MO_NUM MO(_NUMBERS)
#define MO_HEX MO(_HEX)
#define MO_SHEX LM(_HEX, MOD_LSFT)
#define MO_NAV MO(_NAVIGATION)
#define MO_MOUS MO(_MOUSE)
