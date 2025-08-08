from split42 import split42
import board
import busio
from digitalio import DigitalInOut
from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.modules.layers import Layers
from kmk.extensions.rgb import RGB
from kmk.extensions.media_keys import MediaKeys

keyboard = KMKKeyboard()

# class LayerRGB(RGB):
#     def on_layer_change(self, layer):
#         if layer <= 2: # normal
#             self.set_hsv_fill(0, 0, self.val_default)
#         if layer == 3: # gaming
#             self.set_hsv_fill(0, self.sat_default, self.val_default)
#         if layer == 4: # CAD
#             self.set_hsv_fill(170, self.sat_default, self.val_default)
# 
# rgb = LayerRGB(pixel_pin=board.LED, num_pixels=1, rgb_order=(0, 1, 2), hue_default=0, sat_default=255, val_default=5)
# keyboard.extensions.append(rgb)
# 
# class RGBLayers(Layers):
#     def activate_layer(self, keyboard, layer, idx=None):
#         super().activate_layer(keyboard, layer, idx)
#         rgb.on_layer_change(layer)
# 
#     def deactivate_layer(self, keyboard, layer):
#         super().deactivate_layer(keyboard, layer)
#         rgb.on_layer_change(keyboard.active_layers[0])

# keyboard.modules.append(RGBLayers())
keyboard.modules.append(Layers())
keyboard.modules.append(MediaKeys())

L1SPC = KC.LT(1, KC.SPACE, tap_time=200)
L2BSPC = KC.LT(2, KC.BSPC, tap_time=200)
L1ENT = KC.LT(1, KC.ENT, tap_time=200)

WS1 = KC.LGUI(KC.N1)
WS2 = KC.LGUI(KC.N2)
WS3 = KC.LGUI(KC.N3)
WS4 = KC.LGUI(KC.N4)
WS5 = KC.LGUI(KC.N5)
WS6 = KC.LGUI(KC.N6)
WS7 = KC.LGUI(KC.N7)
WS8 = KC.LGUI(KC.N8)

keyboard.keymap = [
    # base
    [
        KC.TAB,  KC.Q,    KC.W,    KC.E,    KC.R,    KC.T,       KC.Y,    KC.U,    KC.I,    KC.O,    KC.P,    KC.MINS,
        KC.ESC,  KC.A,    KC.S,    KC.D,    KC.F,    KC.G,       KC.H,    KC.J,    KC.K,    KC.L,    KC.SCLN, KC.EQL,
        KC.LALT, KC.Z,    KC.X,    KC.C,    KC.V,    KC.B,       KC.N,    KC.M,    KC.COMM, KC.DOT,  KC.SLSH, KC.DEL,
                                   KC.LCTL, KC.LSFT, KC.LGUI,    L2BSPC,  L1SPC,   KC.ENT
    ],
    # upper
    [
        KC.GRV,  KC.N1,   KC.N2,   KC.N3,   KC.N4,   KC.N5,      KC.N6,   KC.N7,   KC.N8,   KC.N9,   KC.N0,   KC.NO,
        KC.NO,   WS1,     WS2,     WS3,     WS4,     KC.NO,      KC.LEFT, KC.DOWN, KC.UP,   KC.RGHT, KC.QUOT, KC.NO,
        KC.TRNS, KC.FD(0),KC.FD(3),KC.FD(4),KC.FD(5),KC.NO,      KC.NO,   KC.NO,   KC.LBRC, KC.RBRC, KC.BSLS, KC.NO,
                                   KC.TRNS, KC.TRNS, KC.TRNS,    KC.NO,   KC.NO,   KC.NO
    ],
    # lower
    [
        KC.NO,   KC.F1,   KC.F2,   KC.F3,   KC.F4,   KC.F5,      KC.F6,   KC.F7,   KC.F8,   KC.F9,   KC.F10,  KC.F11,
        KC.CAPS, WS5,     WS6,     WS7,     WS8,     KC.NO,      KC.HOME, KC.PGDN, KC.PGUP, KC.END,  KC.NO,   KC.F12,
        KC.TRNS, KC.NO,   KC.NO,   KC.NO,   KC.NO,   KC.NO,      KC.MRWD, KC.VOLD, KC.VOLU, KC.MFFD, KC.EJCT, KC.NO,
                                   KC.TRNS, KC.TRNS, KC.TRNS,    KC.NO,   KC.NO,   KC.NO
    ],
    # gaming
    [
        KC.TAB,  KC.N1,   KC.N2,   KC.N3,   KC.N4,   KC.T,       KC.Y,    KC.U,    KC.I ,   KC.O,    KC.P,    KC.F7,
        KC.ESC,  KC.LSFT, KC.A,    KC.W,    KC.D,    KC.R,       KC.H,    KC.J,    KC.K,    KC.L,    KC.F5,   KC.F6,
        KC.Q,    KC.Z,    KC.X,    KC.S,    KC.V,    KC.B,       KC.N,    KC.M,    KC.F1,   KC.F2,   KC.F3,   KC.F4,
                                   KC.LCTL, KC.SPC,  KC.E,       KC.NO,   KC.FD(0),KC.NO
    ],
    # CAD
    [
        KC.TAB,  KC.Q,    KC.W,    KC.E,    KC.R,    KC.T,       KC.Y,    KC.U,    KC.I,    KC.O,    KC.P,    KC.MINS,
        KC.ESC,  KC.A,    KC.S,    KC.D,    KC.F,    KC.G,       KC.H,    KC.J,    KC.K,    KC.L,    KC.SCLN, KC.EQL,
        KC.DEL,  KC.Z,    KC.X,    KC.C,    KC.V,    KC.B,       KC.N,    KC.M,    KC.COMM, KC.DOT,  KC.SLSH, KC.DEL,
                                   KC.LCTL, KC.LSFT, L1ENT,      L2BSPC,  L1SPC,   KC.LGUI
    ],
    # colemak dh
    [
        KC.TAB,  KC.Q,    KC.W,    KC.F,    KC.P,    KC.B,       KC.J,    KC.L,    KC.U,    KC.Y,    KC.SCLN, KC.MINS,
        KC.ESC,  KC.A,    KC.R,    KC.S,    KC.T,    KC.G,       KC.M,    KC.N,    KC.E,    KC.I,    KC.O,    KC.EQL,
        KC.LALT, KC.Z,    KC.X,    KC.C,    KC.D,    KC.V,       KC.K,    KC.H,    KC.COMM, KC.DOT,  KC.SLSH, KC.DEL,
                                   KC.LCTL, KC.LSFT, KC.LGUI,    L2BSPC,  L1SPC,   KC.ENT
    ]
]

i2c = busio.I2C(board.SCL, board.SDA, frequency=100_000)
interrupt = DigitalInOut(board.D3)
while not i2c.try_lock():
    pass
i2c.unlock()

pinmap = (
    43, 31, 28, 27, 24, 38,        14,  0,  3,  4,  7, 19,
    42, 44, 29, 26, 39, 37,        13, 15,  2,  5, 20, 18,
    41, 40, 30, 25, 35, 36,        12, 11,  1,  6, 16, 17,
                45, 46, 47,        23, 22, 21)

scanner = split42(i2c, interrupt, 0x24, 0x20, (0, 3, 4), pinmap)

keyboard.matrix = scanner

if __name__ == '__main__':
    keyboard.go()
