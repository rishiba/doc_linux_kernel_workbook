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
*  Netlink Kernel Sockets

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

=======================================
Proc entry to read and write data to it
=======================================

.. literalinclude:: code/06_proc/01_read_write_proc/myproc.c
    :linenos:
    :language: c

.. literalinclude:: code/06_proc/01_read_write_proc/myproc.h
    :linenos:
    :language: c

.. literalinclude:: code/06_proc/01_read_write_proc/Makefile
    :linenos: 
    :language: make
