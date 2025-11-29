// File: queue.c
// Include this file *after* including <stdlib.h>
struct node
{
  struct node * next;
  int val;
};

typedef struct node node;

typedef struct
{
  node * head;
  node * tail;
  int len;
}
queue;

queue * q_new()
{
  queue * data = malloc(sizeof(queue));
  data->head = NULL;
  data->tail = NULL;
  data->len = 0;
  return data;
}

void q_free(queue * data)
{
  if (data == NULL) return;
  while (data->head != NULL)
  {
    data->tail = data->head;
    data->head = data->head->next;
    free(data->tail);
  }
  free(data);
}

void q_push(queue * data, int init_val)
{
  if (data->tail == NULL)
  {
    data->tail = malloc(sizeof(node));
    data->head = data->tail;
  }
  else
  {
    data->tail->next = malloc(sizeof(node));
    data->tail = data->tail->next;
  }
  data->tail->val = init_val;
  data->tail->next = NULL;
  data->len += 1;
}

void q_pop(queue * data)
{
  if (data->head == NULL) return;
  node * temp = data->head;
  data->head = data->head->next;
  free(temp);
  data->len -= 1;
  if (data->head == NULL) data->tail = NULL;
}

int q_front(queue * data)
{
  if (data->head == NULL) return 0;
  else return data->head->val;
}
