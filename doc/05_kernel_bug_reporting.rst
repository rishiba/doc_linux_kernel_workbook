######################
Kernel's Bug Reporting
######################

* Kernel has built-in functions/macros for BUGS
* BUG(), BUG_ON(), dump_stack() and panic() can be used in your code to report error conditions.

BUG(), BUG_ON(), dump_stack(), panic() example
----------------------------------------------

``file``: proc.c
~~~~~~~~~~~~~~~~
.. literalinclude:: code/bug_on/proc.c
    :language: c
    :linenos:

``file``: Makefile
~~~~~~~~~~~~~~~~~~
.. literalinclude:: code/bug_on/Makefile
    :language: c
    :linenos:
