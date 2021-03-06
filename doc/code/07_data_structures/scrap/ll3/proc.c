#include "ll.h"

struct proc_dir_entry *my_proc;

/*
 * read function for the proc entry, reading of it is invalid
 */
int my_proc_read(char *page, char **start, off_t off, int count, int *eof,
		 void *data)
{
	return -EINVAL;
}

/*
 * Function to make proc entry
 */
int configure_proc_entry(void)
{

	if (!(my_proc = create_proc_entry(NODE, S_IRUGO | S_IWUSR, NULL))) {
		printk(KERN_INFO "Failed to make the required proc entry\n");
		return -1;
	}

	pr_info("I created the entry\n");
	my_proc->read_proc = my_proc_read;
	my_proc->write_proc = my_proc_write;
	return 0;
}

/*
 * Function for writing to my proc entry
 */
int my_proc_write(struct file *file, const char __user * buffer,
		  unsigned long count, void *data)
{
	char *str;
	char command[20];
	int val = 0;
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

	if (!strcmp(command, "destroy")) {
		/* Destroy the linked list */
		printk("Destroying the linked list\n");
		destroy();

	}

	kfree(str);
	return count;
}
