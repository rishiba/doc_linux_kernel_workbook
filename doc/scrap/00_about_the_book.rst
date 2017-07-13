##############
About the Book
##############

************
Introduction
************

Linux Kernel Programming is one of the most exciting thing for the beginners in
System Programming. With time a lot of excellent books were published on it but
the books were written to cover everything about the Linux Kernel and thus had
a widespread scope. These books enabled to a lot of people to take kernel
programming as their career chocices or as a hobby.

I have been seeing a lot of queries on the ``kernelnewbies`` mailing list where
people are requesting for the documents to start with. Most of them want to go
through a guided course or something. 

People (even I) generally suggest them the following books:

.. todo:: Write the names of the books which one should read.

For the learners who can't wait to get into code - I have written this small book.

This book is updated with the latest Ubuntu Desktop LTS releases. That means that the book have the
code which will meet the latest Ubuntu Desktop Releases.

1. Basics of Kernel Programming

    In this section we will deal with 
    
    * Compilation of Kernel
    * Code Walkthrough using ``cscope`` and ``ctags``
    * Kernel Modules
    * Kernel Module Programming
    * Proc Interface
    * Data Strucutures available in the Kernel
    * Character Device Drivers
    * Other good stuff

    The section has many ``Hands-On`` exercises which will enable you to learn how
    to write code for kernel modules, and make changes to the linux kernel. This
    section is very essential for getting a good feel of kernel programming.

===========================
Some Books On Similar Topic
===========================

I found a book on linux kernel programming, http://www.amazon.com/Linux-Kernel-Programming-3rd-Edition/dp/0201719754#reader_0201719754

Another one ... http://kernelbook.sourceforge.net/

Found a university course on it http://www.cs.utexas.edu/~ygz/378-03S/

****************
Acknowledgements
****************


.. todo:: Write the acknowlegment of this book.


**********
Motivation
**********

While learning the nitty gritties of linux kernel I found that there is not
document which tells the details in the way most of the people understand. I
also saw a lot of requests on kernel new bies for tutorials and documents which
can help programmers and learners in a hands-on way.

This document is just a small attempt for bridging the gap between the hands-on
and theory.

While interacting with students related to Linux and Linux Kernel I found that
they do not have a head start guide which gives a detailed view of the whle
linux system. Moreover there is no such document which is hands-on based,
exercise based. 

I see a lot of questions on mailing lists asking for help in starting with linux
kernel and then getting lost in the wide amount of unstructed information
present every where.

*************
Prerequisites
*************


**********************************
The coding and testing enviornment
**********************************

#. Virtual Machine with Linux Installed on it.
#. Install gcc, vim, and git
#. Install 4.2.0-rc7 kernel on it. Get the kernel from kernel.org. See  :ref:`install_linux_kernel-label`.
#. Write and test a sample kernel module. See :ref:`test_kernel_module-label`.


::
  
  make
  insmod hello.ko
  dmesg | grep hello -i

#. Install python-docutils package. We will use Sphinx tool for writing our documentation. Here is the link http://sphinx-doc.org/ 
  Try writing some hello world document in that. Use the following convention.

  ::

    Normally, there are no heading levels assigned to certain characters as the
    structure is determined from the succession of headings. However, for the Python
    documentation, this convention is used which you may follow:
    
    # with overline, for parts
    
    * with overline, for chapters
    
    =, for sections
    
    -, for subsections
    
    ^, for subsubsections
    
    ", for paragraphs

#. Checkout the code from git@github.com:abrrba/bfs.git  -- you will need a github account. Upload your ssh keys for passwordless authentication.

  How to upload the key?

  do "ssh-keygen" keep pressing enter

  At the end of the command do "cat .ssh/id_rsa.pub" and copy the text from
  "ssh-rsa" to end.

  Then in https://github.com/settings/profile page go to SSH Keys (direct link
  is https://github.com/settings/ssh") and upload your keys.

  Read about it if required.

*******
Reading
*******

This is important so that we get connected to the fundamentals of operating
systems. You are free to read the whole books as well !!

.. note:: For those who are already comfortable with the chapters should also skim the chapters once just to revise them.

#. Linux Kernel Development
    Chapter 01 - Introduction to the Linux Kernel 
    Chapter 02 - Getting startted with the kernel
    Chapter 05 - System Calls
    Chapter 12 - Memory Management
    Chapter 13 - The Virtual File System

#. Understanding The Unix Kernel
    Chapter 12 - The Virtual File System
    Chapter 18 - The Ext2 File System

#. The Design Of Unix Operating System
    Chapter 01 - General Overview of the system
    Chapter 02 - Introduction to the kernel
    Chapter 03 - The Buffer Cache
    Chapter 04 - Internal Representation Of Files
    Chapter 05 - System Calls For The File System

.. _test_kernel_module-label:

******************
Test Kernel Module
******************


************
Introduction
************

This is a book on how to write a file system in Linux Kernel. The purpose of the
file system is to demonstrate how easy it is to code a file system.

********************
Reading the document
********************

#. Checkout the Repo. See :ref:`checkout_repo-label`.
#. Install sphinx using the command ``pip install -U Sphinx``.
#. Install ``rst2pdf`` for reading this document in pdf. Run ``rst2pdf README.rst``. Read the pdf as ``README.pdf``
#. Use ``./hh`` file to read the html version of the document. Alternatively make html ``make html``. Open the document ``_build/html/index.html``.
#. Use ``./pp`` file to read the PDF version of the doucment. Alternatively make pdf ``make latexpdf``. Open the document ``_build/latex/BasicFilesystem.pdf``

.. _checkout_repo-label:

*****************
Checkout The Repo
*****************

#. Make a github account.
#. Upload your ssh keys for passwordless authentication. Read the document for understanding how to upload ssh keys. See :ref:`upload_ssh_keys-label`.
#. Checkout the code from git@github.com:abrrba/bfs.git.

.. _upload_ssh_keys-label:

How to upload the key?
======================

#. Do "ssh-keygen" keep pressing enter.
#. At the end of the command do "cat .ssh/id_rsa.pub" and copy the text from "ssh-rsa" to end.
#. Then in https://github.com/settings/profile page go to SSH Keys (direct link is https://github.com/settings/ssh") and upload your keys.
