import board
import adafruit_74hc595
import digitalio
import time

latch_pin = digitalio.DigitalInOut(board.D5)
sr = adafruit_74hc595.ShiftRegister74HC595(board.SPI(), latch_pin)

test_led = digitalio.DigitalInOut(board.LED)
test_led.direction = digitalio.Direction.OUTPUT
pin0 = sr.get_pin(0)
pin1 = sr.get_pin(1)

while True:
    test_led.value = True
    pin0.value = True
    pin1.value = True
    time.sleep(1)
    test_led.value = False
    pin0.value = False
    pin1.value = False
    time.sleep(1)
