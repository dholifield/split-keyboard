#pragma once

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define MANUFACTURER YourName
#define PRODUCT Xiao RP2040 Split PCA9505
#define DESCRIPTION     “Split keyboard on one XIAO + 2x PCA9505”

#define MATRIX_ROWS 42 // e.g. 21 keys×2 halves
#define MATRIX_COLS 1

#define DIODE_DIRECTION ROW2COL // doesn’t matter, we’re custom
#define MATRIX_HAS_GHOST        // suppress unused warnings

#define UNICODE_SELECTED_MODES UC_LNX

// no “split” defines here — single controller
