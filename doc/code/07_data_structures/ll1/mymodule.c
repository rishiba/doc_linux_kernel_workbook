/*
 * Module to show how to use the kernel linked list for managing data
 * 1. Add node to linked list
 * 2. Print the list
 * 3. Delete nodes from the list
 * The modules exposes a /proc interface on which if you cat 
 * 1. add 5 -- it adds five
 * 2. print -- it prints the linked list
 * 3. delete 5 -- it deletes the node in the linked list
 * 4. destroy -- destroys the whole linked list
 */

#include "ll.h"
extern struct proc_dir_entry *proc;
extern struct list_head todo_list;
static int __init my_init(void)
{

   printk(KERN_INFO "Hello from Linked List Module");

   if (ll_proc_init()) {
      printk(KERN_INFO "Falied to create the proc interface");
      return -EFAULT;
   }

   INIT_LIST_HEAD(&todo_list);
   return 0;
}

static void __exit my_exit(void)
{
   if (proc) {
      proc_cleanup();
      pr_info("Removed the entry");
   }
   printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("abr");
