#!/bin/sh
echo -e -n "\r" > /proc/LCDI2C
while [ 1 ];
do
	echo -e -n "\t" > /proc/LCDI2C
	date | awk '{print $4}' > /proc/LCDI2C
	sleep 1
done

