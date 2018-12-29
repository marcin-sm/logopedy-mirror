import os
import time
import fan1
import fan2
import TV

def measure_temp():
        temp = os.popen("vcgencmd measure_temp").readline()
        return (temp.replace("temp=",""))
fake = 50

while True:
        print(measure_temp())
        time.sleep(1)
        if (fake < 60.0):
            fan1.off()
            fan2.off()
        elif (fake >= 60.0 and fake < 65.00):
            fan1.on()
            fan2.off()
        elif (fake >= 65.0 and fake < 70.00):
            fan1.on()
            fan2.on()
        elif (fake >= 70.0):
            TV.off()
            fan1.on()
            fan2.on()