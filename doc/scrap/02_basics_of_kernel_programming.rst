
.. _different_log_levels_printk-label:

Different log levels for ``printk()``
=====================================

::

    There are eight possible loglevel strings, defined in the header
    <linux/kernel.h>; we list them in order of decreasing severity:

    KERN_EMERG

    Used for emergency messages, usually those that precede a crash.
    KERN_ALERT

    A situation requiring immediate action.
    KERN_CRIT

    Critical conditions, often related to serious hardware or software
    failures.
    KERN_ERR

    Used to report error conditions; device drivers often use
    KERN_ERR to report hardware difficulties.
    KERN_WARNING

    Warnings about problematic situations that do not, in
    themselves, create serious problems with the system.
    KERN_NOTICE

    Situations that are normal, but still worthy of note. A
    number of security-related conditions are reported at
    this level.
    KERN_INFO

    Informational messages. Many drivers print
    information about the hardware they find at startup
    time at this level.
    KERN_DEBUG

    Used for debugging messages.

    Reference: http://www.makelinux.net/ldd3/chp-4-sect-2

