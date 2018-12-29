import sys
import os
import random
from time import sleep

sys.path.append('/home/pi/black-mirror/led_strip/')
import pulse

def good():
    number = random.randint(1,7)
    #print(number)
    os.system("omxplayer -o hdmi /home/pi/Music/logopedy/yes/{0}.mp3 &".format(number))
    pulse.pulse('green',3,2)
    time.sleep(3)
    os.system("killall omxplayer.bin")
    os.system("kill $(pgrep omxplayer)")
    sys.exit()

def bad():
    number = random.randint(1,7)
    #print(number)
    os.system("omxplayer -o hdmi /home/pi/Music/logopedy/no/{0}.mp3 &".format(number))
    pulse.pulse('red',4,2)
    time.sleep(3)
    os.system("killall omxplayer.bin")
    os.system("kill $(pgrep omxplayer)")
    sys.exit()


if __name__ == "__main__":
    args =  sys.argv[1:]
    if (args[0])=='good':
        good()
    elif (args[0])=='bad':
        bad()
    else:
        print "unknown parameter"