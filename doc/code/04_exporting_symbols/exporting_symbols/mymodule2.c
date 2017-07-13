/*
 * <PD> Module 2 for exporting symbol demostration </PD>
 */
#include <linux/module.h>
#include <linux/init.h>

extern void print_hello(int);
extern void add_two_numbers(int, int);
extern int GLOBAL_VARIABLE;

/*
 * The function has been written just to call the functions which are in other module. This way you can also write modules which does provide some functionality to the other modules.
 */
static int __init my_init(void)
{
    printk(KERN_INFO "Hello from Hello Module");
    print_hello(10);
    add_two_numbers(5, 6);
    printk(KERN_INFO "Value of GLOBAL_VARIABLE %d", GLOBAL_VARIABLE);
    return 0;
}

static void __exit my_exit(void)
{
    printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION("Module to demonstrate the EXPORT_SYMBOL functionality");
MODULE_AUTHOR("Rishi Agrawal <rishi.b.agrawal@gmail.com>");
MODULE_LICENSE("GPL v2");
