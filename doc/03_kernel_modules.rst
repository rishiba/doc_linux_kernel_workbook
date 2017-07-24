##############
Kernel Modules
##############

============
Introduction
============

We generally do not make changes directly to the core kernel code. We mostly
write small modules to be added to the kernel. This way we can separate out our
changes from the mainline kernel.

If you see - the file system are thus modules only, as not all the Linux
installations do not need all the file systems and the user can load them on
demand.

In this chapter we will see how to write kernel modules.

Why this chapter
================

This chapter is the most important building block of the whole document. So
spend some time with it. Do not just copy paste the code.

Type the code and then run it. Read the comments and type them as well so as to
understand what the comments mean.

The more time you spend here - the lesser time you will spend later.

What will you learn
===================

We will learn

* How to write a basic kernel module.
* How to write functions and make it available to other modules. Sort of library.
* How to pass parameters to the modules which is getting loaded.

Concepts and Keywords involved
==============================

Prerequisites
=============

C Programming.

=======================
What are Kernel Modules
=======================

* Pieces of code that can be loaded and unloaded into the kernel upon demand.
* Extends the functionality of the kernel without the need to reboot the system.
* Device drivers which allows the kernel to access hardware connected to the
  system. If we plug any new device the kernel cannot use it properly unless we
  have the right drivers in place. The kernel detects the device type and loads
  the respective modules from the code base. Thus device drivers are generally
  modules (apart from the basic / legacy drivers.)

========================
Kernel Module Advantages
========================

* Without modules, we would have to build monolithic kernels.
* Adding new functionality would require adding the code in the kernel image which will need recompilation.
* Monolithic kernel leads to  larger kernel images resulting in loading code which is not required.
* Rebooting machine whenever new functionality is added.
* Example: till the time you don't have to mount a Ext2 file system why will you load code for reading ext2 file system.

========================
Tools for Kernel Modules
========================

Before getting into writing a module we must first see the tools/commands which
we will use to get the modules working.

``insmod``
==========

*   ``insmod`` - insert module.


``modprobe``
============

*   ``modprobe -r`` - remove the module present in the kernel.

``rmmod``
=========


*   ``rmmod`` - remove the module present in the kernel.

``lsmod``
=========

*   ``lsmod`` - list the modules inserted in the kernel.

``modinfo``
===========


*   ``modinfo`` - prints the information of the module.

``dmesg``
===========

*   ``dmesg``

``syslog``
==========

*   ``syslog``

Some System Calls
=================

*   ``init_module(), query_module(), create_module(), delete_module()`` - system calls called by the various commands to insert/delete module to the kernel space.

=============
New Functions
=============

There are few new things which you will see in the code.


``printk()``
============

*   ``printk()`` - this is the kernel counter part of the user space
    ``printf()`` function. Its syntax is ``printk(LEVEL "FORMAT_SPECIFIER",
    parameters)``. The ``LEVEL`` is used to specify the severity of the message
    you wish to print. See :ref:`different_log_levels_printk-label`.

``module_init()``
==================

*   ``module_init()`` - ``module_init()`` is the first function which will be
    called when the module is loaded. This gives us a entry point to the kernel
    module. Here we can initialize the global variables, setup functions, setup
    enviornment and other stuff. The use of this will be clear in the next
    chapters.

``module_exit()``
=================

*   ``module_exit()`` - ``module_exit()`` is the function which is called when
    the module is being unloaded from the system. Here we can free the
    allocated memory, free the locks and do other cleanup actions. This will be
    clear in the coming chapters.

=========================
Hello World Kernel Module
=========================

Introduction
============

We will write our first kernel module. We will code it, compile it and then
``insert`` the module in the kernel. When the module gets inserted the kernel
gets the functionality provided by the module. In this ``Hello World`` module,
their is no functionality provided to the kernel. The module just gets inserted
and it prints ``Hello World``. You can see the message printed by the kernel
module by running the ``dmesg`` tool. ``dmesg`` shows you the buffer of the
kernel.

Code
====

``FILE: mymodule.c``
--------------------

.. literalinclude:: code/03_modules/hello_world/mymodule.c
    :language: c
    :linenos:

``FILE: Makefile``
------------------

.. literalinclude:: code/03_modules/hello_world/Makefile
    :language: make
    :linenos:

Common Questions
================

How to run the code
-------------------

To insert the module we need to use the ``insmod`` command with the module
name. We need to be ``root`` while doing it.

In the ``Makefile`` we have a target ``insert``. This target calls the
``insmod`` command to insert the module into the kernel.


How the code gets executed
--------------------------

On inserting the module the function registered as ``module_init()`` gets
called. In our case it is ``my_init()``.

This function just prints a message to the logs and returns.

How to remove the module
------------------------

To remove the module we need to use the ``rmmod`` command with the module name.
We need to be ``root`` while doing it.

``rmmod mymodule``

How the module gets removed/unloaded
------------------------------------

When the ``rmmod`` command is invoked the function registered with
``module_exit()`` is called. In our case it is ``my_exit()``. The function just
prints the messages in the logs and then returns.

===================================
Module Which Does Some Calculations
===================================

Introduction
============

The above module did not do anything and just printed some messages. We will
now write a module which will do some calculations.

The intention of this excercise it to show that its plain C code and you can do
the regular stuff here as well.

Code
====

``FILE: mycalc.c``
-------------------

.. literalinclude:: code/03_modules/mycalc/mycalc.c
    :language: c
    :linenos:

``FILE: Makefile``
-------------------

.. literalinclude:: code/03_modules/mycalc/Makefile
    :language: c
    :linenos:

======================
Module with Parameters
======================

Introduction
============

In the above calculator if we want to change the variables, or we want to do
calculation of different integers we will have to change the code and hardcode
the value.

We do not want that, we want that the values should be taken from the user.
For this we can pass the paramters to the kernel module to do it.

First we will see a small module which does it and then we will see it in the
calculator program.

.. todo:: Explain the code of moduleparam.h

Code
====

``FILE: mymodule_with_parameters.c``
-------------------------------------

.. literalinclude:: code/03_modules/module_with_parameters/mymodule.c
    :language: c
    :linenos:

``FILE: Makefile``
------------------

.. literalinclude:: code/03_modules/module_with_parameters/Makefile
    :language: make
    :linenos:


====================================================
Module with Character Array and Arrays as parameters
====================================================

Introduction
============

Passing paramters is not limited to integers only, we can pass characters and
arrays as well. See the following example to understand how to do it.

Questions
=========

How to pass floats?

Code
====


``FILE: mymodule_with_parameters.c``
-------------------------------------

.. literalinclude:: code/03_modules/module_string_array_parameters/mymodule_with_parameters.c
    :language: c
    :linenos:

``FILE: Makefile``
------------------

.. literalinclude:: code/03_modules/module_string_array_parameters/Makefile
    :language: make
    :linenos:

==========================
Calculator with parameters
==========================

Introduction
============

In this module, we have mostly changed the calculator's code to suite the parameter passing.

Code
====

``FILE: mycalc_with_parameters.c``
-----------------------------------

.. literalinclude:: code/03_modules/mycalc_with_parameters/mycalc_with_parameters.c
    :language: c
    :linenos:

``FILE: Makefile``
------------------

.. literalinclude:: code/03_modules/mycalc_with_parameters/Makefile
    :language: make
    :linenos:

==========
Conclusion
==========

In this chapter we mostly learnt about the very basics of kernel module
programming. We have a lot of ground to cover. Let's get into other concepts of
modules.

==========
References
==========
