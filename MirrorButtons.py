import RPi.GPIO as GPIO
import time
import os
from time import sleep

GPIO.setmode(GPIO.BCM)

buttonR = 23
buttonL = 24
relayTV = 20
relayBulbs = 16

GPIO.setup(buttonL,GPIO.IN,pull_up_down=GPIO.PUD_UP)
GPIO.setup(buttonR,GPIO.IN,pull_up_down=GPIO.PUD_UP)

GPIO.setup(relayTV,GPIO.OUT)
GPIO.setup(relayBulbs,GPIO.OUT)

stateTV = 1
stateBulbs = 1
stateScreen = 0
stateSpecial= 0

GPIO.output(relayTV, stateTV)
GPIO.output(relayBulbs, stateBulbs)
os.system("vcgencmd display_power 1")

GPIO.add_event_detect(buttonR, GPIO.BOTH, bouncetime=1000)  # add both edge detection on a channel
GPIO.add_event_detect(buttonL, GPIO.BOTH, bouncetime=1000)  #for both buttons
GPIO.setwarnings(False)


#GPIO.remove_event_detect(buttonL)
#GPIO.remove_event_detect(buttonR)

def leftPress():
    GPIO.remove_event_detect(buttonL)
    now = time.time()
    count=1
    GPIO.add_event_detect(buttonL, GPIO.BOTH)
    while time.time() < now + 1: # 0.5 second period
        if GPIO.event_detected(buttonL):
           count +=1
           time.sleep(.25) # debounce time

    if count == 1:
        GPIO.remove_event_detect(buttonL)
        print "buttonL pressed " + str(count) + " times"
        toggleScreen()
        GPIO.add_event_detect(buttonL, GPIO.BOTH, bouncetime=1000)

    if count == 2:
        GPIO.remove_event_detect(buttonL)
        print "buttonL pressed " + str(count) + " times"
        special()
        GPIO.add_event_detect(buttonL, GPIO.BOTH, bouncetime=1000)		
    
    if count == 3:
        GPIO.remove_event_detect(buttonL)       
        print "buttonL pressed " + str(count) + " times"
        toggleTV()
        GPIO.add_event_detect(buttonL, GPIO.BOTH, bouncetime=1000)

def rightPress():
    GPIO.remove_event_detect(buttonR)
    GPIO.remove_event_detect(buttonL)
    global stateBulbs
    if stateBulbs == 1:
        stateBulbs = 0
        GPIO.output(relayBulbs, stateBulbs)
        print "Bulbs: " + str(stateBulbs)
        time.sleep(0.1)
    elif stateBulbs == 0:
        stateBulbs = 1
        GPIO.output(relayBulbs, stateBulbs)
        print "Bulbs: " + str(stateBulbs)
        time.sleep(0.1)
    time.sleep(0.1)    
    GPIO.add_event_detect(buttonR, GPIO.BOTH, bouncetime=1000)
    GPIO.add_event_detect(buttonL, GPIO.BOTH, bouncetime=1000)

def toggleTV():
    GPIO.remove_event_detect(buttonR)
    GPIO.remove_event_detect(buttonL)
    global stateTV
    if stateTV == 1:
        stateTV = 0
        GPIO.output(relayTV, stateTV)
        print "TV: " + str(not stateTV)
        time.sleep(0.1)
    elif stateTV == 0:
        stateTV = 1
        GPIO.output(relayTV, stateTV)
        print "TV: " + str(not stateTV)
        time.sleep(0.1)
    time.sleep(0.1)
    GPIO.add_event_detect(buttonR, GPIO.BOTH, bouncetime=1000)
	
def toggleScreen():

    global stateScreen
    if stateScreen == 1:
        stateScreen = 0
        os.system("xset -display :0 dpms force off")
        print "Screen: " + str(stateScreen)
        time.sleep(0.1)
    elif stateScreen == 0:
        stateScreen = 1
        os.system("xset -display :0 dpms force on")
        print "Screen: " + str(stateScreen)
        time.sleep(0.1)
    time.sleep(0.1)	
	
def special():
    global stateSpecial
    if stateSpecial == 1:
        stateSpecial = 0
        os.system("python rgb_off.py")
        print "special: " + str(stateSpecial)
        time.sleep(0.1)
    elif stateSpecial == 0:
        stateSpecial = 1
        os.system("python rgb.py")
        print "special: " + str(stateSpecial)
        time.sleep(0.1)
    time.sleep(0.1)

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

