/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#pragma once

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_CONTIGUOUS_PER_COMBO
#define COMBO_PROCESS_KEY_RELEASE
#define COMBO_MUST_HOLD_PER_COMBO
#define COMBO_TERM_PER_COMBO
#define COMBO_HOLD_TERM 200
#define COMBO_TERM 125

// These don't do actually do anything, if RGB matrix EEPROM has already been written
// To set RGB matrix defaults, you need to explicitly reset EEPROM
#define RGB_MATRIX_DEFAULT_ON true
#define RGB_MATRIX_DEFAULT_MODE 1
