import os
import time
import fan1
import fan2
import TV
from subprocess import PIPE, Popen

cpu = 0
gpu = 0

def measure_temp():
        global cpu
        global gpu
        tFile = open('/sys/class/thermal/thermal_zone0/temp')
        cpu = float(tFile.read())
        cpu = cpu/1000
        process = Popen(['vcgencmd', 'measure_temp'], stdout=PIPE)
        output, _error = process.communicate()
        return float(output[output.index('=') + 1:output.rindex("'")])


while True:
        gpu = measure_temp()
        temp = max(cpu,gpu)
        print('CPU: '+ str(cpu) + "'C" + "\t" + 'GPU: '+ str(gpu) + "'C" + "\t" + 'MAX: '+ str(temp) + "'C" )
        if (temp < 60.0):
            fan1.off()
            fan2.off()
        elif (temp >= 60.0 and temp < 65.00):
            fan1.on()
            fan2.off()
        elif (temp >= 65.0 and temp < 70.00):
            fan1.on()
            fan2.on()
        elif (temp >= 70.0):
            TV.off()
            fan1.on()
            fan2.on()
        time.sleep(1)