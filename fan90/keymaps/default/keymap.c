/* Copyright 2020 xcd0
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
#include "keymap_jp.h"

#define JP_F1   KC_F1
#define JP_F2   KC_F2
#define JP_F3   KC_F3
#define JP_F4   KC_F4
#define JP_F5   KC_F5
#define JP_F6   KC_F6
#define JP_F7   KC_F7
#define JP_F8   KC_F8
#define JP_F9   KC_F9
#define JP_F10   KC_F10
#define JP_F11   KC_F11
#define JP_F12   KC_F12
#define JP_PGUP KC_PGUP
#define JP_PGDN KC_PGDN
#define JP_LSFT KC_LSFT
#define JP_RSFT KC_RSFT
#define JP_LCTL KC_LCTL
#define JP_RCTL KC_RCTL
#define JP_LALT KC_LALT
#define JP_RALT KC_RALT
#define JP_LGUI KC_LGUI
#define JP_RGUI KC_RGUI
#define JP_ENT  KC_ENT
#define JP_SPC  KC_SPC
#define JP_ESC  KC_ESC
#define JP_TAB  KC_TAB
#define JP_DEL  KC_DEL
#define JP_HOME KC_HOME
#define JP_END  KC_END
#define JP_INS  KC_INS
#define JP_PAUS KC_PAUS
#define JP_SLCK KC_SLCK
#define JP_PSCR KC_PSCR
#define JP_BSPC KC_BSPC

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//    col 00   col 01   col 02   col 03   col 04   col 05   col 06   col 07   col 08   col 09   col 10   col 11   col 12   col 13   col 14
  [_QWERTY] = LAYOUT( \
      JP_PGUP, _______, JP_F1,   JP_F2,   JP_F3,   JP_F4,   JP_F5,   JP_F8,   JP_PSCR, JP_SLCK, JP_F11,  JP_F12,  _______, _______, JP_GRV, \
      JP_PGDN, JP_ESC,  JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_F7,   JP_PAUS, JP_F10,  JP_0,    JP_MINS, JP_DEL,  _______, JP_QUOT, \
      JP_HOME, JP_TAB,  JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,    JP_F6,   JP_F9,   JP_9,    JP_O,    JP_P,    JP_BSPC, JP_ASTR, JP_EQL, \
      JP_END,  JP_LSFT, JP_A,    JP_S,    JP_D,    JP_F,    JP_G,    JP_6,    JP_8,    JP_I,    JP_K,    JP_L,    JP_SCLN, JP_COMM, JP_DOT,  \
      JP_INS,  JP_LCTL, JP_Z,    JP_X,    JP_C,    JP_V,    JP_B,    JP_7,    JP_U,    JP_J,    JP_M,    JP_MHEN, JP_HENK, JP_LPRN, JP_RPRN, \
      _______, JP_LALT, JP_LGUI, _______, _______, JP_SLSH, JP_BSLS, JP_Y,    JP_H,    JP_N,    _______, JP_SPC,  JP_RSFT, JP_LCTL, JP_ENT  \
      )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
