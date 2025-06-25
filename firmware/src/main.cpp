#include "split42.h"
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

const uint8_t int_pin = 29;
int32_t prev = 0;

// clang-format off
KBHalf left(0x24,
           {3, 23, 20, 19, 16, 14,
            2,  4, 21, 18, 15, 13,
            1,  0, 22, 17, 11, 12,
                        5,  6,  7},
        //    {KEY_TAB,      KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T,
        //     KEY_ESC,      KEY_A, KEY_S, KEY_D, KEY_F, KEY_F,
        //     KEY_LEFT_ALT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,
        //         KEY_LEFT_SHIFT, KEY_LEFT_CTRL, KEY_LEFT_GUI}
           {'t', 'q', 'w', 'e', 'r', 't',
            'e', 'a', 's', 'd', 'f', 'g',
            'a', 'z', 'x', 'c', 'v', 'b',
                           's', '\n', ' '}
           );

// KBHalf right(0x20,
//             {14, 16, 19, 20, 23, 3,
//              13, 15, 18, 21,  4, 2,
//              12, 11, 17, 22,  0, 1,
//               7,  6,  5}
//             );

// clang-format on

void setup() {
    Serial.begin(115200); // debugging

    Wire.begin(); // start i2c
    Wire.setClock(400000);

    pinMode(int_pin, INPUT); // setup interrupt pin

    left.init();
    // right.init();
}

void loop() {
    // Serial.print(digitalRead(int_pin));
    if (digitalRead(int_pin)) return;
    uint32_t state = left.get_state();
    uint32_t diff = state ^ prev;
    for (int bit = 0; bit < 24; ++bit) {
        if (diff & (1 << bit)) {
            bool pressed = state & (1 << bit);
            uint8_t sw = left.pinmap[bit];
            char key = left.keymap[sw];

            if (pressed) Serial.print(key);
        }
    }
    prev = state;
    delay(2);
}