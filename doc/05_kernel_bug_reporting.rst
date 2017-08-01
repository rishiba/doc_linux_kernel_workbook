######################
Kernel's Bug Reporting
######################

* Kernel has built-in functions/macros for BUGS
* BUG(), BUG_ON(), dump_stack() and panic() can be used in your code to report error conditions.

BUG(), BUG_ON(), dump_stack(), panic() example
----------------------------------------------

.. literalinclude:: code/05_bug_reporting/01_bugon/mybugondriver.c
    :language: c
    :linenos:

``file``: Makefile
~~~~~~~~~~~~~~~~~~
.. literalinclude:: code/05_bug_reporting/01_bugon/Makefile
    :language: make
    :linenos:
