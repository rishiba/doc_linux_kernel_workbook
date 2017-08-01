/*
 * The program makes /proc/driver/my_mod_3
 * Based on the contents written on the interface functions are called.
 * 1 -- hello_world
 * 2 -- hello_people
 * 3 -- hello_mars
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define NODE "driver/my_mod_3"

#define HELLO_PEOPLE 1
#define HELLO_WORLD 2
#define HELLO_MARS 3

static struct proc_dir_entry *my_proc;
static int param = 100;

static void hello_people(void)
{
	int i = 0;
	for (i = 0; i < 5; i++) {
		pr_info("Hello People !!!");
	}
}

static void hello_world(void)
{
	int i = 0;
	for (i = 0; i < 5; i++) {
		pr_info("Hello World !!!");
	}

}

static void hello_mars(void)
{
	int i = 0;
	for (i = 0; i < 5; i++) {
		pr_info("Hello Mars !!!");
	}

}

static int my_proc_read(char *page, char **start, off_t off, int count,
			int *eof, void *data)
{
	*eof = 1;
	return sprintf(page, "%d\n", param);
}

static int my_proc_write(struct file *file, const char __user * buffer,
			 unsigned long count, void *data)
{
	char *str;
	str = kmalloc((size_t) count, GFP_KERNEL);
	if (copy_from_user(str, buffer, count)) {
		kfree(str);
		return -EFAULT;
	}
	sscanf(str, "%d", &param);
	kfree(str);

	switch (param) {
	case HELLO_WORLD:
		hello_world();
		break;

	case HELLO_PEOPLE:
		hello_people();
		break;

	case HELLO_MARS:
		hello_mars();
		break;

	default:
		pr_info("User entered a wrong value");
	}

	return count;
}

static int __init my_init(void)
{
	printk(KERN_INFO "Hello from Hello Module");

	if (!(my_proc = create_proc_entry(NODE, S_IRUGO | S_IWUSR, NULL))) {
		printk(KERN_INFO "Failed to make the required proc entry");
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
