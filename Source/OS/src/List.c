
#include <stdlib.h>
#include "List.h"



void List_InsertElement(List_t * const list, ListItem_t * const pNewItem)
{  
  
  if (list->size == 0u) {
    /* list is empty */
    list->pElems = pNewItem;
  } else {
    /* make link between the new element and the next one */
    pNewItem->pNext = list->pElems;
    /* make the link between the new element and the previous one */
    pNewItem->pPrevious = list->pElems->pPrevious;
    
    /* if there is any element in front: make the link with the new element */
    if (list->pElems->pPrevious != NULL) {
      list->pElems->pPrevious->pNext = pNewItem;
    }
    
    list->pElems->pPrevious = pNewItem;
    
    /* the list will not point to the lastest element */
    list->pElems = pNewItem;
    
    list->pElems->pNext = pNewItem->pNext;
  }
  list->size++;   
}

void List_InsertElementAtEnd(List_t * const list, ListItem_t * const pNewItem)
{
  if (list->size == 0) {    
    /* list is empty */
    list->pElems = pNewItem;
  } else {
    list->pElems->pNext = pNewItem;
    pNewItem->pPrevious = list->pElems;
  }
  list->size++;
}

ListItem_t * List_RemoveElement(List_t * const list)
{
  ListItem_t * pElem;
  
  if (list->size == 0) {
    pElem = NULL;
  } else {
    /* select the element to be removed */
    pElem = list->pElems;
    if (pElem->pPrevious != NULL) {
      /* brake the link between current element and the previous one */
      pElem->pPrevious->pNext = pElem->pNext;
    }
    if (pElem->pNext != NULL) {
      /* brake the link between current element and the next one */
      pElem->pNext->pPrevious = pElem->pPrevious;
    }
    /* set the list to point to the next element */
    list->pElems = pElem->pNext;
    /* isolate the element to be removed */
    pElem->pPrevious = NULL;
    pElem->pNext = NULL;
    list->size--;
  }
  return pElem;
}


ListItem_t * List_CreateListItem(void * element)
{
  ListItem_t * pNewElem;
  
  pNewElem = malloc(sizeof(ListItem_t));
  pNewElem->pCurrentItem = element;
  pNewElem->pNext = NULL;
  pNewElem->pPrevious = NULL;
  
  return pNewElem;
}