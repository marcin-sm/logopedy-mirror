import RPi.GPIO as GPIO
relayTV = 20
GPIO.setmode(GPIO.BCM)
GPIO.setup(relayTV,GPIO.OUT)
GPIO.output(relayTV, 1)