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
#include "implied_mods.h"


extern const uint16_t PROGMEM implied_mod_groups[];
static const uint16_t *active_implied_mods = NULL;

#define GET_IMPLIED_MODS_MASK(implied_mods) (pgm_read_word(implied_mods-1))

static bool get_group_has_keycode(const uint16_t *group, uint16_t keycode) {
    while (true) {
        uint16_t member = pgm_read_word(group);
        if (!member) {
            return false;
        } else if (member == keycode) {
            return true;
        }
        group++;
    }
}

static const uint16_t *get_implied_mods(uint16_t keycode) {
    const uint16_t *result = NULL;
    for (const uint16_t *code_ptr = implied_mod_groups; ; code_ptr++) {
        uint16_t code = pgm_read_word(code_ptr);
        if (!code) {
            if (result == NULL) {
                return NULL;
            } else {
                result = NULL;
            }
        } else {
            if (result == NULL) {
                result = code_ptr+1;
            } else {
                if (code == keycode) {
                    return result;
                }
            }
        }
    }
}

void unregister_implied_mods(void) {
    if (active_implied_mods != NULL) {
        unregister_mods(GET_IMPLIED_MODS_MASK(active_implied_mods));
        active_implied_mods = NULL;
    }
}

void process_implied_mods_press(uint16_t keycode) {
    if (active_implied_mods == NULL) {
        active_implied_mods = get_implied_mods(keycode);
        if (active_implied_mods != NULL) {
            register_mods(GET_IMPLIED_MODS_MASK(active_implied_mods));
        }
    } else if (!get_group_has_keycode(active_implied_mods, keycode)) {
        unregister_implied_mods();
    }
}

