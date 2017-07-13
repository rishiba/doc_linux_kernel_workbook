MODULE_FILENAME=mymodule

obj-m +=  $(MODULE_FILENAME).o
KO_FILE=$(MODULE_FILENAME).ko

export KROOT=/lib/modules/$(shell uname -r)/build

compile: clean
	@$(MAKE) -C $(KROOT) M=$(PWD) modules

modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install

clean: 
	@$(MAKE) -C $(KROOT) M=$(PWD) clean
	rm -rf   Module.symvers modules.order

insert: compile
	sudo insmod $(KO_FILE) param1=10 param2=20

remove:
	sudo rmmod $(MODULE_FILENAME)

printlog:
	sudo dmesg -c 
	sudo insmod $(KO_FILE)
	dmesg

output:
	sudo rmmod $(MODULE_FILENAME)
	sudo dmesg -c
	sudo insmod $(KO_FILE) param1=10 param2=20
	sudo dmesg -c

testsanity: clean compile insert remove

