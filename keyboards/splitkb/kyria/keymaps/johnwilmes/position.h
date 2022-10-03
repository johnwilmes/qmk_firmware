#pragma once

#include "keyboard.h"

/* Positions of Kyria keyboard, in same order as used in LAYOUT macro */
const keypos_t inverse_keymap[50] =
{
    (keypos_t){.row = 0, .col = 7},
    (keypos_t){.row = 0, .col = 6},
    (keypos_t){.row = 0, .col = 5},
    (keypos_t){.row = 0, .col = 4},
    (keypos_t){.row = 0, .col = 3},
    (keypos_t){.row = 0, .col = 2},
    (keypos_t){.row = 4, .col = 2},
    (keypos_t){.row = 4, .col = 3},
    (keypos_t){.row = 4, .col = 4},
    (keypos_t){.row = 4, .col = 5},
    (keypos_t){.row = 4, .col = 6},
    (keypos_t){.row = 4, .col = 7},
    (keypos_t){.row = 1, .col = 7},
    (keypos_t){.row = 1, .col = 6},
    (keypos_t){.row = 1, .col = 5},
    (keypos_t){.row = 1, .col = 4},
    (keypos_t){.row = 1, .col = 3},
    (keypos_t){.row = 1, .col = 2},
    (keypos_t){.row = 5, .col = 2},
    (keypos_t){.row = 5, .col = 3},
    (keypos_t){.row = 5, .col = 4},
    (keypos_t){.row = 5, .col = 5},
    (keypos_t){.row = 5, .col = 6},
    (keypos_t){.row = 5, .col = 7},
    (keypos_t){.row = 2, .col = 7},
    (keypos_t){.row = 2, .col = 6},
    (keypos_t){.row = 2, .col = 5},
    (keypos_t){.row = 2, .col = 4},
    (keypos_t){.row = 2, .col = 3},
    (keypos_t){.row = 2, .col = 2},
    (keypos_t){.row = 2, .col = 1},
    (keypos_t){.row = 2, .col = 0},
    (keypos_t){.row = 6, .col = 0},
    (keypos_t){.row = 6, .col = 1},
    (keypos_t){.row = 6, .col = 2},
    (keypos_t){.row = 6, .col = 3},
    (keypos_t){.row = 6, .col = 4},
    (keypos_t){.row = 6, .col = 5},
    (keypos_t){.row = 6, .col = 6},
    (keypos_t){.row = 6, .col = 7},
    (keypos_t){.row = 3, .col = 4},
    (keypos_t){.row = 3, .col = 3},
    (keypos_t){.row = 3, .col = 2},
    (keypos_t){.row = 3, .col = 1},
    (keypos_t){.row = 3, .col = 0},
    (keypos_t){.row = 7, .col = 0},
    (keypos_t){.row = 7, .col = 1},
    (keypos_t){.row = 7, .col = 2},
    (keypos_t){.row = 7, .col = 3},
    (keypos_t){.row = 7, .col = 4},
};

#define FINGER_INDEX(f) f-(FINGERS_START+1)
#define IS_FINGER(f) (f > FINGERS_START && f < FINGERS_END)

#define NULL_POSITION (keypos_t){.row = 255, .col = 255}

keypos_t get_finger_position(uint16_t finger_keycode) {
    if IS_FINGER(finger_keycode) {
        return inverse_keymap[FINGER_INDEX(finger_keycode)];
    }
    return NULL_POSITION;
}
