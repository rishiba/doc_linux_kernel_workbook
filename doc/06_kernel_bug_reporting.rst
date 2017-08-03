######################
Kernel's Bug Reporting
######################

*   Kernel has built-in functions/macros for BUGS
*   BUG(), BUG_ON(), dump_stack() and panic() can be used in your code to report error conditions.
*   For more details on these function read the chapter ``Debugging`` in the book ``Linux Kernel Development, 3rd Edition, Robert love``. 
*   This chapter will give you example with the proc interface on how to use the debugging facilities given in the kernel.

BUG(), BUG_ON(), dump_stack(), panic() example
==============================================



.. literalinclude:: code/05_bug_reporting/01_bugon/mybugondriver.c
    :language: c
    :linenos:

Makefile
=========

.. literalinclude:: code/05_bug_reporting/01_bugon/Makefile
    :language: make
    :linenos:

Running the code
================

To run the code you will have to write to the ``proc`` entry. Based on the value written the system will behave differently.

You can see the output in the ``dmesg`` output.

::

    $ make insert
    make[1]: Entering directory '/usr/src/linux-headers-4.4.0-62-generic'
    CLEAN   /home/rishi/doc_linux_kernel_workbook/doc/code/05_bug_reporting/01_bugon/.tmp_versions
    CLEAN   /home/rishi/doc_linux_kernel_workbook/doc/code/05_bug_reporting/01_bugon/Module.symvers
    make[1]: Leaving directory '/usr/src/linux-headers-4.4.0-62-generic'
    rm -rf   Module.symvers modules.order
    make[1]: Entering directory '/usr/src/linux-headers-4.4.0-62-generic'
    CC [M]  /home/rishi/doc_linux_kernel_workbook/doc/code/05_bug_reporting/01_bugon/mybugondriver.o
    Building modules, stage 2.
    MODPOST 1 modules
    CC      /home/rishi/doc_linux_kernel_workbook/doc/code/05_bug_reporting/01_bugon/mybugondriver.mod.o
    LD [M]  /home/rishi/doc_linux_kernel_workbook/doc/code/05_bug_reporting/01_bugon/mybugondriver.ko
    make[1]: Leaving directory '/usr/src/linux-headers-4.4.0-62-generic'
    sudo dmesg -c
    sudo insmod mybugondriver.ko

We will now write 1 to the proc entry.


