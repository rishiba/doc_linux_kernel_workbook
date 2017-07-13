/*
 * <PD> Calculator  with parameters </PD>
 */
#include <linux/module.h>
#include <linux/init.h>

struct sample {
    int x, y;
};

void print_sample_struct(struct sample temp) {
    printk (KERN_INFO "\nx is %d y is %d", temp.x, temp.y);
}


/*
 * Variable for integer parameter
 */
int param1;
module_param(param1, int, 0);

int param2;
module_param(param2, int, 0);

void calculator(int a, int b) {
    int *ptra = &a;
    int i;

    struct sample temp;
    temp.x = 10;
    temp.y = 20;

    printk (KERN_INFO "\nSum is           %d", a+b);
    printk (KERN_INFO "\nDifference is    %d", a-b);
    printk (KERN_INFO "\nProduct is       %d", a*b);
    printk (KERN_INFO "\nDivison is       %d", a/b);
    printk (KERN_INFO "\nMod is           %d", a%b);
    printk (KERN_INFO "\nBitwise NOT of %d Is   %d", a, ~a);
    printk (KERN_INFO "\nBitwise OR is    %d", a|b);
    printk (KERN_INFO "\nBitwise AND is   %d", a&b);
    printk (KERN_INFO "\nBitwise XOR Is   %d", a^b);
    printk (KERN_INFO "\nLogical OR Is    %d", a||b);
    printk (KERN_INFO "\nLogical AND Is   %d", a&&b);


    if (a>b) {
        printk (KERN_INFO "\n%d is greater than %d", a, b);
    } else if (b>a) {
        printk (KERN_INFO "\n%d is greater than %d", b, a);
    } else {
        printk (KERN_INFO "\n%d is equal to %d", b, a);
    }


    printk (KERN_INFO "\nAddress of a is %p", ptra);
    printk (KERN_INFO "\nValue of ptra is %d", *ptra);

    /*
     * You can have loops as well.
     */

    for (i = b; i <=a; i++) {
        printk (KERN_INFO "\nPrinting i %d", i);
    }

    /*
     * You can have structures as well.
     */

    print_sample_struct(temp);
    
}

/*
 * This is the starting point of the kernel module's code execution.
 * Right now we will just print a hello and return from here.
 */

static int __init my_init(void)
{
    /*
     * Variable for integer parameter
     */
	printk(KERN_INFO "Hello from Hello Module");
    
    calculator(param1, param2);
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

MODULE_DESCRIPTION("Calculator with parameters.");
MODULE_AUTHOR("Rishi Agrawal <rishi.b.agrawal@gmail.com>");
MODULE_LICENSE("GPL");
