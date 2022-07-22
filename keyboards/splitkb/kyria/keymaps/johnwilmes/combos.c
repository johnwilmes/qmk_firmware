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

/*********************
 * COMBO DEFINITIONS *
 *********************/

#define CMB_PREFIX COMBO_
#define BLANK(...)
#define CMB_ENUM(name, ...) CMB_PREFIX##name,
#define CMB_DATA(name, result, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define CMB_KEY(name, key, ...) [CMB_PREFIX##name] = COMBO(cmb_##name, key),
#define CMB_ACTION(name, key, ...) [CMB_PREFIX##name] = COMBO_ACTION(cmb_##name),

/* Store combo index enum */
#undef COMBO_KEY
#undef COMBO_SUBS
#undef COMBO_PRECOG
#define COMBO_KEY CMB_ENUM
#define COMBO_SUBS CMB_ENUM
#define COMBO_PRECOG CMB_ENUM
enum combos {
#include "combos.def"
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

/* Store combo triggering keys data */
#undef COMBO_KEY
#undef COMBO_SUBS
#undef COMBO_PRECOG
#define COMBO_KEY CMB_DATA
#define COMBO_SUBS CMB_DATA
#define COMBO_PRECOG CMB_DATA
#include "combos.def"

/* Store combo_t array (combo results) */
#undef COMBO_KEY
#undef COMBO_SUBS
#undef COMBO_PRECOG
#define COMBO_KEY CMB_KEY
#define COMBO_SUBS CMB_ACTION
#define COMBO_PRECOG CMB_ACTION
combo_t key_combos[] = {
#include "combos.def"
};

#undef COMBO_KEY
#define COMBO_KEY BLANK

/*****************
 * SUBSTITUTIONS *
 *****************/

#undef COMBO_PRECOG
#define COMBO_PRECOG BLANK

#define SUBS_EVENT(name, string, ...) case CMB_PREFIX##name: if (pressed) { SEND_STRING(string); } break;

#undef COMBO_SUBS
#define COMBO_SUBS SUBS_EVENT

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
#include "combos.def"
    }
}

/****************
 * PRECOGNITION *
 ****************/

#undef COMBO_SUBS
#define COMBO_SUBS BLANK

#define PRECOG_LAYER(name, layer, ...) case CMB_PREFIX##name: return layer;

#undef COMBO_PRECOG
#define COMBO_PRECOG PRECOG_LAYER

extern bool _combo_has_key(combo_t *combo, uint16_t keycode);
extern void dump_keyrecord(keyrecord_t *record);

uint8_t get_precognition_layer(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
#include "combos.def"
    }
    return 0;
}

bool get_combo_needs_details(uint16_t combo_index, combo_t *combo) {
    /* Combos with non-zero precognition layer need detailed handling */
    return get_precognition_layer(combo_index, combo);
}

bool get_combo_interrupted(uint16_t combo_index, combo_t *combo, keyrecord_t *record) {
    uint8_t precognition_layer = get_precognition_layer(combo_index, combo);
    if (precognition_layer) {
        uint16_t trigger = pgm_read_word(combo->keys);
        for (uint16_t i=0; i < COMBO_LEN; i++) {
            combo_t *other_combo = &key_combos[i];
            if (!other_combo->keycode && (pgm_read_word(other_combo->keys) == trigger)) {
                uint8_t other_precognition = get_precognition_layer(i, other_combo);
                if (other_precognition == precognition_layer) {
                    if (_combo_has_key(other_combo, record->keycode)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


void process_combo_detailed_press(uint16_t combo_index, combo_t *combo, keyrecord_t *triggers) {
    uint8_t precognition_layer = get_precognition_layer(combo_index, combo);
    if (precognition_layer) {
        layer_on(precognition_layer);
        /* For each key after the first one listed for the combo, pass through its key press (in
         * the order of appearance in combo->keys) */
        for (uint8_t i=1; ; i++) {
            uint16_t keycode = pgm_read_word(&combo->keys[i]);
            if (COMBO_END == keycode) {
                break;
            }
            keyrecord_t *record = triggers;
            while (record->keycode != keycode) {
                record++;
            }
            keyrecord_t passthrough = {
                .event =
                    {
                        .key     = record->event.key,
                        .time    = triggers->event.time,
                        .pressed = true,
                    },
            };
            dump_keyrecord(&passthrough);
        }
    }
}

bool process_combo_detailed_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode, keyevent_t *event) {
    uint8_t precognition_layer = get_precognition_layer(combo_index, combo);
    if (precognition_layer) {
        if (key_index == 0) {
            layer_off(precognition_layer);
            return true;
        } else {
            keyrecord_t record = { .event = *event };
            dump_keyrecord(&record);
        }
    }
    return false;
}


/************************
 * HOLDING, TERMS, ETC. *
 ************************/

bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    return get_precognition_layer(combo_index, combo);
}

const uint8_t n_thumbs = 14;
const uint16_t thumbs[] = {L_THUMB_I3, L_THUMB_I2, L_THUMB_I1, L_THUMB, L_THUMB_O, L_THUMB_U, L_THUMB_OU,
                           R_THUMB_I3, R_THUMB_I2, R_THUMB_I1, R_THUMB, R_THUMB_O, R_THUMB_U, R_THUMB_OU};
                          

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    if (get_precognition_layer(combo_index, combo)) {
        return 200;
    }
    /* Thumbs are slower than other fingers, so they get longer combo terms */
    for (uint8_t i=0; i<n_thumbs; i++) {
        if (_combo_has_key(combo, thumbs[i])) {
            return 125;
        }
    }
    return COMBO_TERM;
}
