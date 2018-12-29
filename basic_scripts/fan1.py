import RPi.GPIO as GPIO
import sys
fan1 = 27
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(fan1,GPIO.OUT)

if __name__ == "__main__":
    args =  sys.argv[1:]
    if (args[0])=='on':
        GPIO.output(fan1, 1)
    elif (args[0])=='off':
        GPIO.output(fan1, 0)
    else:
        print "unknown parameter"