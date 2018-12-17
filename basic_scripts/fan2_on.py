import RPi.GPIO as GPIO
fan2 = 22
GPIO.setmode(GPIO.BCM)
GPIO.setup(fan2,GPIO.OUT)
GPIO.output(fan2, 1)