::

    $ echo 1 > /proc/my_bugon_driver
    $ dmesg


    ------------[ cut here ]------------
    [ 2936.363067] kernel BUG at /home/rishi/doc_linux_kernel_workbook/doc/code/05_bug_reporting/01_bugon/mybugondriver.c:45!
    [ 2936.363101] invalid opcode: 0000 [#1] SMP 
    [ 2936.363118] Modules linked in: mybugondriver(OE) ppdev vboxvideo ttm drm_kms_helper drm snd_intel8x0 fb_sys_fops snd_ac97_codec syscopyarea ac97_bus sysfillrect snd_pcm joydev sysimgblt input_leds snd_timer snd soundcore serio_raw i2c_piix4 parport_pc vboxguest 8250_fintek parport mac_hid ib_iser rdma_cm iw_cm ib_cm ib_sa ib_mad ib_core ib_addr iscsi_tcp libiscsi_tcp libiscsi scsi_transport_iscsi autofs4 btrfs raid10 raid456 async_raid6_recov async_memcpy async_pq async_xor async_tx xor raid6_pq libcrc32c raid1 raid0 multipath linear hid_generic usbhid hid crct10dif_pclmul crc32_pclmul ghash_clmulni_intel aesni_intel aes_x86_64 lrw gf128mul glue_helper ablk_helper cryptd ahci psmouse libahci e1000 pata_acpi fjes video
    [ 2936.363407] CPU: 0 PID: 1766 Comm: bash Tainted: G           OE   4.4.0-62-generic #83-Ubuntu
    [ 2936.363429] Hardware name: innotek GmbH VirtualBox/VirtualBox, BIOS VirtualBox 12/01/2006
    [ 2936.363451] task: ffff8800d8deb800 ti: ffff880035734000 task.ti: ffff880035734000
    [ 2936.363471] RIP: 0010:[<ffffffffc03e618e>]  [<ffffffffc03e618e>] my_proc_write+0xae/0xc0 [mybugondriver]
    [ 2936.363501] RSP: 0018:ffff880035737e78  EFLAGS: 00010246
    [ 2936.363516] RAX: 0000000000000000 RBX: 0000000000000002 RCX: 00000000000032a5
    [ 2936.363535] RDX: 00000000000032a4 RSI: ffff88011b41a020 RDI: ffff880116801e00
    [ 2936.363553] RBP: ffff880035737e90 R08: 000000000001a020 R09: ffffffffc03e615c
    [ 2936.363572] R10: ffffea0004572b40 R11: 0000000000000239 R12: ffff880115cad950
    [ 2936.363592] R13: 0000000001189408 R14: 0000000000000002 R15: 0000000000000000
    [ 2936.363611] FS:  00007f4b6fc64700(0000) GS:ffff88011b400000(0000) knlGS:0000000000000000
    [ 2936.363633] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
    [ 2936.363648] CR2: 00007ffedb58b4b8 CR3: 00000000d597d000 CR4: 00000000000406f0
    [ 2936.363669] Stack:
    [ 2936.363676]  ffff8800344a4a80 fffffffffffffffb ffff880035737f18 ffff880035737eb0
    [ 2936.363699]  ffffffff8127bee2 ffff8800da934400 0000000001189408 ffff880035737ec0
    [ 2936.363723]  ffffffff8120e168 ffff880035737f00 ffffffff8120eaf9 ffffffff810caeb1
    [ 2936.363746] Call Trace:
    [ 2936.363758]  [<ffffffff8127bee2>] proc_reg_write+0x42/0x70
    [ 2936.363784]  [<ffffffff8120e168>] __vfs_write+0x18/0x40
    [ 2936.363799]  [<ffffffff8120eaf9>] vfs_write+0xa9/0x1a0
    [ 2936.364337]  [<ffffffff810caeb1>] ? __raw_callee_save___pv_queued_spin_unlock+0x11/0x20
    [ 2936.365035]  [<ffffffff8120f7b5>] SyS_write+0x55/0xc0
    [ 2936.365697]  [<ffffffff818385f2>] entry_SYSCALL_64_fastpath+0x16/0x71
    [ 2936.366236] Code: f8 02 74 29 7e 20 83 f8 03 74 11 83 f8 04 75 11 48 c7 c7 e0 70 3e c0 e8 c5 6f da c0 e8 7c 1a 01 c1 48 89 d8 eb 9c 83 e8 01 75 f6 <0f> 0b 0f 0b 0f 1f 40 00 66 2e 0f 1f 84 00 00 00 00 00 0f 1f 44 
    [ 2936.367912] RIP  [<ffffffffc03e618e>] my_proc_write+0xae/0xc0 [mybugondriver]
    [ 2936.368464]  RSP <ffff880035737e78>
    [ 2936.369000] fbcon_switch: detected unhandled fb_set_par error, error code -16
    [ 2936.370289] fbcon_switch: detected unhandled fb_set_par error, error code -16
    [ 2936.371596] ---[ end trace 064cb0dbcc2892d3 ]---


::

    $ echo 2 > /proc/mybugondriver
    $ dmesg

    ------------[ cut here ]------------
    [ 3035.436271] kernel BUG at /home/rishi/doc_linux_kernel_workbook/doc/code/05_bug_reporting/01_bugon/mybugondriver.c:48!
    [ 3035.437611] invalid opcode: 0000 [#3] SMP 
    [ 3035.438117] Modules linked in: mybugondriver(OE) ppdev vboxvideo ttm drm_kms_helper drm snd_intel8x0 fb_sys_fops snd_ac97_codec syscopyarea ac97_bus sysfillrect snd_pcm joydev sysimgblt input_leds snd_timer snd soundcore serio_raw i2c_piix4 parport_pc vboxguest 8250_fintek parport mac_hid ib_iser rdma_cm iw_cm ib_cm ib_sa ib_mad ib_core ib_addr iscsi_tcp libiscsi_tcp libiscsi scsi_transport_iscsi autofs4 btrfs raid10 raid456 async_raid6_recov async_memcpy async_pq async_xor async_tx xor raid6_pq libcrc32c raid1 raid0 multipath linear hid_generic usbhid hid crct10dif_pclmul crc32_pclmul ghash_clmulni_intel aesni_intel aes_x86_64 lrw gf128mul glue_helper ablk_helper cryptd ahci psmouse libahci e1000 pata_acpi fjes video
    [ 3035.442196] CPU: 1 PID: 4793 Comm: bash Tainted: G      D    OE   4.4.0-62-generic #83-Ubuntu
    [ 3035.442719] Hardware name: innotek GmbH VirtualBox/VirtualBox, BIOS VirtualBox 12/01/2006
    [ 3035.443321] task: ffff8800da7bc600 ti: ffff8800db9bc000 task.ti: ffff8800db9bc000
    [ 3035.443858] RIP: 0010:[<ffffffffc03e6190>]  [<ffffffffc03e6190>] my_proc_write+0xb0/0xc0 [mybugondriver]
    [ 3035.444982] RSP: 0018:ffff8800db9bfe78  EFLAGS: 00010246
    [ 3035.445590] RAX: 0000000000000002 RBX: 0000000000000002 RCX: 0000000000001063
    [ 3035.446204] RDX: 0000000000001062 RSI: ffff88011b51a020 RDI: ffff880116801e00
    [ 3035.446741] RBP: ffff8800db9bfe90 R08: 000000000001a020 R09: ffffffffc03e615c
    [ 3035.447305] R10: ffffea0003653180 R11: 000000000000027d R12: ffff8800d94c6400
    [ 3035.447842] R13: 0000000001e05408 R14: 0000000000000002 R15: 0000000000000000
    [ 3035.448374] FS:  00007f2dc4769700(0000) GS:ffff88011b500000(0000) knlGS:0000000000000000
    [ 3035.448945] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
    [ 3035.449484] CR2: 00007ffed043f1b0 CR3: 00000000d5f6f000 CR4: 00000000000406e0
    [ 3035.450035] Stack:
    [ 3035.450573]  ffff8800344a4a80 fffffffffffffffb ffff8800db9bff18 ffff8800db9bfeb0
    [ 3035.451152]  ffffffff8127bee2 ffff8800da949b00 0000000001e05408 ffff8800db9bfec0
    [ 3035.451730]  ffffffff8120e168 ffff8800db9bff00 ffffffff8120eaf9 ffffffff810caeb1
    [ 3035.452368] Call Trace:
    [ 3035.452911]  [<ffffffff8127bee2>] proc_reg_write+0x42/0x70
    [ 3035.453545]  [<ffffffff8120e168>] __vfs_write+0x18/0x40
    [ 3035.454400]  [<ffffffff8120eaf9>] vfs_write+0xa9/0x1a0
    [ 3035.455002]  [<ffffffff810caeb1>] ? __raw_callee_save___pv_queued_spin_unlock+0x11/0x20
    [ 3035.455525]  [<ffffffff8120f7b5>] SyS_write+0x55/0xc0
    [ 3035.456044]  [<ffffffff818385f2>] entry_SYSCALL_64_fastpath+0x16/0x71
    [ 3035.456587] Code: 74 29 7e 20 83 f8 03 74 11 83 f8 04 75 11 48 c7 c7 e0 70 3e c0 e8 c5 6f da c0 e8 7c 1a 01 c1 48 89 d8 eb 9c 83 e8 01 75 f6 0f 0b <0f> 0b 0f 1f 40 00 66 2e 0f 1f 84 00 00 00 00 00 0f 1f 44 00 00 
    [ 3035.458285] RIP  [<ffffffffc03e6190>] my_proc_write+0xb0/0xc0 [mybugondriver]
    [ 3035.458821]  RSP <ffff8800db9bfe78>
    [ 3035.459413] ---[ end trace 064cb0dbcc2892d5 ]---



::

    $ echo 3 > /proc/my_bugon_driver
    $ dmesg
     param has been set to 3
    [ 3097.627769] CPU: 1 PID: 4846 Comm: bash Tainted: G      D    OE   4.4.0-62-generic #83-Ubuntu
    [ 3097.628428] Hardware name: innotek GmbH VirtualBox/VirtualBox, BIOS VirtualBox 12/01/2006
    [ 3097.629052]  0000000000000286 00000000f2a77aaf ffff880035737e68 ffffffff813f7c63
    [ 3097.629676]  0000000000000002 ffff8800d94c6780 ffff880035737e90 ffffffffc03e6184
    [ 3097.630283]  ffff8800344a4a80 fffffffffffffffb ffff880035737f18 ffff880035737eb0
    [ 3097.630882] Call Trace:
    [ 3097.631464]  [<ffffffff813f7c63>] dump_stack+0x63/0x90
    [ 3097.632046]  [<ffffffffc03e6184>] my_proc_write+0xa4/0xc0 [mybugondriver]
    [ 3097.632587]  [<ffffffff8127bee2>] proc_reg_write+0x42/0x70
    [ 3097.633036]  [<ffffffff8120e168>] __vfs_write+0x18/0x40
    [ 3097.633480]  [<ffffffff8120eaf9>] vfs_write+0xa9/0x1a0
    [ 3097.633917]  [<ffffffff810caeb1>] ? __raw_callee_save___pv_queued_spin_unlock+0x11/0x20
    [ 3097.634411]  [<ffffffff8120f7b5>] SyS_write+0x55/0xc0
    [ 3097.634854]  [<ffffffff818385f2>] entry_SYSCALL_64_fastpath+0x16/0x71



The following command will panic the machine ``echo 4 > /proc/my_bugon_driver``

