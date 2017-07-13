/*
 * <PD> Program for linked list manipulation using proc </PD>
 */
#include "ll.h"

struct list_head todo_list;

int todo_add_entry(int number)
{
   struct todo_struct *new_node = kmalloc((size_t) (sizeof(struct todo_struct)), GFP_KERNEL);
   if (!new_node) {
      printk(KERN_INFO
             "Memory allocation failed, this should never fail due to GFP_KERNEL flag\n");
      return 1;
   }
   new_node->priority = number;
   list_add_tail(&(new_node->list), &todo_list);
   return 0;
}

void show_list(void)
{
   struct todo_struct *entry = NULL;

   list_for_each_entry(entry, &todo_list, list) {
      printk(KERN_INFO "Node is %d\n", entry->priority);
   }
}

int delete_node(int number)
{
   struct todo_struct *entry = NULL;

   list_for_each_entry(entry, &todo_list, list) {
      if (entry->priority == number) {
         printk(KERN_INFO "Found the element %d\n",
                entry->priority);
         list_del(&(entry->list));
         kfree(entry);
         return 0;
      }
   }
   printk(KERN_INFO "Could not find the element %d\n", number);
   return 1;
}
