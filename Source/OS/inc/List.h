
#ifndef LIST_H_
#define LIST_H_

#include <stdint.h>
#include "Task.h"

struct ListItem_Tag{
  void * pCurrentItem;
  struct ListItem_Tag * pNext;
  struct ListItem_Tag * pPrevious;
};

typedef struct ListItem_Tag ListItem_t;

typedef struct {
  ListItem_t * pElems;
  uint32_t size;
} List_t;


void List_InsertElement(List_t * const list, ListItem_t * const pNewItem);
void List_InsertElementAtEnd(List_t * const list, ListItem_t * const pNewItem);
ListItem_t * List_RemoveElement(List_t * const list);
ListItem_t * List_CreateListItem(void * element);

#endif