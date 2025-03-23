import board
import adafruit_74hc595
import digitalio
import time
import displayio
import rgbmatrix

shifterLAT = digitalio.DigitalInOut(board.D5)
shifter = adafruit_74hc595.ShiftRegister74HC595(board.SPI(), shifterLAT)

red1 = shifter.get_pin(1)
blue1 = shifter.get_pin(2)
green1 = shifter.get_pin(3)
red2 = shifter.get_pin(4)
blue2 = shifter.get_pin(5)
green2 = shifter.get_pin(6)

pinA = board.A4
pinB = board.A2
pinC = board.A3
pinD = board.A1

LAT = board.D10
OE = board.D12
CLK = board.D11

displayio.release_displays()
matrix = rgbmatrix.RGBMatrix(
    width=32, height=32, bit_depth=1,
    rgb_pins=[red1, green1, blue1, red1, green1, blue1],
    addr_pins=[pinA, pinB, pinC, pinD],
    clock_pin=CLK, latch_pin=LAT, output_enable_pin=OE)
