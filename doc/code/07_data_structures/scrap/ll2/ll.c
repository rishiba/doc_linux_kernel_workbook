#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>

struct todo_struct {
	struct list_head list;
	int priority;
};

struct list_head todo_list;

void todo_add_entry(struct todo_struct *new)
{
	struct list_head *ptr;
	struct todo_struct *entry;
	list_for_each(ptr, &todo_list) {
		entry = list_entry(ptr, struct todo_struct, list);
		if (entry->priority < new->priority) {
			list_add_tail(&new->list, ptr);
			return;
		}
	}
	list_add_tail(&new->list, &todo_list);
}

void todo_add_entry_2(struct todo_struct *new)
{
	struct todo_struct *entry;

	list_for_each_entry(entry, &todo_list, list) {
		pr_info("Node value %d", entry->priority);
	}
	list_add_tail(&new->list, &todo_list);
}

void show_list_2(void)
{
	struct todo_struct *entry = NULL;

	list_for_each_entry(entry, &todo_list, list) {
		printk(KERN_INFO "Node is %d", entry->priority);
	}
}

void show_list(void)
{
	struct list_head *ptr;
	struct todo_struct *entry;
	list_for_each(ptr, &todo_list) {
		entry = list_entry(ptr, struct todo_struct, list);
		printk(KERN_INFO "Priority %d", entry->priority);
	}

}

void add_nodes_to_ll(void)
{

	struct todo_struct temp[5];
	int i;

	INIT_LIST_HEAD(&todo_list);

	for (i = 0; i < 5; i++) {
		temp[i].priority = i * 100;
		pr_info("Adding value 1 ");

		todo_add_entry(&temp[i]);
	}

/*
	pr_info ("Printing the list 1\n");
	show_list();
*/

//      pr_info("Adding Again\n");

	for (i = 0; i < 5; i++) {
		temp[i].priority = i * 200;
		pr_info("Adding value2 ");
		todo_add_entry_2(&temp[i]);
	}

	pr_info("Printing the list Again\n");
	show_list_2();

}

static int __init my_init(void)
{

	printk(KERN_INFO "Hello from Hello Module");
	add_nodes_to_ll();

	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Bye from Hello Module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("abr");
MODULE_LICENSE("GPL v2");
