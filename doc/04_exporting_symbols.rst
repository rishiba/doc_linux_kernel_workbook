#############
EXPORT_SYMBOL
#############

============
Introduction
============

Generally the modules will never live alone. We need to divide the code into
multiple modules for better organization and readability as well as we need to
use the APIs or functionality which is available in other modules or the
functions which are made available to us by the Linux Kernel.

Here in this chapter we will see how to make our functions available to other
modules. In latter chapters we will use some functionality given by the other
modules or the kernel code.

Why this chapter
================

We need to understand how to

*   For making a function available for others to use.
*   How to use functions given by other modules.

What will you learn
===================

*   Exporting an API to an external module.
*   Using API given by the other module.
*   Using library functions available in kernel.

Prerequisites
=============

Previous chapters.

=============
Export Symbol
=============

*   ``EXPORT_SYMBOL()`` helps you provide APIs to other modules/code.

*   The functions which you EXPORT are available to the other modules/code.

*   Your module will not load if the its expecting a symbol(variable/function) and its not present in the kernel.

*   ``modprobe`` helps here and loads the modules which is needed by your module.

*   What if there is circular dependency between the modules?

=============================================
Module Exporting Some Functions and Variables
=============================================

Introduction
============

*   Here we will write two modules. In one module we will have the functions
    which will be exported using the ``EXPORT_SYMBOL()`` whereas the other
    module will just call the functions and use the variables which are exported.

*   We will then see the details of the module by seeing the ``modinfo
    command``. See the ``depends`` field of the output. In ``mymodule1.ko`` you
    will see that it depends on ``mymodule1``.

``FILE: mymodule1.c``
=====================

.. literalinclude:: code/04_exporting_symbols/exporting_symbols/mymodule1.c
    :language: c
    :linenos:

``FILE: mymodule2.c``
=====================

.. literalinclude:: code/04_exporting_symbols/exporting_symbols/mymodule2.c
    :language: c
    :linenos:

``FILE: Makefile``
==================

.. literalinclude:: code/04_exporting_symbols/exporting_symbols/Makefile
    :language: make
    :linenos:


*   Let us see what ``modinfo`` tells about our modules. Before this compile the modules.

::

    $ modinfo mymodule1.ko
    filename:       /home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/mymodule1.ko
    license:        GPL v2
    author:         Rishi Agrawal <rishi.b.agrawal@gmail.com
    description:    Module to demonstrate the EXPORT_SYMBOL functionality
    depends:
    vermagic:       4.7.0 SMP mod_unload

    $ modinfo mymodule2.ko
    filename:       /home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/mymodule2.ko
    license:        GPL v2
    author:         Rishi Agrawal <rishi.b.agrawal@gmail.com>
    description:    Module to demonstrate the EXPORT_SYMBOL functionality
    depends:        mymodule1    <<<<<<<<<<<<<<<
    vermagic:       4.7.0 SMP mod_unload

*   Let us try to insert the ``mymodule2.ko`` before the ``mymodule1.ko``. It will give errors.

::

    $ sudo insmod mymodule2.ko
    insmod: ERROR: could not insert module mymodule2.ko: Unknown symbol in module

    rishi@rishi-VirtualBox:~/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols$ dmesg
    [15588.009164] mymodule2: Unknown symbol add_two_numbers (err 0)
    [15588.009171] mymodule2: Unknown symbol GLOBAL_VARIABLE (err 0)
    [15588.009176] mymodule2: Unknown symbol print_hello (err 0)

*   Now insert the ``mymodule1.ko``

::

    $ sudo insmod mymodule1.ko

*   Now insert the ``mymodule2.ko``

::

    $ sudo insmod mymodule2.ko
    [15606.692155] Hello from Export Symbol 1 module.
    [15612.175760] Hello from Hello Module
    [15612.175764] Hello Friend!!!
    [15612.175766] Hello Friend!!!
    [15612.175767] Hello Friend!!!
    [15612.175769] Hello Friend!!!
    [15612.175770] Hello Friend!!!
    [15612.175772] Hello Friend!!!
    [15612.175773] Hello Friend!!!
    [15612.175775] Hello Friend!!!
    [15612.175776] Hello Friend!!!
    [15612.175778] Hello Friend!!!
    [15612.175780] Sum of the numbers 11
    [15612.175782] Value of GLOBAL_VARIABLE 1000

*   ``SUCESSS !!`` You have successfully inserted a module which uses functions from another module.

====================
Removing the modules
====================

*   You cannot remove a module which is in use.

::

    $ sudo rmmod mymodule1
    rmmod: ERROR: Module mymodule1 is in use by: mymodule2

*   Check who is using the ``mymodule1``. See the ``Used by`` column in the ``lsmod`` output.

::

    $ lsmod
    Module                  Size  Used by
    mymodule2               1056  0
    mymodule1               1324  1 mymodule2

*   We will have to remove the ``mymodule2`` first and ``mymodule1``.

::

     $ sudo rmmod mymodule2
     $ sudo rmmod mymodule1

===========
Other files
===========

*   See the ``Module.order`` file. It has the order in which the modules should be loaded.

::

    $ cat modules.order
    kernel//home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/mymodule1.ko
    kernel//home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/mymodule2.ko

*   See the ``Module.symvers`` file. It shows the symbols which are exported.

::

    $ cat Module.symvers
    0x00000000  print_hello /home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/mymodule1    EXPORT_SYMBOL
    0x00000000  add_two_numbers /home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/mymodule1    EXPORT_SYMBOL
    0x00000000  GLOBAL_VARIABLE /home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/mymodule1    EXPORT_SYMBOL


========================
See the exported symbols
========================

*   Module1 exports the symbols.

