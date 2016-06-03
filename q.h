#include<stdio.h>
#include <stdlib.h>
#include "TCB.h"


// creates a empty queue, pointed to by the variable head.
tcb_t * InitQueue(tcb_t **Q)
{
*Q=NULL;
return *Q;


}

//adds a queue item, pointed to by “item”, to the queue pointed to by head.
void AddQueue(tcb_t ** Q, tcb_t * Item)
{
tcb_t * head, *tail;                        //Declare head and tail of the queue

//If queue is null i.e no items in the queue add item
if (*Q==NULL)
{
Item->prev=Item;
Item->next=Item;
*Q=Item;
}
// If queue has existing item, add items to the head
else
{
head=*Q;
tail=head->prev;

//circulat queue implementation
Item->next=head;
Item->prev=tail;
head->prev=Item;
tail->next=Item;
}
}


 // deletes an item from head and returns a pointer to the deleted item
tcb_t * DelQueue(tcb_t **Q)
{
// If queue is empty, return a message
if(*Q==NULL)
{
printf("\nEmpty Queue");
return NULL;
}

//Delete an item from the head and update the new head and tail
tcb_t *head,*tail,*current;
current=*Q;
head=current;
tail=current->prev;
current=current->next;
tail->next=current;
current->prev=tail;
head->next=head->prev=NULL;

// If only single item is present, which is pointed by both head and tail, delete it
if(head==tail)
*Q=NULL;
else
*Q=current;

return head;

}

//Moves the header pointer to the next element in the queue. This is equivalent to AddQ(&head, DeleteQ(&head)), but is simpler to use and more efficient to implement.
tcb_t * RotateQ(tcb_t **Q)
{
tcb_t *current;
// If queue is not empty, rotate and return the current head
if (*Q!=NULL)
{
current=*Q;
current=current->next;
*Q=current;
}
else
{
current=NULL;
}
return current;
}

// Display the payload of the queue
void DisplayQ(tcb_t **Q)
{
tcb_t *current;
current=*Q;
if(current==NULL)
{
printf("\t Queue is empty");
return;
}

do {
//printf("\n \t Queue loads thread number %d",current->payload);
current=current->next;
} while(current!=*Q);
printf("\n");
}


