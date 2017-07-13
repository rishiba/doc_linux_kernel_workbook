##################
Kernel Compilation
##################

============
Introduction
============

At first we will learn how to compile a kernel. This is just a series of steps we need to do in
order to compile and boot to a new kernel.

Why this chapter
================

This chapter will give you your first hands on with Linux Kernel - thus
enabling you understand some fundamental concepts around it.

You compile the kernel - make changes to the kernel right in the first chapter.
So your exicting journey with Linux kernel begins.

What will you learn
===================

You will learn 

*   How to download a Linux kernel.
*   How to configure the Linux kernel in differnent ways.
*   How to see the effects of the configuration changes you did.
*   Compile a Linux kernel.
*   Package a compiled kernel.
*   Install a Linux kernel.
*   Boot from a new Linux kernel.
*   Making only a module in the kernel.

Prerequisites
=============

*   We expect that you have already installed a Linux system and have some basic understanding of Linux terminal.

============
Linux Kernel
============

*   This is simple code written in ``C``.
*   This is a **LARGE** ``C`` program.
*   Code looks difficult to understand because of the LARGENESS of the system and lack of understanding of the operating system concepts.
*   You have to be little more careful while coding as small mistakes can cause the whole system to crash. Debugging these can be diffcult at times.

==================
Kernel Compilation
==================

*   We may need to compile our own kernel to add/remove some features present in the system.
*   The kernel distributed with **general settings** setting which should run on all the possible installations.
*   Thus they need to support a wide range of hardware.
*   Some of the features may be built in the kernel while some of them may be built as modules.
*   It's alright if they are built as module as they don't increase the size of the kernel.
*   Built-in features will increase the size of kernel, thus effecting the system's performance. (not too heavily)
*   Making our own kernel will ensure the kernel is having appropriate set of features.
*   Double check before you **remove** any feature, your freshly compiled kernel may not boot :-).
*   Read ``Linux Kernel In A Nutshell`` for further understanding.

.. _install_linux_kernel-label:

Compiling a Kernel - Steps
===========================
* www.kernel.org - download the new kernel from this website.
* :command:`tar -xzf/xjf downloaded kernel`
* :command:`make oldconfig` - makes the old configuration present in the system, if new features are present asks about them.
* :command:`make defconfig` - makes the default configuration for your architecture, the configuration file is present in ``arch/ARCHITECTURE/configs/``.
* :command:`make gconfig` - gives a GTK based configuration menu. (We will not use this in this book.)
* :command:`make menuconfig` - gives a ncurses based configuration menu.
* :command:`make modules` - makes the modules.
* :command:`make modules_install` - installs the modules to the required loaction usually ``/lib/modules/KERNEL-VERSION/kernel``.
* :command:`make install` - installs the kernel in the required location usually ``/boot/``, makes the initial ramfs sets up the boot loader, you are now ready to reboot your system.

Hands-On Compling a Kernel
==========================

*   Let us see the current kernel version on the system

::

    rishi@rishi-VirtualBox:~$ uname -a 
    Linux rishi-VirtualBox 4.4.0-24-generic #43-Ubuntu SMP Wed Jun 8 19:27:37 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux


*   First download the kernel. We will use the 4.7 kernel for it.

::

    wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.7.tar.xz 
    --2016-07-28 08:38:14--  https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.7.tar.xz
    Resolving cdn.kernel.org (cdn.kernel.org)... 151.101.8.69
    Connecting to cdn.kernel.org (cdn.kernel.org)|151.101.8.69|:443... connected.
    HTTP request sent, awaiting response... 200 OK
    Length: 90412100 (86M) [application/x-xz]
    Saving to: ‘linux-4.7.tar.xz’

    100%[================================================================================>]
    9,04,12,100  225KB/s   in 4m 23s 

    2016-07-28 08:42:39 (336 KB/s) - ‘linux-4.7.tar.xz’ saved [90412100/90412100]

*   Copy the kernel to your virtual machine. Here replace the IP with your machine's IP. You can directly download the kernel in your virtual machine as well.

::
    
    [08:42 - ] -------- /home/rishi/code  
    [rishi-office 7] > scp linux-4.7.tar.xz rishi@192.168.0.106:
    linux-4.7.tar.xz
    100%   86MB  86.2MB/s   00:01    
    [08:47 - ] -------- /home/rishi/code  
    [rishi-office 8] > 

*   Untar the kernel

::

    $ tar -xf linux-4.7.tar.xz

*   This will give you a folder.

