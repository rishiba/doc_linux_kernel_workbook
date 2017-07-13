/*
 * <PD> String functions available in the kernel. </PD>
 */
#include <linux/module.h>
#include <linux/init.h>
#include <string.h>

static int __init my_init(void)
{
    char str1[20] = "Hello";
    char str2[20] = "World";
    char *dest  = NULL;

    dest = strcat(str1, str2);
    printk(KERN_INFO "Concated String is %s", dest);
    return 0;
}

static void __exit my_exit(void)
{
        printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION("Sample Module using string functions.");
MODULE_AUTHOR("Rishi Agrawal <rishi.b.agrawal@gmail.com>");
MODULE_LICENSE("Apache");
