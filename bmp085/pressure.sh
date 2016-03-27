#!/bin/bash

filename=/home/pi/weather/weather.txt

#echo 17 > /sys/class/gpio/export
#echo out | sudo tee /sys/class/gpio/gpio17/direction


#while [ 1 ] ; 
#do 

d=$(date "+%Y-%m-%d %H:%M:%S")



while [ 1 ] 
do

	h=$(/home/pi/src/AM2302/AM2302 | cut -f2)

	if [[ "$h" != "Parity bit error" ]] 
	then 
		break;
	fi

	sleep 1
done


to=$(cat /sys/bus/w1/devices/28-0115a36a70ff/w1_slave | grep t | sed 's/^.*t=//')
tout=$(echo "scale=2; $to/1000" | bc)


${BASH_SOURCE%/*}/bmp085 | while IFS=$'\t' read -r p t 
	do  
		echo -e "$d\t$p\t$t\t$h\t$tout\t"  
#		d=$(date "+%Y-%m-%d %H:%M:%S")
		echo -e "$d\t$p\t$t\t$h\t$tout" >> $filename


#t1=$(echo "$tout < 0.0"| bc)

#if [ "$t1" = "1" ]
#then
#	echo "ON"
#	echo 1 > /sys/class/gpio/gpio17/value
#else
#	echo  "OFF"
#	echo 0 > /sys/class/gpio/gpio17/value
#fi
done

#done

