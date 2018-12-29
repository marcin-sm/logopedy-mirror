import RPi.GPIO as GPIO
import sys
fan2 = 22
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(fan2,GPIO.OUT)

def on():
    GPIO.output(fan2, 1)

def off():
    GPIO.output(fan2, 0)

if __name__ == "__main__":
    args =  sys.argv[1:]
    if (args[0])=='on':
        on()
    elif (args[0])=='off':
        off()
    else:
        print "unknown parameter"