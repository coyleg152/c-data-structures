// File: linked_list.c
// Include this file *after* including <stdlib.h>
struct linked_list
{
  struct linked_list * prev;
  struct linked_list * next;
  int val;
};

typedef struct linked_list linked_list;

linked_list * ll_new(int init_val)
{
  linked_list * itr = malloc(sizeof(linked_list));
  itr->prev = NULL;
  itr->next = NULL;
  itr->val = init_val;
  return itr;
}

void ll_delete(linked_list * itr)
{
  if (itr == NULL) return;
  while (itr->prev != NULL) itr = itr->prev;
  while (itr->next != NULL)
  {
    itr = itr->next;
    free(itr->prev);
  }
  free(itr);
}

void ll_free(linked_list * itr)
{
  if (itr == NULL) return;
  while (itr->next != NULL) itr = itr->next;
  while (itr->prev != NULL)
  {
    itr = itr->prev;
    free(itr->next);
  }
  free(itr);
}

linked_list * ll_prev(linked_list * itr)
{
  if (itr != NULL && itr->prev != NULL) return itr->prev;
  else return itr;
}

linked_list * ll_next(linked_list * itr)
{
  if (itr != NULL && itr->next != NULL) return itr->next;
  else return itr;
}

void ll_push_prev(linked_list * itr, int init_val)
{
  if (itr == NULL) return;
  linked_list * temp = itr->prev;
  itr->prev = ll_new(init_val);
  itr->prev->next = itr;
  if (temp != NULL)
  {
    temp->next = itr->prev;
    itr->prev->prev = temp;
  }
}

void ll_push_next(linked_list * itr, int init_val)
{
  if (itr == NULL) return;
  linked_list * temp = itr->next;
  itr->next = ll_new(init_val);
  itr->next->prev = itr;
  if (temp != NULL)
  {
    temp->prev = itr->next;
    itr->next->next = temp;
  }
}

void ll_pop_prev(linked_list * itr)
{
  if (itr == NULL || itr->prev == NULL) return;
  struct linked_list * temp = itr->prev->prev;
  free(itr->prev);
  itr->prev = temp;
  if (temp != NULL) temp->next = itr;
}

void ll_pop_next(linked_list * itr)
{
  if (itr == NULL || itr->next == NULL) return;
  linked_list * temp = itr->next->next;
  free(itr->next);
  itr->next = temp;
  if (temp != NULL) temp->prev = itr;
}

int ll_length(linked_list * itr)
{
  if (itr == NULL) return 0;
  int length = 1;
  for (linked_list * l = itr->prev; l != NULL; l = l->prev) length++;
  for (linked_list * r = itr->next; r != NULL; r = r->next) length++;
  return length;
}
