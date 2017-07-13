/*
 * Make a directory entry in the proc file system and have two 
 * parameters in the directory.
 * Make proc directory entry as 
 * /proc/my_proc_dir/param_1
 * /proc/my_proc_dir/param_2
 * Implement only the read functions of the entries.
 * Use simple read and write - do not use seq_files.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/seq_file.h>

#define MY_PROC_DIR "my_proc_dir"
#define MY_PROC_ENTRY "info"

static int myproc_show (struct seq_file *m, void *v) {
        seq_printf(m, "%llu\n", (unsigned long long) 54);
        return 0;
}

static ssize_t my_proc_write(struct file *file, const char __user * buffer, size_t count, loff_t *pos)
{
   char *str;
   int param;
   pr_info("Writing to proc");
//   str = kmalloc((size_t) count, GFP_KERNEL);
//   if (copy_from_user(str, buffer, count)) {
//      kfree(str);
//      return -EFAULT;
//   }
//   sscanf(str, "%d", &param);
//   pr_info("param has been set to %d\n", param);
//   kfree(str);
   return 10;
}

static int myproc_open(struct inode *inode, struct file *file) {
        return single_open(file, myproc_show, NULL);
}

struct file_operations my_file_operations = {
        .open = myproc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
        .write = my_proc_write,
};

int n = 10;

static int __init my_init(void)
{
        struct proc_dir_entry *basedir = proc_mkdir(MY_PROC_DIR, NULL);
        if (basedir) {
                pr_info("Succeeded in making a directory entry");
                proc_create_data(MY_PROC_ENTRY, 0777, basedir, &my_file_operations, (void *) (&n));
                return 0;
        } else {
                return -1;
        }
}

static void __exit my_exit(void)
{
        remove_proc_subtree(MY_PROC_DIR, NULL);
        printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("abr");
MODULE_LICENSE("GPL");
