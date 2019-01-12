import RPi.GPIO as GPIO
import time
import os
GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def my_callback(self):
    if GPIO.input(4): 
        print 'DOOR OPENED !'
        os.system("omxplayer -o hdmi /home/pi/Music/logopedy/open.mp3 &")
    elif not GPIO.input(4): 
        print 'DOOR CLOSED !'
        os.system("omxplayer -o hdmi /home/pi/Music/logopedy/close.mp3 &")
    GPIO.remove_event_detect(4)
    time.sleep(1)
    GPIO.add_event_detect(4, GPIO.RISING, callback=my_callback, bouncetime=1000)
	

GPIO.add_event_detect(4, GPIO.RISING, callback=my_callback, bouncetime=1000)
	
GPIO.add_event_callback(4, my_callback)

while True:
    time.sleep(0.0001)

