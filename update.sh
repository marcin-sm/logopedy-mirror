git fetch
git reset --hard origin/master

./arduino --board esp8266:esp8266:d1_mini:CpuFrequency=80,FlashSize=4M1M --port /dev/ttyUSB0 --upload /home/pi/black-mirror/esp_logic/esp_logic.ino