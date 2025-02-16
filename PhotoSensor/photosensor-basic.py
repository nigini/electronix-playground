from machine import Pin
import machine
led = Pin(25, Pin.OUT)
sensor = machine.ADC(28)

while True:
     reading = sensor.read_u16()
     if reading < 1000:
         led.value(1)
     else:
         led.value(0)
