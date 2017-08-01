
obj-m +=  ll_module.o
obj-m +=  ll_proc.o
obj-m +=  ll.o
obj-m += ll_driver.o
ll_driver-objs := ll_module.o ll_proc.o ll.o

export KROOT=/lib/modules/$(shell uname -r)/build
#export KROOT=/lib/modules/$(uname)3.2.0-23-generic/build

allofit:  modules

modules: clean

	@$(MAKE) -C $(KROOT) M=$(PWD) modules

modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install

kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean

clean: kernel_clean
	rm -rf   Module.symvers modules.order

insert: modules 
	sudo dmesg -c
	sudo insmod ll_driver.ko

remove: clean
	sudo rmmod ll_driver.ko

        
