/*
 * <PD> Program to demonstrate arrays and strings for module paramters. </PD>
 */
#include <linux/module.h>
#include <linux/init.h>

#define DEFAULT_PARAM1 100
#define ARRAY_LEN 5
#define STRING_LEN 10

/*
 * Variable for integer parameter
 */
int param1 = DEFAULT_PARAM1;
module_param(param1, int, S_IRUGO | S_IWUSR);

/*
 * Variable for named parameters
 */
static int for_myself = 42;
module_param_named(for_world, for_myself, int, 0444);
MODULE_PARM_DESC(for_world, "For the world");

/*
 * Variable for integer array
 */
static int int_array[ARRAY_LEN];
int array_len;
module_param_array(int_array, int, &array_len, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(int_array, "Integer array for doing nothing");

/*
 * Variable for strings
 */
char test[STRING_LEN];
module_param_string(test_string, test, STRING_LEN, S_IRUGO | S_IWUSR);

static int __init my_init(void)
{
   int i = 0;
   printk(KERN_INFO "\nHello from Hello Module\n");
   printk(KERN_INFO "\nPassed Parameters\n");

   /*
    * Print the parameters passed
    */
   if (param1 == DEFAULT_PARAM1) {
      printk(KERN_INFO
             "\nNothing Passed or Default Value %d for param1 \
                              passed\n",
             DEFAULT_PARAM1);
   } else {
      printk(KERN_INFO "\nParam1 passed is %d", param1);
   }

   /*
    * Module Parameter named - see the file 
    * /sys/module/-module-name-/parameters
    */
   printk(KERN_INFO "\nValue of for_myself is %d", for_myself);

   /*
    * Integer array as a parameter
    */
   for (i = 0; i < array_len; i++) {
      printk(KERN_INFO "Interger Array element %d is %d", i,
             int_array[i]);
   }

   /*
      Print the Character array
    */
   printk(KERN_INFO "\nThe character array passed %s", test);
   return 0;
}

static void __exit my_exit(void)
{
   printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION("module to demonstrate module parameters");
MODULE_AUTHOR("abr");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0");
