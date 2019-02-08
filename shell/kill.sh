sudo XAUTHORITY=/home/pi/.Xauthority DISPLAY=:0.0 xset dpms force off
ps -ef|grep omxplayer | grep -v grep|awk '{print "kill -9 "$2}' |sh
python /home/pi/black-mirror/led_strip/rgb_off.py
killall python
sudo XAUTHORITY=/home/pi/.Xauthority DISPLAY=:0.0 xset dpms force off