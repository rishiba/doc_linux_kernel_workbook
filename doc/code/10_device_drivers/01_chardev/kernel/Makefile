# Makefile to compile chardev.c
# Also this Makefile is used to learn writing Makefiles

CC = gcc

# We have two types of kernel code.
# 1. Which are staticly compiled in the kernel.
# 	For this type we use the string "obj-y". Note the "y" used here.
# 2. Which gets compiled as a module.
# 	For this type we use the string "obj-m". Note the "m" used here.
# So we basically use variables here to specify the value "y" or "m".
# I am using variacle CONFIG_CHARDEV to specify it.
# 
CONFIG_CHARDEV = m
MODULE_NAME = chardev
obj-m += chardev.o
#obj-m += chardev.o
#obj-$(CONFIG_CHARDEV) += chardev.o

# obj-m += chardev.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	ctags -R

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf tags

