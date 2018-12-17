import RPi.GPIO as GPIO
import sys
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
args = [float(x) for x in sys.argv[1:]]
pwm = GPIO.PWM(18, 1000)
pwm.start(0)
pwm.ChangeDutyCycle(args)