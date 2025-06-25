#include "Adafruit_TinyUSB.h"
#include <Arduino.h>
#include <split42.h>
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
           {HID_KEY_TAB,        HID_KEY_Q,  HID_KEY_W,  HID_KEY_E,  HID_KEY_R,  HID_KEY_T,
            HID_KEY_ESC,        HID_KEY_A,  HID_KEY_S,  HID_KEY_D,  HID_KEY_F,  HID_KEY_F,
            HID_KEY_LEFT_ALT,   HID_KEY_Z,  HID_KEY_X,  HID_KEY_C,  HID_KEY_V,  HID_KEY_B,
                                  HID_KEY_LEFT_SHIFT, HID_KEY_LEFT_CTRL, HID_KEY_LEFT_GUI}
           );

// KBHalf right(0x20,
//             {14, 16, 19, 20, 23, 3,
//              13, 15, 18, 21,  4, 2,
//              12, 11, 17, 22,  0, 1,
//               7,  6,  5}
//             );

// clang-format on

Adafruit_USBD_HID usb_hid;

void setup() {
    // setup serial
    Serial.begin(115200);

    // set up I2C
    Wire.begin();
    Wire.setClock(400000);

    // setup interrupt
    pinMode(int_pin, INPUT);

    // setup HID
    if (!TinyUSBDevice.isInitialized()) { TinyUSBDevice.begin(0); }

    uint8_t const desc[] = {TUD_HID_REPORT_DESC_KEYBOARD()};

    usb_hid.setBootProtocol(HID_ITF_PROTOCOL_KEYBOARD);
    usb_hid.setPollInterval(1); // ms
    usb_hid.setReportDescriptor(desc, sizeof(desc));
    usb_hid.setStringDescriptor("Split42 Keyboard");

    usb_hid.begin();
    while (!TinyUSBDevice.mounted())
        ;

    // setup keyboard
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