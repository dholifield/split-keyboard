#include QMK_KEYBOARD_H

// clang-format off
const uint8_t keyPhysicalMap[42] = {
    0,  1,  2,  3,  4,  5,      6,  7,  8,  9,  10, 11,
    12, 13, 14, 15, 16, 17,     18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29,     30, 31, 32, 33, 34, 35,
                36, 37, 38,     39, 40, 41};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( // Base
        KC_Q, KC_W, KC_E, /* … total 42 keys … */ KC_NO),
    [1] = LAYOUT( // L1
        KC_1, KC_2, KC_3, /* … */ KC_NO),
    [2] = LAYOUT( // L2
        KC_1, KC_2, KC_3, /* … */ KC_NO)
};
// clang-format on