::
    
    $ ls
    linux-4.7  linux-4.7.tar.xz

*  This folder has thousands of files. Lets do a ``find`` and count the number of files.

::
    
    rishi@rishi-VirtualBox:~/lkw$ find linux-4.7/| wc -l 
    58057

*   This folder has a lot of folders. See the following tree command.

::

    $ tree linux-4.7  -L 1 -f 
    linux-4.7
    |__ linux-4.7/arch
    |__ linux-4.7/block
    |__ linux-4.7/certs
    |__ linux-4.7/COPYING
    |__ linux-4.7/CREDITS
    |__ linux-4.7/crypto
    |__ linux-4.7/Documentation
    |__ linux-4.7/drivers
    |__ linux-4.7/firmware
    |__ linux-4.7/fs
    |__ linux-4.7/include
    |__ linux-4.7/init
    |__ linux-4.7/ipc
    |__ linux-4.7/Kbuild
    |__ linux-4.7/Kconfig
    |__ linux-4.7/kernel
    |__ linux-4.7/lib
    |__ linux-4.7/MAINTAINERS
    |__ linux-4.7/Makefile
    |__ linux-4.7/mm
    |__ linux-4.7/net
    |__ linux-4.7/README
    |__ linux-4.7/REPORTING-BUGS
    |__ linux-4.7/samples
    |__ linux-4.7/scripts
    |__ linux-4.7/security
    |__ linux-4.7/sound
    |__ linux-4.7/tools
    |__ linux-4.7/usr
    |__ linux-4.7/virt

*   This folder has a ``Makefile`` which is the ``Makefile`` to compile the kernel. The file is very long, but you need not bother about it. We are interested only in few targets.

::

    $ wc -l  Makefile 
    1669 Makefile

*   We will now do the steps mentioned above. Right now the folder has no ``.config`` file. When we configure the kernel for compilation the file get created. The ``.config`` file keep the configuration for the kernel to be built. Whatever configuration changes you do while configuring the kernel, it gets saved in this file.

::
    
    $ ls .config 
    ls: cannot access '.config': No such file or directory

*   Here is a small snippet of the configuration file which we will generate in sometime.

::

    $ tail -f .config
    CONFIG_UCS2_STRING=y
    CONFIG_FONT_SUPPORT=y
    # CONFIG_FONTS is not set
    CONFIG_FONT_8x8=y
    CONFIG_FONT_8x16=y
    # CONFIG_SG_SPLIT is not set
    CONFIG_SG_POOL=y
    CONFIG_ARCH_HAS_SG_CHAIN=y
    CONFIG_ARCH_HAS_PMEM_API=y
    CONFIG_ARCH_HAS_MMIO_FLUSH=y
    

*   ``make defconfig`` - makes the default configuration for your architecture, the configuration file is present in ``arch/ARCHITECTURE/configs/``.

::

    $ make defconfig 
    *** Default configuration is based on 'x86_64_defconfig'
    #
    # configuration written to .config
    #
    
    rishi@rishi-VirtualBox:~/lkw/linux-4.7$ ls .config 
    .config

*   The config file is very long. See this.

::

    $ wc -l .config 
    4044 .config


*   ``make oldconfig`` will read the config file ``(/boot/config-4.4.0-24-generic)`` in your machine and try to use that configuration
    file. There might be some features in the new kernel which is not available in the older/default
    kernel you have. For this the command takes input from you. Based on the features you want to enable
    and disable - you can give the inputs.

