#include "split42.h"

KBHalf::KBHalf(uint8_t addr, std::initializer_list<uint8_t> pinmap,
               std::initializer_list<uint8_t> keymap)
    : addr(addr) {
    // pinmap
    assert(pinmap.size() <= 21);
    int i = 0;
    for (auto pin : pinmap) {
        assert(pin < 24);
        this->pinmap[pin] = i++;
    }

    // keymaps
    assert(keymap.size() <= 21);
    i = 0;
    for (auto key : keymap) {
        this->keymap[i++] = key;
    }
}

void KBHalf::init() {
    write(0x10, 0xFF, 5); // invert all polarity
    write(0x18, 0xFF, 5); // set all to inputs
    write(0x20, 0x00, 5); // enable interrupts on all pins
    get_state();          // clear all interupts
}

void KBHalf::write(uint8_t reg, uint8_t value, uint8_t len) {
    Wire.beginTransmission(addr);
    Wire.write(reg | 0x80); // add auto-incrementing
    for (uint8_t i = 0; i < len; ++i)
        Wire.write(value);
    Wire.endTransmission();
}

uint32_t KBHalf::get_state() {
    Wire.beginTransmission(addr);
    Wire.write(0x80);
    Wire.endTransmission(false);
    uint8_t buf[5];
    uint8_t count = Wire.requestFrom(addr, (uint8_t)5);
    for (uint8_t i = 0; i < count; ++i)
        buf[i] = Wire.read();

    return (buf[0]) | (buf[3] << 8) | (buf[4] << 16);
}