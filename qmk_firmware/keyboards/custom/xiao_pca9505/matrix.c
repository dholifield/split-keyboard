// #include "xiao_pca9505.h"
#include "i2c_master.h"
#include "quantum.h"

#define EXP_ADDR0 0x20
#define EXP_ADDR1 0x21
#define PORTS 3 // we read ports 0–2 = 24 bits each

extern const uint8_t keyPhysicalMap[42]; // declared in keymap.c

// pull in the QMK matrix arrays
extern matrix_row_t matrix_current[], matrix_previous[];

void matrix_init_custom(void) {
    // Initialize I2C on RP2040’s default SDA/SCL pins
    i2c_init_master();
    i2c_set_bitrate(400000);

    // Configure both PCA9505s: enable pull-ups & unmask interrupts
    for (uint8_t addr = EXP_ADDR0; addr <= EXP_ADDR1; addr++) {
        uint8_t cmd[1 + PORTS + 1 + PORTS] = {0x28 /*PU reg*/, /*..fill*/, 0x10 /*INT‑MASK*/, /*..fill*/};
        // build cmd: 0x28,0xFF×PORTS, 0x10,0x00×PORTS
        i2c_write_blocking(addr, cmd, 1 + PORTS, false);
        i2c_write_blocking(addr, cmd + 1 + PORTS, 1 + PORTS, false);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[], matrix_row_t previous_matrix[]) {
    uint8_t buf[PORTS];

    // read half 0
    i2c_read_blocking(EXP_ADDR0, 0x00, buf, PORTS, false);
    // read half 1
    i2c_read_blocking(EXP_ADDR1, 0x00, buf + PORTS, PORTS, false);

    // zero out the matrix
    for (int r = 0; r < MATRIX_ROWS; r++)
        current_matrix[r] = 0;

    // fill each “row” = one key
    for (int logical = 0; logical < MATRIX_ROWS; logical++) {
        uint8_t phys            = keyPhysicalMap[logical];
        uint8_t half            = phys / (PORTS * 8);
        uint8_t bit             = phys % 8;
        uint8_t port            = (phys % (PORTS * 8)) / 8;
        bool    pressed         = !(buf[half * PORTS + port] & (1 << bit));
        current_matrix[logical] = pressed ? 0x0001 : 0x0000;
    }

    // copy into QMK’s backing store (for matrix changed detection)
    for (int i = 0; i < MATRIX_ROWS; i++)
        previous_matrix[i] = current_matrix[i];
    return true;
}
