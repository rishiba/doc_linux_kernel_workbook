#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#ifndef LL_H
#define LL_H
#define NODE "driver/mmmod"
/*
 * Linked List Node
 */
struct todo_struct {
		struct list_head list;
		int priority;
};

/*
 * Linked list related functions
 */
void show_list(void);
int todo_add_entry(int);

/*
 * Proc Interface related function
 */

void proc_cleanup(void);
int ll_proc_init (void);
int configure_proc_entry(void);


ssize_t my_proc_read (struct file *filp,char *buf,size_t count,loff_t *offp ); 
ssize_t my_proc_write(struct file *filp, const char __user * buffer, size_t count, loff_t *pos);

int configure_proc_entry(void);
int delete_node (int);
void destroy(void); 
#endif
