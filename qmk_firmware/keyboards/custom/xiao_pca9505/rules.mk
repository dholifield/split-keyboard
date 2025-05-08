MCU = rp2040
PLATFORM = rp2040
BOARD = seeed_xiao_rp2040      # uses the existing Seeed XIAO RP2040 board dfn
F_CPU = 133333333

MATRIX_CUSTOM_DRIVER = yes     # we’ll write matrix_init_custom + matrix_scan_custom
DEBOUNCE = 5
