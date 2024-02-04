
#include "../inc/garbage.h"
#include "../libft/libft.h"
#include <stdio.h>

void add_address(void *address, t_alloc *head) {
	t_alloc *iter = head;
  // puts("adding address");
  while (iter->next != NULL) {
	iter = iter->next;
  }
  t_alloc *new_alloc_node = ft_calloc(1, sizeof(t_alloc));
  head = iter;
  head->next = new_alloc_node;
  // printf("address: %p\n", new_alloc_node);
  new_alloc_node->address = address;
  new_alloc_node->alloc_node = new_alloc_node;
  new_alloc_node->next = NULL;
}

void *chad_alloc(size_t size, int quantity, t_alloc *address) {
  void *alloc_ptr;
  t_alloc *iter;
  
  iter = address;

  alloc_ptr = ft_calloc(size ,quantity);
  if (!alloc_ptr)
    return (NULL);
    while (iter->next != NULL) {
      iter = iter->next;
    }
    t_alloc *new_alloc_node = ft_calloc(1, sizeof(t_alloc));
    new_alloc_node->alloc_node = new_alloc_node;
    iter->next = new_alloc_node;
    new_alloc_node->address = alloc_ptr;
    new_alloc_node->next = NULL;
  return (alloc_ptr);
}

void free_all(t_alloc *head) {
  t_alloc *tmp;
  while (head->next != NULL) {
    tmp = head;
    head = head->next;
    if (tmp->address)
    {
    free(tmp->address);
    free(tmp->alloc_node);
    // tmp->address = NULL;
    // tmp->alloc_node = NULL;
    }
  }
    free(head->address);
    free(head->alloc_node);
}
