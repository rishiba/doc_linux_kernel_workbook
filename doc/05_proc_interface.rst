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
Proc interface is being used by kernel to communicate information to the
userspace and take input from the userspace. For example: file ``/proc/mounts``
is a file which lists the file systems which are mounted on the system. 

Proc insterface is useful to communicate some information to the kernel space
as well. For example the file ``/proc/sysrq-trigger`` gives you ability to ask
the kernel to behave differently. For example

``echo l > /proc/sysrq-trigger`` will print the backtraces of all cpus. The
file ``linux-4.7/Documentation/sysrq.txt`` describes this in more detail.

For more details on proc interface read ``https://www.kernel.org/doc/Documentation/filesystems/proc.txt``.


Thus - we can also use the proc interface to talk to the user space. In the
next chapter on BUGS, we will see how a write to a proc interface can trigger
different function calls in the kernel space. In the next chapter on linked
list, we will see how we can get some work done using the proc interface.
Understanding the code of this chapter is thus important as it becomes the
ground work of next chapters.

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

.. literalinclude:: code/06_proc/01_read_write_proc/Makefile
    :linenos: 
    :language: make


*   Let us first insert the module by running ``make insert``

*   Let us print the original value.

::

     cat /proc/my_proc_entry_write 
     Hello People$

*   Let us now write on the original value.

::

     # echo "I am writing this" > /proc/my_proc_entry_write 
     # cat /proc/my_proc_entry_write 
     I am writing this
