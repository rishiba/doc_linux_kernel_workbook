MYPROC=myproc
obj-m += $(MYPROC).o

export KROOT=/lib/modules/$(shell uname -r)/build
#export KROOT=/lib/modules/$(uname)3.2.0-23-generic/build

allofit:  modules
modules:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules
modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean

clean: kernel_clean
	rm -rf   Module.symvers modules.order
	rm e_read_proc


insert: modules 
	sudo insmod myproc.ko

remove:
	sudo rmmod myproc
	sudo dmesg -c
        
test:
	gcc read_proc.c -o e_read_proc
	./e_read_proc