::

    $ make oldconfig 
    scripts/kconfig/conf  --oldconfig Kconfig
    #
    # using defaults found in /boot/config-4.4.0-24-generic
    #
    /boot/config-4.4.0-24-generic:1631:warning: symbol value 'm' invalid
        for RXKAD

    /boot/config-4.4.0-24-generic:3589:warning: symbol value 'm' invalid 
        for SERIAL_8250_FINTEK
    *
    * Restart config...
    *
    *
    * General setup
    *
    *
    * Timers subsystem
    *
    Timer tick handling
      1. Periodic timer ticks (constant rate, no dynticks) (HZ_PERIODIC)
    > 2. Idle dynticks system (tickless idle) (NO_HZ_IDLE)
      3. Full dynticks system (tickless) (NO_HZ_FULL)
    choice[1-3]: 2
    Old Idle dynticks config (NO_HZ) [Y/n/?] y
    High Resolution Timer Support (HIGH_RES_TIMERS) [Y/n/?] y
    *
    * CPU/Task time and stats accounting
    *
    Cputime accounting
    > 1. Simple tick based cputime accounting (TICK_CPU_ACCOUNTING)
      2. Full dynticks CPU time accounting (VIRT_CPU_ACCOUNTING_GEN)
      3. Fine granularity task level IRQ time accounting (IRQ_TIME_ACCOUNTING)
    choice[1-3]: 1
    BSD Process Accounting (BSD_PROCESS_ACCT) [Y/n/?] y
      BSD Process Accounting version 3 file format (BSD_PROCESS_ACCT_V3) [Y/n/?] y
    Export task/process statistics through netlink (TASKSTATS) [Y/?] y
      Enable per-task delay accounting (TASK_DELAY_ACCT) [Y/?] y
      Enable extended accounting over taskstats (TASK_XACCT) [Y/n/?] y
        Enable per-task storage I/O accounting (TASK_IO_ACCOUNTING) [Y/n/?] y
    *
    * RCU Subsystem
    *
    Make expert-level adjustments to RCU configuration (RCU_EXPERT) [N/y/?] n
    Kernel .config support (IKCONFIG) [N/m/y/?] n
    Kernel log buffer size (16 => 64KB, 17 => 128KB) (LOG_BUF_SHIFT) [18] 18
    CPU kernel log buffer size contribution (13 => 8 KB, 17 => 128KB) (LOG_CPU_MAX_BUF_SHIFT) [12] 12
    Temporary per-CPU NMI log buffer size (12 => 4KB, 13 => 8KB) (NMI_LOG_BUF_SHIFT) [13] (NEW) 

    -----------SNIPPED------------
    #
    # configuration written to .config
    #

*   You can see the difference in the default config file and the currently generated ``.config``
    file by the ``diff`` command.

::

    $ diff /boot/config-4.4.0-24-generic .config  | more
    3c3
    < # Linux/x86_64 4.4.0-24-generic Kernel Configuration
    ---
    > # Linux/x86 4.7.0 Kernel Configuration
    9d8
    < CONFIG_PERF_EVENTS_INTEL_UNCORE=y
    14d12
    < CONFIG_HAVE_LATENCYTOP_SUPPORT=y
    15a14,17
    > CONFIG_ARCH_MMAP_RND_BITS_MIN=28
    > CONFIG_ARCH_MMAP_RND_BITS_MAX=32
    > CONFIG_ARCH_MMAP_RND_COMPAT_BITS_MIN=8
    > CONFIG_ARCH_MMAP_RND_COMPAT_BITS_MAX=16
    42a45
    > CONFIG_DEBUG_RODATA=y
    69d71
    < CONFIG_VERSION_SIGNATURE="Ubuntu 4.4.0-24.43-generic 4.4.10"
    97d98
    < # CONFIG_IRQ_FORCED_THREADING_DEFAULT is not set
    145a147
    > CONFIG_NMI_LOG_BUF_SHIFT=13
    153,159d154
    < # CONFIG_CGROUP_DEBUG is not set
    < CONFIG_CGROUP_FREEZER=y
    < CONFIG_CGROUP_PIDS=y
    < CONFIG_CGROUP_DEVICE=y
    < CONFIG_CPUSETS=y
    < CONFIG_PROC_PID_CPUSET=y
    < CONFIG_CGROUP_CPUACCT=y
    164,166c159,161
    < CONFIG_MEMCG_KMEM=y
    < CONFIG_CGROUP_HUGETLB=y
    < CONFIG_CGROUP_PERF=y
    ---


* ``make gconfig`` - gives a GTK based configuration menu. In my system there is no gtk based libraries available hence the window did not start.

::

    rishi@rishi-VirtualBox:~/lkw/linux-4.7$ make gconfig 
    *
    * Unable to find the GTK+ installation. Please make sure that
    * the GTK+ 2.0 development package is correctly installed...
    * You need gtk+-2.0, glib-2.0 and libglade-2.0.
    *
    make[1]: *** No rule to make target 'scripts/kconfig/.tmp_gtkcheck', needed by
    'scripts/kconfig/gconf.o'.  Stop.
    Makefile:544: recipe for target 'gconfig' failed
    make: *** [gconfig] Error 2
    

* ``make menuconfig`` - gives a ncurses based configuration menu. We will use this for configuring our new kernel. **This will initially fail as there is not ncurses installed.**

