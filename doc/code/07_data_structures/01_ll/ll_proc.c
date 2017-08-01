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


#include "ll.h"
struct proc_dir_entry *proc;
int len,temp;
char *msg;

#define PROC_NAME "linked_list"

ssize_t my_proc_write(struct file *filp, const char __user * buffer, size_t count, loff_t *pos)
{
   char *str;
   char command[20];
   int val = 0;

   printk("Calling Proc Write");
   str = kmalloc((size_t) count, GFP_KERNEL);
   if (copy_from_user(str, buffer, count)) {
      kfree(str);
      return -EFAULT;
   }

   sscanf(str, "%s %d", command, &val);
   printk("First Arguement %s\n", command);
   printk("Second Argument %d\n", val);

   if (!strcmp(command, "add")) {
      /* Add node */
      printk(KERN_INFO "Adding data to linked list %d\n", val);
      todo_add_entry(val);
   }

   if (!strcmp(command, "delete")) {
      /* Delete Node */
      printk(KERN_INFO "Deleting node from linked list %d\n", val);
      if (delete_node(val)) {
         printk(KERN_INFO "Delete failed \n");
      }
   }

   if (!strcmp(command, "print")) {
      /* Print the linked list */
      printk(KERN_INFO "Printing the linked list\n");
      show_list();
   }

   kfree(str);
   return count;
}

ssize_t my_proc_read (struct file *filp,char *buf,size_t count,loff_t *offp ) 
{
        char *data;
        int err;
        data=PDE_DATA(file_inode(filp));
        if(!(data)){
                printk(KERN_INFO "Null data");
                return 0;
        }

        if(count>temp) {
                count=temp;
        }

        temp=temp-count;

        err = copy_to_user(buf,data, count);
        if (err) {      
                printk(KERN_INFO "Error in copying data.");
        }

        if(count==0) {
                temp=len;
        }

        return count;
}

struct file_operations proc_fops = {
    .read = my_proc_read,
    .write = my_proc_write,
};

int create_new_proc_entry(void) {
        msg="Hello World";
        proc=proc_create_data(PROC_NAME, 0666, NULL, &proc_fops, msg);
        len=strlen(msg);
        temp=len;
        if (proc) {
            return 0;
        } else {
            return -1;
        }
}

int ll_proc_init (void) {
        create_new_proc_entry();
        return 0;
}

void proc_cleanup(void) {
        remove_proc_entry("hello", NULL);
}

