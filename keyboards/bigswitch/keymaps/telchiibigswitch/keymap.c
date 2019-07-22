/*
Copyright 2018 QMK Contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgblight.h"

enum custom_keycodes {
	FLASHLOCK = SAFE_RANGE,
};

const uint8_t RGBLED_CHRISTMAS_INTERVALS[] PROGMEM = {250};

void matrix_init_user() {
	rgblight_disable();
	rgblight_disable_noeeprom();
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case FLASHLOCK:
			if(record->event.pressed) {
				//rgblight_mode(25);
				//SEND_STRING(SS_TAP(RGB_MODE_XMAS));
				rgblight_mode_noeeprom(25);
				rgblight_enable();
			} else {
				SEND_STRING(SS_LGUI("l"));
				rgblight_disable();
			}
	};
	
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT(FLASHLOCK),
};
