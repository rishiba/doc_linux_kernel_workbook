/*
 * Module to create a proc entry. The user can read and write to the proc entry.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/types.h>

#define DATA_SIZE 1024 // We can keep 1024 bytes of data with us.
#define MY_PROC_ENTRY "my_proc_entry_write"
#define PROC_FULL_PATH "/proc/my_proc_entry_write"

struct proc_dir_entry *proc;
int len;
char *msg = NULL;

/*
 * Function to write to the proc. Here we free get the new value from buffer,
 * count from the buffer and then overwrite the data in our file.
 *
 * Note that - you can have any other implementation as well for this, all you have to
 * ensure that you comply with the expectations of the write() system calls
 * like filling in the buffer, and returning the numbers of character written.
 */

static ssize_t my_proc_write(struct file *filp, const char __user * buffer, size_t count, loff_t *pos)
{
    int i;
    char *data = PDE_DATA(file_inode(filp));

    if (count > DATA_SIZE) {
        return -EFAULT;
    }

    printk(KERN_INFO "Printing the data passed. Count is %lu", (size_t) count);
    for (i=0; i < count; i++) {
        printk(KERN_INFO "Index: %d . Character: %c Ascii: %d", i, buffer[i], buffer[i]);
    }

    printk(KERN_INFO "Writing to proc");
    if (copy_from_user(data, buffer, count)) {
        return -EFAULT;
    }

    data[count-1] = '\0';

    printk(KERN_INFO "msg has been set to %s", msg);
    printk(KERN_INFO "Message is: ");
    for (i=0; i < count; i++) {
        printk(KERN_INFO "\n Index: %d . Character: %c", i, msg[i]);
    }

    *pos = (int) count;
    len = count-1;

    return count;
}

/*
 * Function to read the proc entry, here we copy the data from our proc entry 
 * to the buffer passed.
 */

ssize_t my_proc_read(struct file *filp,char *buf, size_t count, loff_t *offp )
{
    int err;
    char *data = PDE_DATA(file_inode(filp));

    if ((int) (*offp) > len) {
        return 0;
    }

    printk(KERN_INFO "Reading the proc entry, len of the file is %d", len);
    if(!(data)) {
        printk(KERN_INFO "NULL DATA");
        return 0;
    }

    if (count == 0) {
        printk(KERN_INFO "Read of size zero, doing nothing.");
        return count;
    } else {
        printk(KERN_INFO "Read of size %d", (int) count);
    }

    count = len + 1; // +1 to read the \0
    err = copy_to_user(buf, data, count); // +1 for \0
    printk(KERN_INFO "Read data : %s", buf);
    *offp = count;

    if (err) {
        printk(KERN_INFO "Error in copying data.");
    } else {
        printk(KERN_INFO "Successfully copied data.");
    }

    return count;
}


/*
 * The file_operations structure. This is the glue layer which associates the
 * proc entry to the read and write operations.
 */
struct file_operations proc_fops = {
    .read = my_proc_read,
    .write = my_proc_write,
};


/*
 * This function will create the proc entry. This function will allocate some
 * data where the data will be written incase of a write to the proc entry. The
 * same memory will be used to serve the reads.  * Initially the function fills
 * the data with DATA which has "Hello People".

 * The important function to see here is the proc_create_data, this function
 * will take the proc entry name and create it with the given permissions
 * (0666). We also need to pass the file_operations structure which has the
 * function pointers to the functions which needs to be called when read or
 * write is called on the file. The last argument has the pointer to the data
 * associated with the file.
 */

int create_new_proc_entry(void) {
    int i;
    char *DATA = "Hello People";
    len = strlen(DATA);
    msg = kmalloc((size_t) DATA_SIZE, GFP_KERNEL); // +1 for \0

    if (msg != NULL) {
        printk(KERN_INFO "Allocated memory for msg");
    } else {
        return -1;
    }

    strncpy(msg, DATA, len+1);
    for (i=0; i < len +1 ; i++) {
        printk(KERN_INFO "%c", msg[i]);
        if (msg[i] == '\0') {
            printk(KERN_INFO "YES");
        }
    }
    proc = proc_create_data(MY_PROC_ENTRY, 0666, NULL, &proc_fops, msg);
    if (proc) {
        return 0;
    }
    return -1;
}


/* The init function of the module. Does nothing other than calling the
 * create_new_proc_entry. */

int proc_init (void) {
    if (create_new_proc_entry()) {
        return -1;
    }
    return 0;
}

/* Function to remove the proc entry.  Call this when the module unloads. */
void proc_cleanup(void) {
    remove_proc_entry(MY_PROC_ENTRY, NULL);
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);
