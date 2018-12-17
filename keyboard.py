import keyboard #Using module keyboard
import os
while True:#making a loop
    try: #used try so that if user pressed other than the given key error will not be shown
        if keyboard.is_pressed('q'):#if key 'q' is pressed 
            print('You Pressed A Key!')
            os.system("python /home/pi/black-mirror/basic_scripts/fan1_on.py")
            break#finishing the loop
        else:
            pass
    except:
        break #if user pressed a key other than the given key the loop will break