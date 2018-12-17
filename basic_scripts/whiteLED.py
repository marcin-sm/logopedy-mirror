import RPi.GPIO as GPIO
import os
import sys
import time

args =  sys.argv[1:]
num = float(args[0])
num = int(num*10.24)
os.system("gpio -g mode 18 pwm")
os.system("gpio -g pwm 18 "+str(num))