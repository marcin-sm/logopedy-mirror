import RPi.GPIO as GPIO
import sys
relayTV = 20
GPIO.setmode(GPIO.BCM)
GPIO.setup(relayTV,GPIO.OUT)

def on ():
    GPIO.output(relayTV, 0)

def off ():
    GPIO.output(relayTV, 1)

if __name__ == "__main__":
    args =  sys.argv[1:]
    if (args[0])=='on':
        on()
    elif (args[0])=='off':
        off()
    else:
        print "unknown parameter"