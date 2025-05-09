#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

#define INPUT_REG 0x00
#define OUTPUT_REG 0x08
#define POLARITY_REG 0x10
#define CONFIG_REG 0x18
#define INTERRUPT_REG 0x20
#define AI_ON 0x80 // auto-increment

class PCA9505 {
  private:
    uint8_t _addr;
    TwoWire& _wire;
    uint8_t _ports;

  public:
    uint64_t last_read = 0x00;

    PCA9505(uint8_t a, TwoWire& wire = Wire, uint8_t ports)
        : _addr(0x20 | a), _wire(wire), _ports(ports > 5 ? 5 : ports) {}

    void begin(uint8_t sda_pin, uint8_t scl_pin) {
        _wire.begin(sda_pin, scl_pin);
        send_data(CONFIG_REG, 0xFF);    // Set all pins to input
        send_data(POLARITY_REG, 0x00);  // Set all pins to normal polarity
        send_data(INTERRUPT_REG, 0x00); // Enable interrupts
    }

    void send_data(uint8_t reg, uint8_t data) {
        _wire.beginTransmission(_addr);
        _wire.write(reg | AI_ON);
        for (uint8_t i = 0; i < _ports; i++) {
            _wire.write(data);
        }
        _wire.endTransmission();
    }

    uint64_t read() {
        uint64_t mask = 0;

        _wire.beginTransmission(_addr);
        _wire.write((uint8_t)INPUT_REG);
        _wire.endTransmission(false);
        _wire.requestFrom(_addr, _ports);

        for (uint8_t i = 0; i < _ports; i++) {
            mask |= ((uint64_t)_wire.read() << (i * 8));
        }

        return mask;
    }
};