::

    $ make menuconfig 
      HOSTCC  scripts/kconfig/mconf.o
      In file included from scripts/kconfig/mconf.c:23:0:
      scripts/kconfig/lxdialog/dialog.h:38:20: fatal error: curses.h: No such file or directory
      compilation terminated.
      scripts/Makefile.host:108: recipe for target 'scripts/kconfig/mconf.o' failed
      make[1]: *** [scripts/kconfig/mconf.o] Error 1
      Makefile:544: recipe for target 'menuconfig' failed
      make: *** [menuconfig] Error 2

*   We will now install ncurses.

::

    $ sudo apt-get install ncurses-dev
    [sudo] password for rishi: 
    Reading package lists... Done
    Building dependency tree       
    Reading state information... Done
    Note, selecting 'libncurses5-dev' instead of 'ncurses-dev'
    The following additional packages will be installed:
      libtinfo-dev
    Suggested packages:
      ncurses-doc
    The following NEW packages will be installed:
      libncurses5-dev libtinfo-dev
    0 upgraded, 2 newly installed, 0 to remove and 306 not upgraded.
    Need to get 252 kB of archives.
    After this operation, 1,461 kB of additional disk space will be used.
    Do you want to continue? [Y/n] y
    Get:1 http://in.archive.ubuntu.com/ubuntu xenial/main amd64 libtinfo-dev amd64 6.0+20160213-1ubuntu1 [77.4 kB]
    Get:2 http://in.archive.ubuntu.com/ubuntu xenial/main amd64 libncurses5-dev amd64 6.0+20160213-1ubuntu1 [175 kB]
    Fetched 252 kB in 0s (255 kB/s)          
    Selecting previously unselected package libtinfo-dev:amd64.
    (Reading database ... 209625 files and directories currently installed.)
    Preparing to unpack .../libtinfo-dev_6.0+20160213-1ubuntu1_amd64.deb ...
    Unpacking libtinfo-dev:amd64 (6.0+20160213-1ubuntu1) ...
    Selecting previously unselected package libncurses5-dev:amd64.
    Preparing to unpack .../libncurses5-dev_6.0+20160213-1ubuntu1_amd64.deb ...
    Unpacking libncurses5-dev:amd64 (6.0+20160213-1ubuntu1) ...
    Processing triggers for man-db (2.7.5-1) ...
    Setting up libtinfo-dev:amd64 (6.0+20160213-1ubuntu1) ...
    Setting up libncurses5-dev:amd64 (6.0+20160213-1ubuntu1) ...
    rishi@rishi-VirtualBox:~/lkw/linux-4.7$ 

*   Now when we run ``make menuconfig`` we will get the following on terminal and a ncurses based screen will open.

::

    $ make menuconfig 
    HOSTCC  scripts/kconfig/mconf.o
    HOSTCC  scripts/kconfig/zconf.tab.o
    HOSTCC  scripts/kconfig/lxdialog/checklist.o
    HOSTCC  scripts/kconfig/lxdialog/util.o
    HOSTCC  scripts/kconfig/lxdialog/inputbox.o
    HOSTCC  scripts/kconfig/lxdialog/textbox.o
    HOSTCC  scripts/kconfig/lxdialog/yesno.o
    HOSTCC  scripts/kconfig/lxdialog/menubox.o
    HOSTLD  scripts/kconfig/mconf
    scripts/kconfig/mconf  Kconfig

.. image:: images/02_kernel_compilation/01_make_menuconfig.png 

*   We will now configure our kernel. 

*   We will add EXT2 and EXT3 as kernel modules. We will then compare the default config file and the
    currently generated config file to see the effect of the changes. We will also remove the VFAT
    support and add the NTFS support to the kernel image directly. There is no particular reason for
    doing all this. All this is intended to teach you how the configuration of kernel works and what are
    the effect of it. Once the kernel boots we will see how these changes effect the booted kernel.

We will now do some configuration changes to the new kernel which we will just compile and
configure.

* Goto - File systems -> 
   mark ``Ext2`` as module i.e. ``M``  use spacebar to toggle between the possible values
   mark ``Ext3`` as a built into images i.e. ``*``

.. image:: images/02_kernel_compilation/02_ext2_ext3.png

* Goto - File Systems -> DOS/NT Filesystem 
      remove VFAT support i.e. ``BLANK``
      add NTFS module support i.e. ``M``

.. image:: images/02_kernel_compilation/03_ntfs_fat.png

* Go back using ``<esc> <esc>``

* Save the configuration, you will get a ``.config`` file in your directory.


*   There a ton of features which are configurable. You should just go inside some of them and see what is available and what are the configuration option. Do it !!

