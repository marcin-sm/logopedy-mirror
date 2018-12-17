import RPi.GPIO as GPIO
fan1 = 27
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(fan1,GPIO.OUT)
GPIO.output(fan1, 0)