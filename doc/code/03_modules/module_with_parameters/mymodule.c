/*
 * <PD> Program to add the passed parameters to a kernel module </PD>
 */
#include <linux/module.h>
#include <linux/init.h>

#define DEFAULT_PARAM1 100
#define DEFAULT_PARAM2 200

/*
 * Variable for integer parameter
 */
int param1 = DEFAULT_PARAM1;
int param2 = DEFAULT_PARAM2;

/* 
 * Get the parameters.
 */
module_param(param2, int, 0);
module_param(param1, int, 0);

static int __init my_init(void)
{
   printk(KERN_INFO "\nHello !! from Paramter Passing Demo Module\n");

   /*
    * Print the parameters passed
    */
   
   printk(KERN_INFO "\nThe sum of the parameters are :%d:", param1 + param2);
   
   printk(KERN_INFO "\nPassed Parameters\n");
   
   if (param1 == DEFAULT_PARAM1) {
      printk(KERN_INFO "\nNothing Passed OR Default Value :%d: for param1 is Passed\n", DEFAULT_PARAM1);
   } else {
      printk(KERN_INFO "\nparam1 passed is :%d:", param1);
   }

   if (param1 == DEFAULT_PARAM2) {
      printk(KERN_INFO "\nNothing Passed OR Default Value :%d: for param1 Passed\n", DEFAULT_PARAM2);
   } else {
      printk(KERN_INFO "\nparam2 passed is :%d:", param2);
   }

   return 0;
}

static void __exit my_exit(void)
{
   printk(KERN_INFO "\nBye from Parameter Passing Demo Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION("Module To Demonstrate Module Parameters");
MODULE_AUTHOR("rishi.b.agrawal@gmail.com");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0");
