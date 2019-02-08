import os
import sys
import RPi.GPIO as GPIO
import time
from time import sleep
sys.path.append('/home/pi/Videos/logopedy/')
file = 'cw_'+'4'+'.mp4'

buttonR = 23
buttonL = 24

exercise = 0

#"The sum of 1 + 2 is {0}".format(1+2)

def rightPress():
    global exercise
    exercise += 1
    if exercise > 10: exercise = 1
    os.system("killall omxplayer.bin")
    os.system("omxplayer --loop -o hdmi /home/pi/Videos/logopedy/cw_{0}.mp4 &".format(exercise))
    print 'right: '+str(exercise)

def leftPress():
    global exercise
    exercise -= 1
    if exercise <= 0: exercise = 1
    os.system("killall omxplayer.bin")
    os.system("omxplayer --loop -o hdmi /home/pi/Videos/logopedy/cw_{0}.mp4 &".format(exercise))
    print 'left: '+str(exercise)

#def start():
while True:
    start = time.time()
    if GPIO.event_detected(buttonR):
        #time.sleep(.01)
        #print('buttonR pressed')
        rightPress()
    if GPIO.event_detected(buttonL):
        #time.sleep(.01)
        leftPress()
    if time.time() - start > 5:
       continue
    time.sleep(0.0001)
    

#if __name__ == '__main__':
#    # test1.py executed as script
#    # do something
#    start()