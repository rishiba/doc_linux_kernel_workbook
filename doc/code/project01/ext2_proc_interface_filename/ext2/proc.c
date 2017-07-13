/*
 *  * Make a entry  /proc/driver/my_mod1 and write something to it.
 *   */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/mount.h>
#include <linux/path.h>

#define NODE_ENTRY "driver/ext2_linuxKernel101_3"

static struct proc_dir_entry *ext2_proc_entry, *ext2_proc_dir;

static int ext2_proc_read(char *page, char **start, off_t off, \
                int count, int *eof, void *data)
{
    
   return -EINVAL;
}


void ext2_proc_print_inode_details(unsigned int inum) {
   printk(KERN_INFO "Print inode details of %u\n", inum);
}

int ext2_proc_print_file_details(char *filename) {

    struct path path;
    struct super_block *sb = NULL;
    struct inode *inode = NULL;
    int res;
    printk(KERN_INFO "Print file details of %s\n", filename);
    res=kern_path(filename, LOOKUP_FOLLOW , &path);
    if (res) {
            printk(KERN_INFO "Error, seems that the file is not 
                            present\n");
            goto err;
    }
    if (path.mnt && path.mnt->mnt_sb) {
        printk(KERN_ERR "superblock filled");
        sb = path.mnt->mnt_sb;
    } else {
        printk(KERN_ERR "superblock empty");
        return 0;
    }
    /*
     * Approach 1
     * Directly get the dentry and print the inode details
     */
    if(path.dentry) {
        inode = path.dentry->d_inode;
        if (inode) {
            printk(KERN_ALERT "inode num %lu \n", inode->i_ino);
        } else {
            printk(KERN_ERR "inode not found");
        }
    }
err:
    return -1; 

}

void ext2_proc_print_all_inodes(void) {
   printk(KERN_INFO "Print all the inodes in the file system\n");
}

/*
 * This should be based per file system and error checkings hould be 
   present, locking too, but as it just for demostrtation, we are 
   skpping those.
 */
static int ext2_proc_write(struct file *file, 
                const char __user * buffer,
                unsigned long count, void *data)
{
   char *str;
   unsigned int inum=0;
   char filename[40], command[40];
   str = kmalloc((size_t) count, GFP_KERNEL);
   if (copy_from_user(str, buffer, count)) {
      kfree(str);
      return -EFAULT;
   }

   sscanf(str, "%s", command);
   printk("First Arguement %s\n", command);

   if (!strcmp(command, "print_inode_details")) {
      sscanf(str, "%s %u", command, &inum);
      printk(KERN_INFO "Printing data of inode number%u\n", inum);
      ext2_proc_print_inode_details(inum);
   }   

   if (!strcmp(command, "print_file_details")) {
      sscanf(str, "%s %s", command, filename);
      printk(KERN_INFO "Printing details of file  %s\n", filename);
      if (!(ext2_proc_print_file_details(filename))) {
                        printk(KERN_INFO "Could not find the file\n");
                } else {
                        printk(KERN_INFO "Printed the file details\n");
                }
   }   


   if (!strcmp(command, "print_all_inodes")) {
      printk(KERN_INFO "Printing the linked list\n");
      ext2_proc_print_all_inodes();
   }   
   return count;
}


int ext2_init_proc_interface(void)
{
   printk(KERN_INFO "Hello from Proc Interface of ext2 module");
    /* Make the entry */
   ext2_proc_entry = create_proc_entry(NODE_ENTRY, S_IRUGO | S_IWUSR, NULL);
   if (ext2_proc_entry == NULL) {
      printk(KERN_INFO "Failed to make the required proc entry");
      return -1;
   } else {
      pr_info("I created the entry");
   }
   /*  Set the procedures for the proc_file */
    ext2_proc_entry->read_proc = ext2_proc_read;
    ext2_proc_entry->write_proc = ext2_proc_write;
    return 0;
}

void ext2_proc_remove(void)
{

    printk(KERN_INFO "Removing the proc entry");
    if (ext2_proc_entry) {
        remove_proc_entry(NODE_ENTRY, NULL);
        pr_info("Removed the entry");
    }
}
