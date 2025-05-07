#include "PCA9505.h"
#include "Split.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <stdint.h>
#include <Wire.h>

constexpr uint8_t INT_PIN = 0;
constexpr uint8_t PORTS_PER_HALF = 3;
constexpr uint8_t KEYS_PER_HALF = 21;
constexpr uint8_t TOTAL_KEYS = KEYS_PER_HALF * 2;
constexpr uint8_t LAYER_COUNT = 3;
constexpr uint8_t DEBOUNCE_MS = 5;

constexpr uint8_t layerKeys[LAYER_COUNT] = {
    0xFF, // Base (unused)
    1,    // L1
    2     // L2
};

uint8_t rawPorts[2][PORTS_PER_HALF];
bool lastRaw[TOTAL_KEYS] = {0};
bool stableState[TOTAL_KEYS] = {0};
uint32_t lastChange[TOTAL_KEYS] = {0};
uint8_t currentLayer = 0;
uint8_t lastKC[TOTAL_KEYS] = {0};

// clang-format off
const uint8_t pinmap[TOTAL_KEYS] = {
    0,  1,  2,  3,  4,  5,      21, 22, 23, 24, 25, 26,
    6,  7,  8,  9,  10, 11,     27, 28, 29, 30, 31, 32,
    12, 13, 14, 15, 16, 17,     33, 34, 35, 36, 37, 38,
                18, 19, 20,     39, 40, 41,
};

const uint8_t keymap[LAYER_COUNT][TOTAL_KEYS] = {
  // ── Base ──────────────────────────────────────────
  { KEY_1,  KEY_2,  KEY_3,  KEY_4,  KEY_5,  KEY_6,      KEY_22, KEY_23, KEY_24, KEY_25, KEY_26, KEY_27,
    KEY_7,  KEY_8,  KEY_9,  KEY_10, KEY_11, KEY_12,     KEY_28, KEY_29, KEY_30, KEY_31, KEY_32, KEY_33,
    KEY_13, KEY_14, KEY_15, KEY_16, KEY_17, KEY_18,     KEY_34, KEY_35, KEY_36, KEY_37, KEY_38, KEY_39,
                            KEY_19, KEY_20, KEY_21,     KEY_40, KEY_41, KEY_42
  },
  // ── L1 ────────────────────────────────────────────
  { KEY_1,  KEY_2,  KEY_3,  KEY_4,  KEY_5,  KEY_6,      KEY_22, KEY_23, KEY_24, KEY_25, KEY_26, KEY_27,
    KEY_7,  KEY_8,  KEY_9,  KEY_10, KEY_11, KEY_12,     KEY_28, KEY_29, KEY_30, KEY_31, KEY_32, KEY_33,
    KEY_13, KEY_14, KEY_15, KEY_16, KEY_17, KEY_18,     KEY_34, KEY_35, KEY_36, KEY_37, KEY_38, KEY_39,
                            KEY_19, KEY_20, KEY_21,     KEY_40, KEY_41, KEY_42
  }
  // ── L2 ────────────────────────────────────────────
  { KEY_1,  KEY_2,  KEY_3,  KEY_4,  KEY_5,  KEY_6,      KEY_22, KEY_23, KEY_24, KEY_25, KEY_26, KEY_27,
    KEY_7,  KEY_8,  KEY_9,  KEY_10, KEY_11, KEY_12,     KEY_28, KEY_29, KEY_30, KEY_31, KEY_32, KEY_33,
    KEY_13, KEY_14, KEY_15, KEY_16, KEY_17, KEY_18,     KEY_34, KEY_35, KEY_36, KEY_37, KEY_38, KEY_39,
                            KEY_19, KEY_20, KEY_21,     KEY_40, KEY_41, KEY_42
  }
};
// clang-format on

bool interrupted = false;

PCA9505 left(0b000, Wire);
PCA9505 right(0b001, Wire);

void setup() {
    left.begin(SDA, SCL);
    right.begin(SDA, SCL);
    attachInterrupt(digitalPinToInterrupt(INT_PIN), interrupt, LOW);
}

void loop() {}

void interrupt() { interrupted = true; }