##########
Setting Up
##########

============
Introduction
============

We need to setup our machine properly so that we do not face issues at a later stage.

This chapter is the pre-requisite for the whole document to be completed successfully.

=====
Steps
=====

*   Download and install ``Ubuntu Server 16.04.2 LTS`` on a Virtual Machine.

*   Here are the output of the commands ``uname -a`` and ``cat /etc/lsb-release`` file.

::

    rishi@rishi-VirtualBox:~$ uname -a
    Linux rishi-VirtualBox 4.4.0-24-generic #43-Ubuntu SMP Wed Jun 8 19:27:37 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux

::

    rishi@rishi-VirtualBox:~$ cat /etc/lsb-release
    DISTRIB_ID=Ubuntu
    DISTRIB_RELEASE=16.04
    DISTRIB_CODENAME=xenial
    DISTRIB_DESCRIPTION="Ubuntu 16.04 LTS"

=====================
Why a Virtual Machine
=====================

*   The machine where you will play should be a virtual machine so that your invalid setting to the
    kernel or any other configuration should not effect your base host machine. During this whole book
    you will write code which CAN end up shutting down the system or corrupting the system. Doing all this stuff on a virtual machine will help us in running the code on a different machine, thus saving our machines from the catastrophic failures.

*   The virtual machine should have at least 2 cores and 512 MB of RAM. This will make the kernel compilation fast.

*   Take a snapshot/clone of the machine once you are done with the installation. This will enable
    you to revert your machine to the original state in case you mess up with it too
    badly.

================
Install Packages
================

Install the following packages.

::

    vim
    gcc
    openssh-server
    gdb
    tree
    cscope
    ctags

The script below will help you in this.

.. literalinclude:: code/01_setting_up/install_packages.sh
    :language: bash
    :linenos:
