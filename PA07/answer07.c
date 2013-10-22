#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

void List_modify(Node * head, int value,int index);

/**
 * Prints a linked-list "head" into the output fie "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
 while(head != NULL)
	{
	    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
	    head = head -> next;
	}
    printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
  if(head==NULL)
    {
      return;
    }
  struct linked * previous = head;
  struct linked * target = head;
  if(head->next !=NULL)
    {
      target=target->next;
      while(target!=NULL)
	{
	  free(previous);
	  previous=target;
	  target=target->next;
	}
      free(previous);
    }
  else
    {
      free(head);
    }
  return;
}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
  struct linked * newnode =  malloc(sizeof(struct linked));
  newnode->value=value;
  newnode->index=index;
  newnode->next=NULL;
  return(newnode);  
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length)
{
  if(length==0)
    {
      return(NULL);
    }
  int small=index[0];
  int smalloc=0;
  int big=index[0];
  int bigloc=0;
  int i;
  struct linked * list;
  struct linked * ret;

  for(i=0;i<length;i++)
    {
      if(index[i]<small)
	{
	  small=index[i];
	  smalloc=i;
	}
      if(index[i]>big)
	{
	  big=index[i];
	  bigloc=i;
	}
    }
  
  list=List_create(value[smalloc],index[smalloc]);
  ret=list;

  while(small!=big)
    {
      small=big;
      smalloc=bigloc;
      for(i=0;i<length;i++)
	{
	  if(index[i]>list->index && index[i]<small)
	    {
	      small=index[i];
	      smalloc=i;
	    }
	}
      list->next=List_create(value[smalloc],index[smalloc]);
      list=list->next;
    }
  return(ret);
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
  if(index<head->index)
    {
      struct linked * new=List_create(value,index);
      new->next=head;
      return(new);
    }
  struct linked * prev=head;
  struct linked * point=prev->next;
  struct linked * newnode = List_create(value,index);

  //Shift down to appropriate location
  while(point->index<index && point->next!=NULL)
    {
      prev=prev->next;
      point=point->next;
    }
  //Make attachments
  if(point->index < index)
    {
      point->next=newnode;
    }
  else
    {
      prev->next=newnode;
      newnode->next=point;
    }
  return(head);
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index)
{
  struct linked * target = head->next;
  struct linked * prev=head;
  if(prev->index==index)
    {
      free(prev);
      return(target);
    }
  //Move pointers to target and previous values
  while(target->index!=index)
    {
      prev=prev->next;
      target=target->next;
    }
  //Reattach next value and free the target
  if(target->next!=NULL)
    {
      prev->next=target->next;
    }
  free(target);
  return(head);
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * List_copy(Node * head)
{
  if(head==NULL)
    {
      return(NULL);
    }

  struct linked * target = head;
  struct linked * copy=List_create(target->value,target->index);
  struct linked * copy_head=copy;

  while(target->next!=NULL)
    {
      target=target->next;
      copy->next=List_create(target->value,target->index);
      copy=copy->next;
    }
  return(copy_head);
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * List_merge(Node * head1, Node * head2)
{
  if(head1==NULL && head2==NULL)
    {
      return(NULL);
    }
  else if(head1==NULL)
    {
      return(List_copy(head2));
    }
  else if(head2==NULL)
    {
      return(List_copy(head1));
    }

  struct linked * merge=List_copy(head1);
  struct linked * list1=head1;
  struct linked * list2=head2;
  int ind;
  int val;

  if(head1->next==NULL && head2->next==NULL)
    {
      if(head1->index != head2->index)
	{
	  merge=List_insert_ascend(merge,head2->value,head2->index);
	}
      else
	{
	  List_destroy(merge);
	  merge=List_create(head1->value+head2->value,head1->index);
	}
      return(merge);
    }
  
  if(head1->next==NULL)
    {
      List_destroy(merge);
      merge=List_copy(head2);
      if(head1->index==head2->index && head1->value+head2->value==0)
	{
	  merge=List_delete(merge,head1->index);
	  return(merge);
	}
      else if(head1->index==head2->index)
	{
	  List_modify(merge,head1->value+head2->value,head1->index);
	  return(merge);
	}
      else
	{
	  merge=List_insert_ascend(merge,head1->value,head1->index);;
	  return(merge);
	}
    }

  while(list2 != NULL)
    {
      if(list1->next==NULL && list1->index<list2->index)
	{
	  ind=list2->index;
	  val=list2->value;
	  list2=list2->next;
	  merge=List_insert_ascend(merge,val,ind);
	}
      else if(list1->index < list2->index)
	{
	  list1=list1->next;
	}
      else if(list1->index > list2->index)
	{
	  ind=list2->index;
	  val=list2->value;
	  list2=list2->next;
	  merge=List_insert_ascend(merge,val,ind);
	}
      else if(list1->index == list2->index)
	{
	  ind=list1->index;
	  val=list1->value+list2->value;
	  if(list1->next!=NULL)
	    {
	      list1=list1->next;
	    }
	  list2=list2->next;
	  if(val!=0)
	    {
	      List_modify(merge,val,ind);
	    }
	  else
	    {
	      merge=List_delete(merge,ind);
	    }
	}
    }  
  return(merge);
}

void List_modify(Node * head,int value,int index)
{
  while(head->index!=index)
    {
      head=head->next;
    }
  head->value=value;
  return;
}
