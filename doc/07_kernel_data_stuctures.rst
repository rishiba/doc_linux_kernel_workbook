######################
Kernel Data Structures
######################

* You need not code your own linked list for your code.
* Kernel gives you linked list and red black tree implementations.
* The linked list is extensively used by the kernel.
* Red Black tree is used in the Completely Fair Schedular.

Using Kernel's linked list for your data structure
--------------------------------------------------

``file``: ll.c
~~~~~~~~~~~~~~
.. literalinclude:: code/ll1/ll.c
    :language: c
    :linenos:

``file``: module.c
~~~~~~~~~~~~~~~~~~

.. literalinclude:: code/ll1/module.c
    :language: c
    :linenos:

``file``: proc.c
~~~~~~~~~~~~~~~~
.. literalinclude:: code/ll1/proc.c
    :language: c
    :linenos:


``file``: Makefile
~~~~~~~~~~~~~~~~~~
.. literalinclude:: code/ll1/Makefile
    :language: c
    :linenos:


Let us write a small application.

The application will show the kernel's linked list in a graphical way. How can we do it.

What we will do 

1. We will implement the kernel linked list.
2. We will give a  proc interface to user. When the user write's ``add [int]`` to the file we will add it to the linked list.
3. We will give a file where all the nodes are listed.
4. We will also give a file where the linked list is present in graphviz format. Any user can run the graphviz tool and generate a graph from that.

RedBlack Tree
=============

http://lwn.net/Articles/184495/

Radix Tree
==========

http://lwn.net/Articles/175432/
