import RPi.GPIO as GPIO
import sys
fan1 = 27
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(fan1,GPIO.OUT)

def on():
    GPIO.output(fan1, 1)

def off():
    GPIO.output(fan1, 0)

if __name__ == "__main__":
    args =  sys.argv[1:]
    if (args[0])=='on':
        on()
    elif (args[0])=='off':
        off()
    else:
        print "unknown parameter"