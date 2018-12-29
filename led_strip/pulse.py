from __future__ import division
import time
import sys

# Import the WS2801 module.
import Adafruit_WS2801
import Adafruit_GPIO.SPI as SPI


# Configure the count of pixels:
PIXEL_COUNT = 9
SPI_PORT   = 0
SPI_DEVICE = 0
pixels = Adafruit_WS2801.WS2801Pixels(PIXEL_COUNT, spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))


def brightness_decrease(pixels, R, G, B, wait=0.0001, step=1):
    wait = (255-max(R, G, B)/max(R, G, B))/10000000
    for j in range(int(256 // step)):
        for i in range(pixels.count()):
            r, b, g = pixels.get_pixel_rgb(i)
            r = int(max(0, r - step))
            g = int(max(0, g - step))
            b = int(max(0, b - step))
            pixels.set_pixel(i, Adafruit_WS2801.RGB_to_color( r, b, g ))
        pixels.show()
        if wait > 0:
            time.sleep(wait)

def brightness_increase(pixels, R, G, B, wait=0.001, step=1):
    wait = (255-max(R, G, B)/max(R, G, B))/10000000
    for j in range(int(256 // step)):
        for i in range(pixels.count()):
            r, b, g = pixels.get_pixel_rgb(i)
            r = int(min(R, r + step))
            g = int(min(G, g + step))
            b = int(min(B, b + step))
            pixels.set_pixel(i, Adafruit_WS2801.RGB_to_color( r, b, g ))
        pixels.show()
        if wait > 0:
            time.sleep(wait)

# Clear all the pixels to turn them off.

def pulse (color, repeat, step):
    if color == "red": 
        R=85
        G=0 
        B=0
    elif color == "orange": 
        R=252
        G=215 
        B=0
    elif color == "green": 
        R=0
        G=255 
        B=0
    else:
        R=255
        G=255 
        B=255
    for x in range(repeat):
        brightness_increase(pixels, R, G, B, 0, step)
        brightness_decrease(pixels, R, G, B, 0, step)
    pixels.clear()

if __name__ == "__main__":
    args =  sys.argv[1:]
    pulse(args[0],2,2)

