/*
 * <PD> Hello World Module </PD>
 */

#include <linux/module.h>
#include <linux/init.h>

/*
 * This is the starting point of the kernel module's code execution.
 * Right now we will just print a hello and return from here.
 */

static int __init my_init(void)
{
	printk(KERN_INFO "Hello from Hello Module");
	return 0;
}

/*
 * This is the exit point of the kernel module. When the module is removed 
 * this function is called to do any sort of cleanup activities and other such
 *  stuff.
 * 
 * For example you have made a tree where you keep someinformation - you would 
 * like to place the code for removing the nodes of the tree here.
 */

static void __exit my_exit(void)
{
	printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION("Sample Hello World Module");
MODULE_AUTHOR("Rishi Agrawal <rishi.b.agrawal@gmail.com>");
MODULE_LICENSE("GPL");
