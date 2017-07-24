##############
Proc Interface
##############

============
Introduction
============

We have inserted modules to the kernel and can get them do something useful.
But how to get some information from the kernel.

We need to be able to get some information from the kernel. There are multiple
ways of doing it.

*  System Calls
*  Proc File System and Sysfs file system
*  NetLink Kernel Sockets

In this chapter we will see the Proc Interface. Others are not in the scope of
this book.

Why this chapter
================

This chapter will enable you to understand and write your own proc interface.

What will you learn
===================

*  Writing a proc interface.

Concepts and Keywords involved
==============================

Prerequisites
=============

None

=============
New Functions
=============

``kmalloc()``
=============

*   kmalloc() is the kernel space version of malloc()
*   call it  **kmalloc(bytes, GFP_KERNEL)**
*   Read more about it in ``Linux Kernel Develpement, Robert Love``

=============================
A Simple Only Read Proc Entry
=============================

Introduction
============

Code
====

``FILE: myproc.c``
~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/00/myproc.c
    :language: c
    :linenos:

``FILE : Makefile``
~~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/00/Makefile
    :language: c
    :linenos:

=====================================
Proc Directory with Multiple Entries
=====================================

Introduction
============

.. todo:: Write this section.

Code
====

``FILE: proc.c``
~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/01/myproc.c
    :language: c
    :linenos:

``FILE : Makefile``
~~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/01/Makefile
    :language: c
    :linenos:

==================================================================================
Make a proc entry and based on value written to the file call different functions.
==================================================================================

Introduction
============

.. todo:: Write this section

Code
====

``FILE : proc.c``
~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/02/myproc.c
    :language: c
    :linenos:

``FILE : Makefile``
~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/02/Makefile
    :language: c
    :linenos:


==================================================================================
Make a proc entry and based on value written to the file call different functions.
==================================================================================

Introduction
============

.. todo:: write this section

Code
====


``FILE : proc.c``
~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/03/myproc.c
    :language: c
    :linenos:

``FILE : Makefile``
~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/03/Makefile
    :language: c
    :linenos:

=========================================
Module to write a command line calculator
=========================================

Introduction
============


.. todo:: Write this section


We can return the number of bytes read :-D

echo "add 1 23" > fileName # check dmesg


Code
====

``FILE : proc.c``
~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/04/myproc.c
    :language: c
    :linenos:

``FILE : Makefile``
~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/04/Makefile
    :language: c
    :linenos:


======================================================================
Module to display some system information using the seq_file interface
======================================================================

Introduction
============

Proc file system is an effecitve way to perform some system realted tasks and
getting some information from the linux kernel.

Here we will see a list of file systems which are registered in the kernel. We
will basically do what the ``/proc/filesystems`` do.

Code
====


``FILE : proc.c``
~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/04/myproc.c
    :language: c
    :linenos:

``FILE : Makefile``
~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/06_proc/04/Makefile
    :language: c
    :linenos:

References
==========

http://tuxthink.blogspot.in/2013/10/creation-of-proc-entrt-using.html
