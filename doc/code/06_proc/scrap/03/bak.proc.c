/*
 * Make a directory entry in the proc file system and have two 
 * parameters in the directory.
 * Make proc directory entry as 
 * /proc/my_proc_dir/param_1
 * /proc/my_proc_dir/param_2
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define NODE1 "param_1"
#define NODE2 "param_2"
#define NODE_DIR "my_proc_dir"

static struct proc_dir_entry *my_proc_dir, *my_proc_1, *my_proc_2;
static int param_1 = 100, param_2 = 200;

int my_proc_read(char *page, char **start, off_t off, int count, 
                 int *eof, void *data)
{
	if (data == my_proc_1) {
		return sprintf(page, "%d\n", param_1);

	} else if (data == my_proc_2) {
		return sprintf(page, "%d\n", param_2);
	}
	return -EINVAL;
}

int my_proc_write(struct file *file, const char __user * buffer,
		  unsigned long count, void *data)
{
	char *str = kmalloc((size_t) count, GFP_KERNEL);

	if (copy_from_user(str, buffer, count)) {
		kfree(str);
		return -EFAULT;
	}

	if (data == my_proc_1) {
		sscanf(str, "%d", &param_1);
		pr_info("Written the value to the param_1");
		kfree(str);
		return (count);
	}

	if (data == my_proc_2) {
		sscanf(str, "%d", &param_2);
		pr_info("Written the value to param_2");
		kfree(str);
		return count;
	}

	kfree(str);
	return -EINVAL;

}

static int __init my_init(void)
{
	printk(KERN_INFO "Hello from Hello Module");

	if (!(my_proc_dir = proc_mkdir(NODE_DIR, NULL))) {
		pr_err("Failed to make the directory entry");
		return -1;
	}
	pr_info("Succeeded in making a directory entry");

	if (!
	    (my_proc_1 =
	     create_proc_entry(NODE1, S_IRUGO | S_IWUSR, \
                                 my_proc_dir))) {
		pr_info("failed to make the directory entry");
		remove_proc_entry(NODE_DIR, NULL);
		return -1;
	}

	pr_info("I created the directory entry");

	my_proc_1->read_proc = my_proc_read;
	my_proc_1->write_proc = my_proc_write;
	my_proc_1->data = my_proc_1;

	if (!
	    (my_proc_2 =
	     create_proc_entry(NODE2, S_IRUGO | S_IWUSR, \
                my_proc_dir))) {
		pr_info("Failed to create the second entry");
		remove_proc_entry(NODE1, NULL);
		remove_proc_entry(NODE_DIR, NULL);
	}

	my_proc_2->read_proc = my_proc_read;
	my_proc_2->write_proc = my_proc_write;
	my_proc_2->data = my_proc_2;

	return 0;
}

static void __exit my_exit(void)
{

	printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("abr");
