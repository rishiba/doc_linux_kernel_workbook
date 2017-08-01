#! /bin/sh
PROC_ENTRY="/proc/driver/mmmod"


# Check if the file is present or not.
if [ -f "/proc/driver/mmmod" ]; then 
	echo "The file $PROC_ENTRY is present"
fi



# Check if add is working or not.

dmesg -c 

for i in `seq 1 100` ; do 
	echo "add $i" > $PROC_ENTRY
done

dmesg

read

# Check if display is working or not

dmesg -c 
echo "print" > $PROC_ENTRY
dmesg 

read

# Check if delete is working or not

dmesg -c 

echo "delete 5"> $PROC_ENTRY

dmesg 

read

