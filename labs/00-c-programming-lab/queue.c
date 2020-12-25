/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q==NULL)
    {
      printf("Memory allocation failed");
      return NULL;
    }
    else
    {    
      q->head = NULL;
      q->tail = NULL;
      q->size = 0;
      return q;
    }
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q==NULL) return;
    if(q->size==0)
    {
      free(q);
      return;
    }
    for(list_ele_t *ptr = q->head, *temp; ptr!=NULL;)
    {
      free(ptr->value);
      temp = ptr->next;
      free(ptr);
      ptr = temp;
    }
    free(q);
    return;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q==NULL)
    {
      printf("Queue pointer is NULL");
      return false;
    }
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh==NULL) return false;

    char *value;
    value = (char *) malloc(strlen(s)+1);
    if (value==NULL) 
    {
      free(newh);
      return false;
    }

    strcpy(value, s);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = value;
    newh->next = q->head;
    q->head = newh;
    if (q->size==0) q->tail = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q==NULL)
    {
      printf("Queue pointer is NULL");
      return false;
    }
    list_ele_t *newt;
    /* What should you do if the q is NULL? */
    newt = malloc(sizeof(list_ele_t));
    if (newt==NULL) return false;

    char *value;
    value = (char *) malloc(strlen(s)+1);
    if (value==NULL)
    {
      free(newt);
      return false;
    }

    strcpy(value, s);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newt->value = value;
    newt->next = NULL;
    if (q->size==0) 
    {
      q->head = newt;
    }
    else
    {
      q->tail->next = newt;
    }
    q->tail = newt;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q==NULL || q->size==0 || sp==NULL) return false;

    strncpy(sp, q->head->value, bufsize-1);
    sp[bufsize-1]='\0';
    // free head
    free(q->head->value);
    list_ele_t *temp;
    temp = q->head->next;
    free(q->head);
    q->head = temp;
    q->size--;
    if(q->size==0) q->tail=NULL;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q==NULL) return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q_size(q)<=1) return; // no need to do anything when q size is 0 or 1
    unsigned int size = q_size(q);
    list_ele_t *ptrs[size];
    list_ele_t *ptr=q->head;
    for (unsigned int i=0; ptr!=NULL; ptr=ptr->next, ++i)
    {
      ptrs[i] = ptr;
    }

    ptr = q->head = q->tail;
    q->tail = ptrs[0];
    for (int i=size-1; i>0;)
    {
      ptr->next = ptrs[--i];
      ptr = ptr->next;
    }
    ptr->next=NULL;
}