*   The exported symbols and other functions in the kernel can be seen in the ``/proc/kallsyms`` file.  Its is a huge file.

*   Let us see the difference in the file after inserting the ``mymodule1.ko``.

*   That file clearly that the functions ``print_hello()`` and others are from ``mymodule1``.

*   The UpperCase ``T`` says that the functions are exported (available for others to use) while a lowercase says its not ``exported``.

*   Run the following commands to make two files with the list of symbols.

    ``cat /proc/kallsyms > /tmp/1``

*   Insert our module.

    ``insmod mymodule1.ko``

*   Save the symbols in another file.

    ``cat /proc/kallsyms > /tmp/2``

*   See the difference.

::

    diff /tmp/1 /tmp/2
    41353a41354,41357
    > 0000000000000000 t my_exit    [mymodule1]
    > 0000000000000000 t cleanup_module [mymodule1]
    > 0000000000000000 T add_two_numbers    [mymodule1]
    > 0000000000000000 T print_hello    [mymodule1]
     $ ~/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols

=============
Tool modprobe
=============

*   ``modprobe`` understands in which order the modules are to be loaded.

*   First remove the modules.

*   Run the command ``modprobe module2`` loads both the module.

.. todo:: Write section on modprobe

::

    $ sudo modprobe mymodule2
    modprobe: FATAL: Module mymodule2 not found in directory /lib/modules/4.7.0

    $ sudo modprobe mymodule2.ko
    modprobe: FATAL: Module mymodule2.ko not found in directory /lib/modules/4.7.0

    $ sudo modprobe -C . mymodule2.ko
    modprobe: FATAL: Module mymodule2.ko not found in directory /lib/modules/4.7.0

    $ man modprobe

    $ sudo modprobe -d . mymodule2.ko
    modprobe: ERROR: ../libkmod/libkmod.c:586 kmod_search_moddep() could not open moddep file '/home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/./lib/modules/4.7.0/modules.dep.bin'
    modprobe: FATAL: Module mymodule2.ko not found in directory /home/rishi/mydev/publications/lkw/doc/code/04_exporting_symbols/exporting_symbols/./lib/modules/4.7.0


=============
Tool - depmod
=============

.. todo:: Write this section on depmod.

* **DONT RUN IT** ``depmod`` is smart enough to find the dependencies and write to a file - don't run it as it will overwrite the original file. First take backup of the file.
    ``depmod ABSOLUTE_PATH_OF_THE_MODULE1 ABSOLUTE_PATH_OF_THE_MODULE2``
    see the file ``/modules/3.2.0-23-generic/modules.dep``


=======================================
One module dependent on several modules
=======================================


``modprobe`` automatically loading all the modules.
===================================================


============================================
String related functions available in kernel
============================================

*   There are a lot of function related to string operations available in the Linux Kernel for you to use. They all are exported.

*   See the output of ``/proc/kallsyms``.

::

    $ cat /proc/kallsyms | grep "T str"
    0000000000000000 T strndup_user
    0000000000000000 T string_to_security_class
    0000000000000000 T string_to_av_perm
    0000000000000000 T strcasecmp
    0000000000000000 T strcpy
    0000000000000000 T strncpy
    0000000000000000 T strcat
    0000000000000000 T strcmp
    0000000000000000 T strncmp
    0000000000000000 T strchr
    0000000000000000 T strchrnul
    0000000000000000 T strrchr
    0000000000000000 T strnchr
    0000000000000000 T strlen
    0000000000000000 T strnlen
    0000000000000000 T strspn
    0000000000000000 T strcspn
    0000000000000000 T strpbrk
    0000000000000000 T strsep
    0000000000000000 T strtobool
    0000000000000000 T strstr
    0000000000000000 T strnstr
    0000000000000000 T strlcpy
    0000000000000000 T strncasecmp
    0000000000000000 T strnicmp
    0000000000000000 T strncat
    0000000000000000 T strim
    0000000000000000 T strlcat
    0000000000000000 T string_get_size
    0000000000000000 T string_unescape
    0000000000000000 T string_escape_mem
    0000000000000000 T strncpy_from_user
    0000000000000000 T strnlen_user
    0000000000000000 T strlen_user
    0000000000000000 T strict_strtoul_scaled

*   The count of exported functions is

::

    cat /proc/kallsyms | grep "T " | wc -l
    18388

*   Let us now see how can we make use of one of the string functions that is ``strcat()``. In the following module we will just concatenate two strings and will print the output.

``FILE: mystring.c``
=====================

.. literalinclude:: code/04_exporting_symbols/strings/mystring.c
    :language: c
    :linenos:

``FILE: Makefile``
==================

.. literalinclude:: code/04_exporting_symbols/strings/Makefile
    :language: make
    :linenos:


=========
Exercises
=========

The exercises here will generally not make much sense with respect to kernel
development. You will not be writing a feature for the kernel but you will be
learning how to do the basics. So you MUST do it.

#.  Write a kernel module to which we can pass a string and it does the following. It must have the functions exported so that another kernel module can use the functions.
    #.  Find the length of the string. ``mystring_find_length()``
    #.  Returns the reverse of the string.   ``mystring_get_reverse()``
    #.  Returns the rotation of the string by 3 places.  ``char *mystring_get_rotated(char *srcstr, char *deststr, int rotations, int direction)``
    #.  Returns if the string is palindrome or not.  ``int mystring_is_palindrome(char *str)``
    #.  Returns a character array where you have saved only the characters which are present in the even indexes.
    #.  Returns a string which has all the letter capitalized.
    #.  Returns a string which has all the letter converted to lowercase.

#.  For the above kernel module write a testcase module which will call the functions and test if the functions are working correctly.

