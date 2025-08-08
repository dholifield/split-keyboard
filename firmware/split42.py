from kmk.scanners import Scanner
from keypad import Event as KeyEvent

class split42(Scanner):
    def __init__(self, i2c, interrupt, l_addr, r_addr, banks, pin_map):
        super().__init__()
        self.i2c = i2c
        self.interrupt = interrupt
        self.l_addr = l_addr
        self.r_addr = r_addr
        self.banks = banks
        self.pin_map = pin_map
        self._key_count = len(pin_map)
        
        self.interval = 0.01

        self.prev = 0
        self.buffer = []
        
        while not i2c.try_lock():
            pass
        try:
            # set polarity, set inputs, enable interrupts
            for reg, val in [(0x10, 0xFF), (0x18, 0xFF), (0x20, 0x00)]:
                data = bytes([reg | 0x80] + [val] * 5)
                    
                i2c.writeto(l_addr, data)
                i2c.writeto(r_addr, data)
                
            # read to clear interrupt
            buf = bytearray(5)
            self.i2c.writeto_then_readfrom(self.l_addr, bytes([0x80]), buf)
            self.i2c.writeto_then_readfrom(self.r_addr, bytes([0x80]), buf)
        finally:
            i2c.unlock()
    # end __init__
        
    @property
    def key_count(self):
        return self._key_count
    # end key_count

    def scan_for_changes(self):
        if (self.interrupt.value == 1) and (not self.buffer): return None
        
        while not self.i2c.try_lock():
            pass
        try:
            l_data = bytearray(5)
            r_data = bytearray(5)
            self.i2c.writeto_then_readfrom(self.l_addr, bytes([0x80]), l_data)
            self.i2c.writeto_then_readfrom(self.r_addr, bytes([0x80]), r_data)
        finally:
            self.i2c.unlock()

        l_data = [l_data[bank] for bank in self.banks]
        r_data = [r_data[bank] for bank in self.banks]

        data = bytes(l_data + r_data)
        state = int.from_bytes(data, 'big')
        
        pressed = state & ~self.prev
        released = ~state & self.prev
        self.prev = state

        for idx, pin in enumerate(self.pin_map):
            if bool(pressed & (1 << pin)):
                self.buffer.append(KeyEvent(idx, True))
            elif bool(released & (1 << pin)):
                self.buffer.append(KeyEvent(idx, False))

        if self.buffer:        
            return self.buffer.pop(0)
        return None
    # end scan_for_changes