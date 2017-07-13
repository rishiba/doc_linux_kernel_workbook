// Module to make a read entry in the proc file system.
// Module to write a command line calculator

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/types.h>

#include "myproc.h"

struct proc_dir_entry *proc;
int len;
char *msg;

int bytes_read;

/*
 * Here you have the find the data where we have stored the related information
 * and then copy the data to the user space buffer which is passed by the read
 * system call.
 *
 * We also need to update the offset to the amount of data read.
 *
 * Read system call should also return the amount of data read, which should be
 * less than or equal to count but not be more than the count.
 */

ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp) 
{
    int err;
    char *data = PDE_DATA(file_inode(filp));

    if ((int) (*offp) > len) {
        return 0;
    }

    if(!(data)) {
        printk(KERN_INFO "NULL DATA");
        return 0;
    }

    if (count == 0) {
        printk(KERN_INFO "Read of size zero, doing nothing.");
        return count;
    }

    count = len + 1; // +1 to read the \0
    err = copy_to_user(buf, data, count+1); // +1 for \0
    *offp = count;

    if (err) {      
        printk(KERN_INFO "Error in copying data.");
    } else {
        printk(KERN_INFO "Successfully copied data.");
    }

    return count;
}

/*
 * Operations for the reading the proc entry. When we will implement write 
 * we will add the function for writing as well.
 */

struct file_operations proc_fops = {
    .read = read_proc,
};


/*
 * Function to create the entry.
 */

void create_new_proc_entry(void) {
    msg = "Hello World";
    proc = proc_create_data(MY_PROC_ENTRY, 0, NULL, &proc_fops, msg);
    len = strlen(msg);
}

int proc_init (void) {
    create_new_proc_entry();
    return 0;
}

void proc_cleanup(void) {
    remove_proc_entry(MY_PROC_ENTRY, NULL);
}

MODULE_LICENSE("GPL"); 
module_init(proc_init);
module_exit(proc_cleanup);
