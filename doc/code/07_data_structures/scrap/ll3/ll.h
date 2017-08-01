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
struct node_struct {
		struct list_head list;
		int val;
};

/*
 * Linked list related functions
 */
void show_list(void);
int todo_add_entry(int);

/*
 * Proc Interface related function
 */
int configure_proc_entry(void);

int my_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data); 

int my_proc_write(struct file *file, const char __user *buffer, unsigned long count, void *data);

int configure_proc_entry(void);
int delete_node (int);
void destroy(void); 
#endif
