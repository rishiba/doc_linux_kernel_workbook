#! /bin/sh

for value in 1 2 3 4; do
	dmesg -c	
	echo $value > /proc/driver/my_mod
	dmesg
	echo "Press key to continue"
	read x
done	
