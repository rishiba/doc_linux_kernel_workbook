/*
 * <PD> Make a entry  /proc/driver/my_debug and call BUG() BUG_ON() 
 * dump_stack() or panic() based on user's input </PD>
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define NODE "driver/my_mod1"

#define MY_BUG_ON 1
#define MY_BUG 2
#define MY_DUMPSTACK 3
#define MY_PANIC 4

static struct proc_dir_entry *my_proc;
static int param = 100;

static int my_proc_read(char *page, char **start, off_t off,
			int count, int *eof, void *data)
{
	*eof = 1;
	return sprintf(page, "%d\n", param);
}

static int my_proc_write(struct file *file,
			 const char __user * buffer,
			 unsigned long count, void *data)
{
	char *str;
	str = kmalloc((size_t) count, GFP_KERNEL);
	if (copy_from_user(str, buffer, count)) {
		kfree(str);
		return -EFAULT;
	}
	sscanf(str, "%d", &param);
	pr_info("param has been set to %d\n", param);
	kfree(str);

	switch (param) {
	case MY_BUG_ON:
		BUG_ON(param);
		break;
	case MY_BUG:
		BUG();
		break;
	case MY_DUMPSTACK:
		dump_stack();
		break;
	case MY_PANIC:
		panic("I am panicking, Why? -- you told so");
		break;
	}
	return count;
}

static int __init my_init(void)
{
	printk(KERN_INFO "Hello from Hello Module");

	if (!
	    (my_proc =
	     create_proc_entry(NODE, S_IRUGO | S_IWUSR, NULL))) {
		printk(KERN_INFO
		       "Failed to make the required proc entry");
		return -1;
	}

	pr_info("I created the entry");
	my_proc->read_proc = my_proc_read;
	my_proc->write_proc = my_proc_write;
	return 0;
}

static void __exit my_exit(void)
{
	if (my_proc) {
		remove_proc_entry(NODE, NULL);
		pr_info("Removed the entry");
	}
	printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("abr");
MODULE_LICENSE("GPL v2");
