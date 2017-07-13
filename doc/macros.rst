====================
Macros and Functions
====================

*   You will see a lot of functionality available in the kernel space. Some are in the form of macros and inline functions while some are in the form of exported function.

*   The functions which are provided as macros 
*   Let us now look at some of the functionality which is present due to macros.

*   The kernel gives a very good interface for you to use a bitmap.

*   See the Macros in the file ``asm/bitops.h`` 

::

    set_bit(bit, addr)                   *addr |= bit
    clear_bit(bit, addr)                 *addr &= ~bit
    change_bit(bit, addr)                *addr ^= bit
    test_bit(bit, addr)                  Is bit set in *addr?
    test_and_set_bit(bit, addr)          Set bit and return old value
    test_and_clear_bit(bit, addr)        Clear bit and return old value
    test_and_change_bit(bit, addr)       Change bit and return old value
    find_first_zero_bit(addr, nbits)     Position first zero bit in *addr
    find_first_bit(addr, nbits)          Position first set bit in *addr
    find_next_zero_bit(addr, nbits, bit) Position next zero bit in *addr >= bit
    find_next_bit(addr, nbits, bit)      Position next set bit in *addr >= bit

*   These are not functions, hence you will not see them in the ``/proc/kallsyms``

::
 
    $ cat /proc/kallsyms | grep "clear_bit\|set_bit" -w
    $ echo $?
    1


While you can see the string related functions being available.

::

    $ cat /proc/kallsyms | grep "strcat\|strcmp"
    0000000000000000 T strcat
    0000000000000000 T strcmp

*   As these are macros we can see them expanded after preprocessing. Do the following for stopping the module compilation just after preprocessing.


::

    KERNEL_SOURCE="/home/rishi/lkw/linux-4.7/"
    gcc -E mybitmap.c -I${KERNEL_SOURCE}/include -I${KERNEL_SOURCE}arch/x86/include > PREPROCESSED.c 2>/dev/null


.. note:: I have redirected the errors to ``/dev/null`` as there were some errors coming.  


*   See the line where we used ``DECLARE_BITMAP``, it has been changed to in the ``PREPROCESSED.c`` file.

::

    unsigned long mybits[BITS_TO_LONGS(40)];
    MYBITMAP = (void *) &mybits;


*   See the line where we call ``test_bit()`` is now converted to

::

    (__builtin_constant_p((i)) ? constant_test_bit((i), (MYBITMAP)) : variable_test_bit((i), (MYBITMAP)))

*   These are not function calls, but these are macro expantions which do the bitmap related operations for you.


.. todo:: show the function and macro definations to the readers.

=============================================================
Example of some bitwise related functionality being available
=============================================================
