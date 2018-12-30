#!/bin/bash

cd /rpi-clock
#GEM_PATH=/home/pi/.rvm/gems/ruby-2.2.2@rpi-clock:/home/pi/.rvm/gems/ruby-2.2.2@global /home/pi/.rvm/rubies/ruby-2.2.2/bin/ruby app.rb &
ruby app.rb &
#sleep 30
midori -e Fullscreen -a http://localhost:4567