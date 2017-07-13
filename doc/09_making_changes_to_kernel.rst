#############################
Making Changes to Kernel Code
#############################

We will have to make changes in the kernel in order to add features to it and get the features
working. There are two steps to it. Making the changes and then compiling them.

The steps are quite simple

#.  Make the changes
#.  Compile the kernel.

Compiling the whole kernel is one way to make the changes you did into the kernel. If your
changes are in a small module of the code you need not compile the whole code and you can just make
that module of the code.

In this section we will make two changes to the kernel.

#.  Effecting only a module.
#.  Effecting the whole kernel.

* Make the changes in the required file, re-check it.
* ``make SUBDIRS="path"`` - to compile the particular module.
* ``make modules_install`` - to install the module, you can manually copy the module to the ``/lib/`` directory.
* ``make install`` - update the whole system if required, not required generally.
* Check the working of the code.

Hands-On - Making changes to a small module
===========================================

* Make changes to the ext2 code. In the ``ext2_fsync`` function, add a ``printk`` and compile the code. Copy the modules to the ``/lib/XX`` directory and test by mounting a ext2 file system. Check ``dmesg`` for the printed message. Open/Write a file using ``vim`` to see the effects.
* The diff is based of ``linux-3.4.6 Kernel`` - use the same kernel version to avoid unneccessary problems at this stage.

.. literalinclude:: code/kernel/project01/ext2_changed_code/file.c.diff
    :language: c
    :linenos: 


Hands-On - Making changes to a code which effects the whole kernel
==================================================================

.. todo:: Make a small diff which will result in compilation of a major part of the kernel.
