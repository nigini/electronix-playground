##
# SPDX-FileCopyrightText: 2022 ladyada for Adafruit Industries
# SPDX-License-Identifier: MIT
# Starter code from https://learn.adafruit.com/adafruit-neotrellis/circuitpython-code
##
import time
from board import SCL, SDA
import busio
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode
from adafruit_neotrellis.neotrellis import NeoTrellis
from adafruit_neotrellis.multitrellis import MultiTrellis

#create the i2c object for the trellis
i2c_bus = busio.I2C(SCL, SDA)
#USB keyboard
kbd = Keyboard(usb_hid.devices)

#create the trellis
trelli = [
    [NeoTrellis(i2c_bus, False, addr=0x2E), NeoTrellis(i2c_bus, False, addr=0x2F)],
    [NeoTrellis(i2c_bus, False, addr=0x30), NeoTrellis(i2c_bus, False, addr=0x31)]
]

trellis = MultiTrellis(trelli)

# some color definitions
OFF = (0, 0, 0)
RED = (255, 0, 0)
YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
COLORS = [
    PURPLE,
    CYAN,
    CYAN,
    CYAN,
    CYAN,
    CYAN,
    CYAN,
    GREEN
]

def get_off_key():
    return Keycode.X

def map_key(is_row, coord):
    map_to_alpha = ['A','B','C','D','E','F','G','H']
    map_to_num = ['ONE','TWO','THREE','FOUR','FIVE','SIX','SEVEN','EIGHT']
    if is_row:
        return Keycode.__dict__[map_to_alpha[coord]]
    else:
        return Keycode.__dict__[map_to_num[coord]]

def blink(col_coord, row_coord, edge):
    # Turn the LED on when a rising edge is detected
    if edge == NeoTrellis.EDGE_RISING:
        kbd.send(map_key(True, row_coord), map_key(False, col_coord))
        trellis.color(col_coord, row_coord, COLORS[row_coord])
        #trellis._trelli[row_coord][col_coord].brightness = 1.0/(col_coord+1)
    # Turn the LED off when a falling edge is detected
    elif edge == NeoTrellis.EDGE_FALLING:
        kbd.send(get_off_key(), map_key(True, row_coord), map_key(False, col_coord))
        trellis.color(col_coord, row_coord, OFF)

for row in range(8):
    for column in range(8):
        #activate rising edge events on all keys
        trellis.activate_key(column, row, NeoTrellis.EDGE_RISING)
        #activate falling edge events on all keys
        trellis.activate_key(column, row, NeoTrellis.EDGE_FALLING)
        #set all keys to trigger the blink callback
        trellis.set_callback(column, row, blink)

while True:
    #call the sync function call any triggered callbacks
    trellis.sync()
    #the trellis can only be read every 10 millisecons or so
    time.sleep(.02)
