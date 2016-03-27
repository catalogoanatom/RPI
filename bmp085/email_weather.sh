#!/bin/bash

# Alexey Martynov 2016-02-11
# send weather to emails

receivers="alexey.martynov@gmail.com, verao.martynova@gmail.com"

d=$(date "+%Y-%m-%d %H:%M:%S")

header=$(echo -e "Date       Time   \tPress\tTin(C)\tH(%)\tTout(C)")
table=$(tail -n6  /home/pi/weather/weather.txt)
echo -e "$header\n$table"| mutt -s "weather $d" $receivers 
