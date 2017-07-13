#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/mount.h>
#include <linux/path.h>
#include "ext2.h"

#define NODE_ENTRY "driver/ext2_linuxKernel101"
static struct proc_dir_entry *ext2_proc_entry;
static int ext2_proc_read(char *page, char **start, off_t off, int count,
            int *eof, void *data)
{
    
	return -EINVAL;
}

int ext2_proc_print_inode_details(char *mntpnt, unsigned int inum) {
   struct path path;
   struct super_block *sb = NULL;
   struct inode *inode = NULL;
   int res;
	struct ext2_inode_info *ei=NULL;
   printk(KERN_INFO "Print file details of %s\n on moun", mntpnt);
   res=kern_path(mntpnt, LOOKUP_FOLLOW , &path);
   if (res) {
      printk(KERN_INFO "Error, seems that the file is not\
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
   printk(KERN_INFO "Print inode details of %u\n", inum);
   inode = iget_locked(sb, inum);
   if (inode) {
      printk(KERN_ALERT "inode num \"%lu\"\n", inode->i_ino);
	   ei = EXT2_I(inode);
	 printk(KERN_INFO "MUID is \"%u\"\n", ei->muid);
   } else {
      printk(KERN_ERR "inode not found");
   }
   unlock_new_inode(inode);
   return 0;
err:
	return -1;   
}

int ext2_proc_print_file_details(char *filename) {
   struct path path;
   struct super_block *sb = NULL;
   struct inode *inode = NULL;
	struct ext2_inode_info *ei=NULL;;
   int res;
   printk(KERN_INFO "Print file details of %s\n", filename);
   res=kern_path(filename, LOOKUP_FOLLOW , &path);
   if (res) {
      printk(KERN_INFO "Error, seems that the file is not\
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
   if(path.dentry) {
      inode = path.dentry->d_inode;
      if (inode) {
         printk(KERN_ALERT "inode num \"%lu\"\n", inode->i_ino);
	 ei = EXT2_I(inode);
	 printk(KERN_INFO "MUID is \"%u\"\n", ei->muid);
      } else {
         printk(KERN_ERR "inode not found");
      }
   }
   path_put(&path);
   return 0;
err:
   return -1; 

}

void ext2_proc_print_all_inodes(void) {
	printk(KERN_INFO "Print all the inodes in the file system\n");
}

/* This should be based per file system and error checkings hould 
   be present, locking too, but as it * just for demostrtation, 
   we skip those */

static int ext2_proc_write(struct file *file, const char __user * buffer,
		unsigned long count, void *data)
{
	char *str;
	unsigned int inum=0;
	char path[40], command[40];
	str = kmalloc((size_t) count, GFP_KERNEL);
	if (copy_from_user(str, buffer, count)) {
		kfree(str);
		return -EFAULT;
	}

	sscanf(str, "%s", command);
	printk("First Arguement %s\n", command);

	if (!strcmp(command, "PID")) {
		sscanf(str, "%s %s %u", command, path, &inum);
		printk(KERN_INFO "Printing data of inode number%u mountpoint \
                      %s\n", inum, path);
		ext2_proc_print_inode_details(path, inum);
		return count;
	}
	if (!strcmp(command, "PFD")) {
		sscanf(str, "%s %s", command, path);
		printk(KERN_INFO "Printing details of file  %s\n", path);
		if (!(ext2_proc_print_file_details(path))) {
			printk(KERN_INFO "Could not find the file\n");
		} else {
			printk(KERN_INFO "Printed the file details\n");
		}
	}   
	if (!strcmp(command, "PAI")) {
		printk(KERN_INFO "Printing the linked list\n");
		ext2_proc_print_all_inodes();
		return count;
	}

	printk(KERN_INFO "The possible values are PID mountPoint number\n");	
	printk(KERN_INFO "PFD path \n");	
	printk(KERN_INFO "PAI mountPoint\n");	
	return count;
}

int ext2_init_proc_interface(void)
{
	printk(KERN_INFO "Hello from Proc Interface of ext2 module");
	/*
	 * Make the entry
	 */
	ext2_proc_entry = create_proc_entry(NODE_ENTRY, S_IRUGO | S_IWUSR,\
                                     NULL);
	if (ext2_proc_entry == NULL) {
		printk(KERN_INFO "Failed to make the required proc entry");
		return -1;
	} else {
		pr_info("I created the entry");
	}
	/* Set the procedures for the proc_file */
    ext2_proc_entry->read_proc = ext2_proc_read;
    ext2_proc_entry->write_proc = ext2_proc_write;
    return 0;
}

void ext2_proc_remove(void)
{
    if (ext2_proc_entry) {
        remove_proc_entry(NODE_ENTRY, NULL);
        pr_info("Removed the entry");
    }
    printk(KERN_INFO "Bye from Hello Module");
}
