##############
Device Drivers
##############

* A device driver or software driver is a computer program allowing higher- level computer programs to interact with a hardware device.
* Translator between a hardware device and the applications or operating systems
* Drivers are hardware-dependent and operating-system-specific.
* They usually provide the interrupt handling required for any necessary asynchronous time-dependent

Device Drivers Types
--------------------
* Character Device Drivers
* Operate on characters as basic unit of input and output
* Accessed in sequential and non-random manner
* Block Device Driver
* Serves blocks of data
* Random access as required by file systems

copy_to_user(), copy_from_user()
--------------------------------
* Macros to copy data from user space and copy data to kernel space.

Character Device driver and ioctls
----------------------------------

``file``: chardev.c
~~~~~~~~~~~~~~~~~~~
.. literalinclude:: code/10_device_drivers/01_chardev/kernel/chardev.c
    :language: c
    :linenos:

``file``: Makefile
~~~~~~~~~~~~~~~~~~
.. literalinclude:: code/10_device_drivers/01_chardev/kernel/Makefile
    :language: c
    :linenos:

``file``: ioctl.c
~~~~~~~~~~~~~~~~~
.. literalinclude:: code/10_device_drivers/01_chardev/user/ioctl.c
    :language: c
    :linenos:

Steps:
~~~~~~

* ``insmod chardev.ko``
* ``cat /proc/devices | grep sav_dev`` - to get the major number of the device, for example 250.
* ``mknod  /dev/mydev c 250 0``
* ``ls -l /dev/mydev``
