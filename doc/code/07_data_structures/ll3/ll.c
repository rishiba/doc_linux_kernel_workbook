#include "ll.h"

struct list_head node_list;

/*
 * Function to add nodes in linked list
 */
int todo_add_entry(int number)
{
	struct node_struct *new_node =
	    kmalloc((size_t) (sizeof(struct node_struct)), GFP_KERNEL);
	if (!new_node) {
		printk(KERN_INFO
		       "Memory allocation failed, this should never fail due to GFP_KERNEL flag\n");
		return 1;
	}
	new_node->val = number;
	list_add_tail(&(new_node->list), &node_list);
	return 0;
}

/*
 * Function to display the linked list
 */

void show_list(void)
{
	struct node_struct *entry = NULL;

	list_for_each_entry(entry, &node_list, list) {
		printk(KERN_INFO "Node is %d\n", entry->val);
	}
}

/*
 * Function to search for a node and delete the node from the linked list
 */
int delete_node(int number)
{
	struct node_struct *entry = NULL;

	list_for_each_entry(entry, &node_list, list) {
		if (entry->val == number) {
			printk(KERN_INFO "Found the element %d\n", entry->val);
			list_del(&(entry->list));
			kfree(entry);
			return 0;
		}
	}
	printk(KERN_INFO "Could not find the element %d\n", number);
	return 1;
}
