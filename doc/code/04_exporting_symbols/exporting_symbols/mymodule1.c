/*
 * <PD> Module 1 for demonstration of circular dependancy </PD>
 */
#include <linux/module.h>
#include <linux/init.h>

int GLOBAL_VARIABLE = 1000;

EXPORT_SYMBOL(GLOBAL_VARIABLE);

/*
 * Function to print hello for num times.
 */
void print_hello(int num)
{
	while (num--) {
		printk(KERN_INFO "Hello Friend!!!\n");
	}
}
EXPORT_SYMBOL(print_hello);

/*
 * Function to add two passed number.
 */
void add_two_numbers(int a, int b)
{
	printk(KERN_INFO "Sum of the numbers %d", a + b);
}

EXPORT_SYMBOL(add_two_numbers);

static int __init my_init(void)
{
	printk(KERN_INFO "Hello from Export Symbol 1 module.");
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Bye from Export Symbol 1 module.");
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION("Module to demonstrate the EXPORT_SYMBOL functionality");
MODULE_AUTHOR("Rishi Agrawal <rishi.b.agrawal@gmail.com");
MODULE_LICENSE("GPL v2");
