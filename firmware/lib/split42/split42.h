#include <Arduino.h>
#include <cassert>
#include <initializer_list>
#include <stdint.h>
#include <Wire.h>

class KBHalf {
  private:
    uint8_t addr;

  public:
    uint8_t pinmap[24];
    uint8_t keymap[21];
    KBHalf(uint8_t addr, std::initializer_list<uint8_t> pinmap,
           std::initializer_list<uint8_t> keymap);

    void init();
    void write(uint8_t reg, uint8_t value, uint8_t len = 1);
    uint32_t get_state();
};