* Let us see the difference in the current config of the system and the config file which is generated by us. We are insterested in seeing the entries which must have been modified because of us, hence we are ``grep-ing`` those.

::

    $ diff -y /boot/config-4.4.0-24-generic .config | grep -a "EXT2\|EXT3\|VFAT\|NTFS" 

    # CONFIG_EXT2_FS is not set                               | CONFIG_EXT2_FS=m
    # CONFIG_EXT3_FS is not set                               | # CONFIG_EXT2_FS_XATTR is not set
                                                              > CONFIG_EXT3_FS=m
                                                              > # CONFIG_EXT3_FS_POSIX_ACL is not set
                                                              > # CONFIG_EXT3_FS_SECURITY is not set
    CONFIG_EXT4_USE_FOR_EXT2=y                                <
    CONFIG_MSDOS_FS=m                                         | # CONFIG_VFAT_FS is not set
    CONFIG_VFAT_FS=y                                          | CONFIG_NTFS_FS=y
    CONFIG_FAT_DEFAULT_CODEPAGE=437                                   | CONFIG_NTFS_DEBUG=y
    CONFIG_FAT_DEFAULT_IOCHARSET="iso8859-1"                  | CONFIG_NTFS_RW=y
    CONFIG_NTFS_FS=m                                          <
    # CONFIG_NTFS_DEBUG is not set                            <
    # CONFIG_NTFS_RW is not set                               <


* Let us see the difference between the default configuration file of the kernel and our configuration file.

::

    $ diff -y .config ./arch/x86/configs/x86_64_defconfig | grep -i "EXT2\|EXT3\|NTFS\|VFAT"
    # CONFIG_EXT2_FS is not set                   <
    # CONFIG_EXT3_FS is not set                   <
    CONFIG_EXT4_USE_FOR_EXT2=y                    <
    CONFIG_VFAT_FS=y                        CONFIG_VFAT_FS=y
    # CONFIG_NTFS_FS is not set         


*   So we have now configured the kernel. Mostly we have changed some of the file system related settings and not made much changes. We will now start with the compilation.    

*   ``make -j 4`` - this will start the compilation of the linux kernel. ``-j`` option runs the ``make`` in a multithreaded fashion. ``4`` here stands for the number of threads. For selecting the number of threads you can see the number of cores in your virtual machine. The file ``/proc/cpuinfo`` has the information about cpus. Generally its a good idea to have 2 threads per cpu. i.e for a 2 cpu machine have 4 threads. You can keep more threads per cpu.

*   Errors I faced - this was due to the openssl library missing from the system. It can be installed by the command ``sudo apt-get install libssl-dev``. Install the package and restart the compilation process.

::

    $ make -j 4 

    scripts/kconfig/conf  --silentoldconfig Kconfig
      SYSHDR  arch/x86/entry/syscalls/../../include/generated/asm/unistd_32_ia32.h
      SYSTBL  arch/x86/entry/syscalls/../../include/generated/asm/syscalls_32.h
      CHK     include/config/kernel.release
      SYSHDR  arch/x86/entry/syscalls/../../include/generated/asm/unistd_64_x32.h

      >>>>>>>> SNIPPED <<<<<<<<<<<<<
      
      HOSTCC  scripts/selinux/genheaders/genheaders
      HOSTCC  scripts/selinux/mdp/mdp
      HOSTCC  scripts/kallsyms
      HOSTLD  scripts/mod/modpost
      HOSTCC  scripts/conmakehash
      HOSTCC  scripts/recordmcount
      HOSTCC  scripts/sortextable
      HOSTCC  scripts/asn1_compiler
      HOSTCC  scripts/sign-file


    scripts/sign-file.c:25:30: fatal error: openssl/opensslv.h: No such file or directory
    
    
    
    compilation terminated.
    scripts/Makefile.host:91: recipe for target 'scripts/sign-file' failed
    make[1]: *** [scripts/sign-file] Error 1
    make[1]: *** Waiting for unfinished jobs....
    Makefile:558: recipe for target 'scripts' failed
    make: *** [scripts] Error 2
    make: *** Waiting for unfinished jobs....
    make: *** wait: No child processes.  Stop.


*   I started with ``make -j 4`` and saw that the processor is still underutilised. Hence I started the 16 threads with ``time`` command to see the time taken.

::
    
    $ time make -j 16

* ``make modules`` - compiles the modules - this step is not required. 
*  ``make modules_installs`` - installs (copies) the modules to the required loaction usually ``/lib/modules/KERNEL-VERSION/kernel``.
*  ``make install`` - installs the kernel in the required location usually ``/boot/``, makes the initial ramfs sets up the boot loader, you are now ready to reboot your system.

