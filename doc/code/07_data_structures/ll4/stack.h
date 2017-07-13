#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#ifndef LL_H
#define LL_H
#define NODE "driver/myStack"
/*
 * Linked List Node
 */
struct stack_struct {
		struct list_head list;
		int val;
};

/*
 * Linked list related functions
 */

/*
 * Proc Interface related function
 */
int configure_proc_entry(void);

int my_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data); 

int my_proc_write(struct file *file, const char __user *buffer, unsigned long count, void *data);

int configure_proc_entry(void);
int push_node (int);
int pop_node (void);
int peek(void);
void print(void);
#endif
