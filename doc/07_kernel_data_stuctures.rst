######################
Kernel Data Structures
######################

* Kernel gives you linked list and red black tree implementations.
* You need not code your own linked list for your code.
* The linked list is extensively used by the kernel.
* Red Black tree is used in the Completely Fair Schedular.

Using Kernel's linked list for your data structure
--------------------------------------------------

Let us write a small application.

The application will show the kernel's linked list in a graphical way. How can we do it.

What we will do

1.  We will implement the kernel linked list.
2.  We will give a  proc interface to user. When the user write's ``add [int]`` to the file we will add it to the linked list.
3.  Writing ``delete [int]`` will delete the node with the provided value from the linked list.
4.  Writing ``print`` will print the whole linked list. The list can be viewed through the ``dmesg`` command.


.. literalinclude:: code/07_data_structures/01_ll/ll.c
    :language: c
    :linenos:

.. literalinclude:: code/07_data_structures/01_ll/ll.h
    :language: c
    :linenos:

.. literalinclude:: code/07_data_structures/01_ll/ll_module.c
    :language: c
    :linenos:

.. literalinclude:: code/07_data_structures/01_ll/ll_proc.c
    :language: c
    :linenos:

.. literalinclude:: code/07_data_structures/01_ll/Makefile
    :language: c
    :linenos:


Examples
--------

*	Lets just print the empty list.

::

	echo "print" > /proc/linked_list 
	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# dmesg 
	[  578.782533] ll_driver: module verification failed: signature and/or required key missing - tainting kernel
	[  578.783117] Hello from Linked List Module
	[  630.344370] Calling Proc Write
	[  630.344376] First Arguement print
	[  630.344378] Second Argument 0
	[  630.344380] Printing the linked list


*	Now let us add some nodes.

::


	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "add 10" > /proc/linked_list 
	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "add 20" > /proc/linked_list 
	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "add 30" > /proc/linked_list 
	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# dmesg 
	[  578.782533] ll_driver: module verification failed: signature and/or required key missing - tainting kernel
	[  578.783117] Hello from Linked List Module
	[  630.344370] Calling Proc Write
	[  630.344376] First Arguement print
	[  630.344378] Second Argument 0
	[  630.344380] Printing the linked list
	[  642.095630] Calling Proc WriteFirst Arguement add
	[  642.095638] Second Argument 10
	[  642.095640] Adding data to linked list 10
	[  645.399251] Calling Proc WriteFirst Arguement add
	[  645.399256] Second Argument 20
	[  645.399257] Adding data to linked list 20
	[  647.542762] Calling Proc WriteFirst Arguement add
	[  647.542767] Second Argument 30
	[  647.542768] Adding data to linked list 30

* 	Let us print again.

::

	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "print" > /proc/linked_list 

* Let us delete some nodes.

::

	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "delete 30" > /proc/linked_list 

*	Let us delete a non existent node.

::

	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "delete 0" > /proc/linked_list 

*	Delete more node.

::

	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "delete 10" > /proc/linked_list 

* 	Print.

::

	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# echo "print" > /proc/linked_list 
	
*	Check the ``dmesg`` commands output.

::

	root@lkw:~/doc_linux_kernel_workbook/doc/code/07_data_structures/01_ll# dmesg
	[  578.782533] ll_driver: module verification failed: signature and/or required key missing - tainting kernel
	[  578.783117] Hello from Linked List Module
	[  630.344370] Calling Proc Write
	[  630.344376] First Arguement print
	[  630.344378] Second Argument 0
	[  630.344380] Printing the linked list
	[  642.095630] Calling Proc WriteFirst Arguement add
	[  642.095638] Second Argument 10
	[  642.095640] Adding data to linked list 10
	[  645.399251] Calling Proc WriteFirst Arguement add
	[  645.399256] Second Argument 20
	[  645.399257] Adding data to linked list 20
	[  647.542762] Calling Proc WriteFirst Arguement add
	[  647.542767] Second Argument 30
	[  647.542768] Adding data to linked list 30
	[  653.222910] Calling Proc WriteFirst Arguement print
	[  653.222916] Second Argument 0
	[  653.222918] Printing the linked list
	[  653.222919] Node is 10
	[  653.222920] Node is 20
	[  653.222921] Node is 30
	[  659.727435] Calling Proc WriteFirst Arguement delete
	[  659.727440] Second Argument 30
	[  659.727442] Deleting node from linked list 30
	[  659.727443] Found the element 30
	[  665.175263] Calling Proc WriteFirst Arguement delete
	[  665.175274] Second Argument 0
	[  665.175277] Deleting node from linked list 0
	[  665.175281] Could not find the element 0
	[  665.175282] Delete failed 
	[  667.134783] Calling Proc WriteFirst Arguement delete
	[  667.134789] Second Argument 10
	[  667.134791] Deleting node from linked list 10
	[  667.134792] Found the element 10
	[  668.942912] Calling Proc WriteFirst Arguement print
	[  668.942917] Second Argument 0
	[  668.942919] Printing the linked list
	[  668.942920] Node is 20