*   If everything goes fine then your kernel will install properly.


==========
BootLoader
==========

*   Let us do some settings in grub so that we can see some of the changes.
*   Open the file ``/etc/default/grub`` and change the ``GRUB_TIMEOUT`` to 60

::

    $ head /etc/default/grub
    # If you change this file, run 'update-grub' afterwards to update
    # /boot/grub/grub.cfg.
    # For full documentation of the options in this file, see:
    #   info -f grub -n 'Simple configuration'

    GRUB_DEFAULT=-1
    GRUB_HIDDEN_TIMEOUT=
    GRUB_HIDDEN_TIMEOUT_QUIET=true
    GRUB_TIMEOUT=60 
    GRUB_DISTRIBUTOR=`lsb_release -i -s 2> /dev/null || echo Debian`


*   This will ensure that the boot menu waits for 60 seconds before it goes to the default selection.
*   Let us check the entries using the ``grub-customizer`` tool. Run the following command and then start the ``grub-customizer``

::

    sudo add-apt-repository ppa:danielrichter2007/grub-customizer
    sudo apt-get update
    sudo apt-get install grub-customizer

Reference for this http://askubuntu.com/questions/532238/how-do-i-customize-the-grub-2-menu

*   When I run the tool I can see the following

.. image:: images/02_kernel_compilation/04_grub_customizer.png

*   Do not make any changes, just observe that there are new entries for the 4.7 kernel.

*   Now let us reboot the system. Following screen will come.

.. image:: images/02_kernel_compilation/05_boot_prompt.png

*   When you go to the ``Advanced options for Ubuntu`` you can see the following screen. Here you can choose which kernel to boot manually. There are settings in ``grub`` which can enable you in making the default kernel as you want.

.. image:: images/02_kernel_compilation/06_select_kernel.png

*   When your new kernel boots up run the command ``uname -a`` to see the current kernel version.

::

    $ uname -a 
    Linux rishi-VirtualBox 4.7.0 #1 SMP Sat Aug 20 09:41:02 IST 2016 x86_64 x86_64 x86_64 GNU/Linux

*   It shows that we are into our new kernel. Congratulations !!!

=======================
Files Of The New Kernel
=======================

.. todo:: Write this section about important files.

* Let us see some of the important files of the newly installed kernel.

*   /boot/initrd.img-4.7.0
*   /boot/System.map-4.7.0
*   /boot/vmlinuz-4.7.0
*   /boot/config-4.7.0

::

    diff /boot/config-4.7.0 ~/lkw/linux-4.7/.config

*   ``/lib/modules/4.7.0/``


*   Symlink


::

    ls /lib/modules/4.7.0/build -l
    lrwxrwxrwx 1 root root 25 Aug 20 09:43 /lib/modules/4.7.0/build -> /home/rishi/lkw/linux-4.7

*   /lib/modules/4.7.0/modules.dep
*   /lib/modules/4.7.0/modules.order
*   /lib/modules/4.7.0/source

============================
Module Loading and Unloading
============================

*   We had configured the system to have ext2 file system as a module. So the linux system should not show that it supports the file system unless the module is loaded. Right?

*   Let us check this fact by listing the supported file systems. ``cat`` the file ``/proc/filesystems``

::

    rishi@rishi-VirtualBox:~$ cat /proc/filesystems 
    nodev   sysfs
    nodev   rootfs
    nodev   ramfs
    nodev   bdev
    nodev   proc
    nodev   cpuset
    nodev   cgroup
    nodev   cgroup2
    nodev   tmpfs
    nodev   devtmpfs
    nodev   binfmt_misc
    nodev   debugfs
    nodev   tracefs
    nodev   sockfs
    nodev   pipefs
    nodev   hugetlbfs
    nodev   rpc_pipefs
    nodev   devpts
            ext3
            ext4
            iso9660
    nodev   nfs
    nodev   nfs4
    nodev   autofs
    nodev   mqueue
    nodev   selinuxfs

.. note:: We will use some commands like ``modprobe`` ``insmod`` ``lsmod`` ``rmmod``. Do not worry if you are unable to understand these. In the next chapters I will detail them.

*   Let us load the ``ext2`` file system in the kernel and see what happens. We can do this by the ``modprobe`` command. ``modprobe`` is an intelligent tool which knows the exact locations of the modules and it can load them from there. We should do it as ``sudo`` as we need the ``root`` priviledges. The other tool to insert modules is ``insmod``.


