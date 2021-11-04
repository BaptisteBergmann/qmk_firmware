/* Copyright 2021 owl
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


void keyboard_pre_init_kb(void) { setPinInputHigh(B7); }

/*
 * .--------------------------.
 * | 1  | 2  | 3  |    ___    |
 * -------------------(   )----
 * | =  | 0  | .  |    ===    |
 * `--------------------------' 
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_7,     KC_8, KC_9,       \
        KC_4,     KC_5, KC_6),      \


/*    // [1] = LAYOUT(
 *   //     RGB_TOG,  RGB_MOD, RGB_HUI,          _______, KC_1, KC_2,   KC_3,   KC_4,     KC_5, KC_6, KC_7, KC_8,   KC_9,   KC_0, _______,  \
 *   //     _______, RGB_RMOD, RGB_HUD,          _______,  _______, _______,   _______,   _______,    _______, _______, _______, _______,   _______,   _______, _______,  \
 *   //     RGB_SPI,  RGB_VAI, RGB_SAI,          _______,   _______,   _______,   _______,  _______, _______, _______,  _______, _______,   _______,   _______, _______, \
 *   //     RGB_SPD,  RGB_VAD, RGB_SAD,          _______,  _______, _______, _______,     _______ ,    _______,     KC_RALT, _______, _______, _______, _______),
 *        
 *
 *   // [2] = LAYOUT(
 *
 *   //     KC_F10,   KC_F11,KC_F12,     _______,  _______,   _______,   _______,  _______,  _______, _______, _______, _______, KC_MINS,   KC_EQL,    KC_DEL,  \
 *   //     KC_F7,    KC_F8, KC_F9,      _______,   _______,   _______,   _______,  _______,  _______, _______, _______, _______,   _______,   KC_BSLS, KC_QUOT,  \
 *   //     KC_F4,    KC_F5, KC_F6,      _______,    _______,   _______,   _______,  _______,  _______, _______,  _______, _______,   _______,   _______, _______, \
 *   //     KC_F1,    KC_F2, KC_F3,      _______,  _______, _______, _______,     _______ ,    _______,     _______, _______, _______, _______, _______),
 *       
 *
 *   // [3] = LAYOUT(
 *   //     KC_F1,    KC_F2, KC_F3,          _______,  _______,   _______,   _______,  _______,   _______, _______, _______, _______,   _______,   _______, _______,  \
 *   //     KC_F4,    KC_F5, KC_F6,          _______,   _______,   _______,   _______,  _______,  _______, _______, _______, _______,   _______,   _______, _______,  \
 *   //     KC_F7,    KC_F8, KC_F9,          _______,   _______,   _______,   _______,  _______, _______, _______,  _______, _______,   _______,   _______, _______, \
 *   //     KC_F10,   KC_F11,KC_F12,        _______,  _______, _______, _______,     _______ ,    _______,     _______, _______, _______, _______, _______),
*/
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
        case 0:
            // layer 0 - next song (CW) and previous (CCW)
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case 1:
            // layer 1 - change desktop right (CW) and left (CCW)
            if (clockwise) {
                tap_code16(KC_BRIU);
            } else {
                tap_code16(KC_BRID);
            }
            break;

        case 2:
            // layer 2 - redo (CW) and undo (CCW)
            if (clockwise) {
                tap_code16(LCTL(KC_Y));
            } else {
                tap_code16(LCTL(KC_Z));
            }
            break;

        case 3:
            // layer 3 - previous (KC_MNXT) and Next (KC_MPRV)
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
            break;
    }
    return true;
}

bool encoder_pin_state = false;

void matrix_scan_user(void) {
    if (readPin(B7) == 0) {
        if (encoder_pin_state == false) {
            uint8_t layer = biton32(layer_state);
            switch (layer) {
                case 0:
                    // layer 0 - next song (CW) and previous (CCW)
                    tap_code(KC_MUTE);
                    break;

                case 1:
                    // layer 1 - change desktop right (CW) and left (CCW)
                    break;

                case 2:
                    // layer 2 - redo (CW) and undo (CCW)
                    break;

                case 3:
                    // layer 3 - Play pause
                    tap_code(KC_MPLY);
                    break;
            }
        }
        encoder_pin_state = true;
    } else {
        encoder_pin_state = false;
    }
}