::
    
    rishi@rishi-VirtualBox:~$ sudo modprobe ext2
    [sudo] password for rishi: 

*   We can check if the module got loaded by running the ``lsmod`` command. The second column of the ``lsmod`` command is the usage count. Right now there is no ext2 filesystem which is mounted hence the usage count is ``0``.

::
    
    rishi@rishi-VirtualBox:~$ lsmod | grep ext2 
    ext2                   50017  0

*   We should now be supporing the ``ext2`` file system as well. See the last line. You can see the ``ext2`` file system being supported.

::

    rishi@rishi-VirtualBox:~$ cat /proc/filesystems 
    nodev   sysfs
    nodev   rootfs
    nodev   ramfs
    nodev   bdev
    nodev   proc
    nodev   cpuset
    nodev   cgroup
    nodev   cgroup2
    nodev   tmpfs
    nodev   devtmpfs
    nodev   binfmt_misc
    nodev   debugfs
    nodev   tracefs
    nodev   sockfs
    nodev   pipefs
    nodev   hugetlbfs
    nodev   rpc_pipefs
    nodev   devpts
            ext3
            ext4
            iso9660
    nodev   nfs
    nodev   nfs4
    nodev   autofs
    nodev   mqueue
    nodev   selinuxfs
            ext2

*   Let us now remove the ``ext2`` module. Use the command ``rmmod``.

::

    rishi@rishi-VirtualBox:~$ sudo rmmod ext2 


*   Now there will be no entry in ``lsmod`` for the ``ext2`` file system.

===========================================
Automatic Loading of modules when required.
===========================================

*   We will now ``mount`` a file system of type ``ext2`` and we will see that the module gets loaded automaticllay.

*   First let us see the currently mounted file systems.

::

    rishi@rishi-VirtualBox:~$ mount 
    sysfs on /sys type sysfs (rw,nosuid,nodev,noexec,relatime)
    proc on /proc type proc (rw,nosuid,nodev,noexec,relatime)
    udev on /dev type devtmpfs (rw,nosuid,relatime,size=1042368k,nr_inodes=260592,mode=755)
    devpts on /dev/pts type devpts (rw,nosuid,noexec,relatime,gid=5,mode=620,ptmxmode=000)
    tmpfs on /run type tmpfs (rw,nosuid,noexec,relatime,size=209632k,mode=755)
    /dev/sda1 on / type ext4 (rw,relatime,errors=remount-ro,data=ordered)
    selinuxfs on /sys/fs/selinux type selinuxfs (rw,relatime)
    tmpfs on /dev/shm type tmpfs (rw,nosuid,nodev)
    tmpfs on /run/lock type tmpfs (rw,nosuid,nodev,noexec,relatime,size=5120k)
    tmpfs on /sys/fs/cgroup type tmpfs (ro,nosuid,nodev,noexec,mode=755)
    cgroup on /sys/fs/cgroup/systemd type cgroup (rw,nosuid,nodev,noexec,relatime,xattr,release_agent=/lib/systemd/systemd-cgroups-agent,name=systemd)
    cgroup on /sys/fs/cgroup/freezer type cgroup (rw,nosuid,nodev,noexec,relatime,freezer)
    cgroup on /sys/fs/cgroup/cpu,cpuacct type cgroup (rw,nosuid,nodev,noexec,relatime,cpu,cpuacct)
    cgroup on /sys/fs/cgroup/cpuset type cgroup (rw,nosuid,nodev,noexec,relatime,cpuset)
    systemd-1 on /proc/sys/fs/binfmt_misc type autofs (rw,relatime,fd=34,pgrp=1,timeout=0,minproto=5,maxproto=5,direct)
    mqueue on /dev/mqueue type mqueue (rw,relatime)
    hugetlbfs on /dev/hugepages type hugetlbfs (rw,relatime)
    debugfs on /sys/kernel/debug type debugfs (rw,relatime)
    tmpfs on /run/user/108 type tmpfs (rw,nosuid,nodev,relatime,size=209632k,mode=700,uid=108,gid=114)
    tmpfs on /run/user/1000 type tmpfs (rw,nosuid,nodev,relatime,size=209632k,mode=700,uid=1000,gid=1000)

*   Now let us create a file which we will use as a disk for making an ``ext2`` partition.

*   ``dd`` command will help us in this. We will make a 100MB file. Here ``if`` is the input file name. ``/dev/zero`` is a device which gives zeros when it is read. Read more about it. ``of`` is the output filename. ``bs`` is the blocksize and ``count`` is the number of blocks we want it to write. ``bs*count`` is the size of the file made.

::

    rishi@rishi-VirtualBox:~$ dd if=/dev/zero of=100mb bs=1M count=100
    100+0 records in
    100+0 records out
    104857600 bytes (105 MB, 100 MiB) copied, 0.0596335 s, 1.8 GB/s


*   Let us make a file system now.

::
    
    rishi@rishi-VirtualBox:~$ mkfs.ext2 100mb 
    mke2fs 1.42.13 (17-May-2015)
    Discarding device blocks: done                            
    Creating filesystem with 102400 1k blocks and 25688 inodes
    Filesystem UUID: acc67a5c-572f-4e83-b0cc-f9a53cbb9f0f
    Superblock backups stored on blocks: 
        8193, 24577, 40961, 57345, 73729

    Allocating group tables: done                            
    Writing inode tables: done                            
    Writing superblocks and filesystem accounting information: done 

*   Associate it with a ``loop`` device. Loop devices are fake devices which allow regular files to be used as block devices. Read about them in ``man losetup``. 

::

    rishi@rishi-VirtualBox:~$ sudo losetup /dev/loop0 100mb 



*   Current status of ``ext2`` module

*   Mounting the ``ext2`` filesystem we just made.

::

    rishi@rishi-VirtualBox:~$ sudo mount /dev/loop0 /mnt 

*   Now the state of ``ext2`` module. The usage count is 1 here.

::
    
    rishi@rishi-VirtualBox:~$ lsmod | grep ext2 
    ext2                   50017  1

*   Status of ``mount`` command.

::

    rishi@rishi-VirtualBox:~$ mount | grep ext2
    /dev/loop0 on /mnt type ext2 (rw,relatime,errors=continue)


*   Status of ``/proc/filesystems``

::
    
    rishi@rishi-VirtualBox:~$ cat /proc/filesystems 
    nodev   sysfs
    nodev   rootfs
    nodev   ramfs
    nodev   bdev
    nodev   proc
    nodev   cpuset
    nodev   cgroup
    nodev   cgroup2
    nodev   tmpfs
    nodev   devtmpfs
    nodev   binfmt_misc
    nodev   debugfs
    nodev   tracefs
    nodev   sockfs
    nodev   pipefs
    nodev   hugetlbfs
    nodev   rpc_pipefs
    nodev   devpts
            ext3
            ext4
            iso9660
    nodev   nfs
    nodev   nfs4
    nodev   autofs
    nodev   mqueue
    nodev   selinuxfs
            ext2

*   Unmounting the file system.

::

    rishi@rishi-VirtualBox:~$ sudo umount /mnt 


*   The module does not get unloaded by itself. Its usage count gets to 0 though.

::
    
    rishi@rishi-VirtualBox:~$ lsmod | grep ext2
    ext2                   50017  0


*   We can now remove it ourselves.

::
    
    rishi@rishi-VirtualBox:~$ sudo rmmod  ext2

*   We can check the supported file systems again. There is not ``ext2``

::

    rishi@rishi-VirtualBox:~$ cat /proc/filesystems 
    nodev   sysfs
    nodev   rootfs
    nodev   ramfs
    nodev   bdev
    nodev   proc
    nodev   cpuset
    nodev   cgroup
    nodev   cgroup2
    nodev   tmpfs
    nodev   devtmpfs
    nodev   binfmt_misc
    nodev   debugfs
    nodev   tracefs
    nodev   sockfs
    nodev   pipefs
    nodev   hugetlbfs
    nodev   rpc_pipefs
    nodev   devpts
            ext3
            ext4
            iso9660
    nodev   nfs
    nodev   nfs4
    nodev   autofs
    nodev   mqueue
    nodev   selinuxfs
    
=========
Exercises
=========

*   Build the XFS file system in the kernel. See the effect in the file ``/proc/filesystems``
*   Build the ``reiserfs`` file system as module. See the effect in the file ``/proc/filesystems``. See the new ``.config`` file which got generated.
*   Make some files and associate them with different loop devices. Mount them, do some operations.

==========
References
==========

*   The Design Of Unix Operating System.
*   ``man`` pages are the best references you will find for Linux. Read the ``man`` pages for ``dd``, ``mkfs.ext2``, ``mount``, ``modprobe``. Do not worry about understanding them end to end, just read it. We will detail them in coming chapters or documents.
