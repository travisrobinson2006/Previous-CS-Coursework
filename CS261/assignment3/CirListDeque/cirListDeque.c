/* CS261- Assignment 3 */
/* Name: Travis Robinson
 * Date: 07/15/2015
 * Solution description: Implement the circular double linked list
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q)
{
  	/* FIXME: you must write this */
  	assert(q != 0);
  	q->size = 0;
  	q->Sentinel = malloc(sizeof(struct DLink));
    q->Sentinel->next = q->Sentinel;
    q->Sentinel->prev = q->Sentinel;
}

/*
 create a new circular list deque

 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/* FIXME: you must write this */
    struct DLink* newLink = malloc(sizeof(struct DLink));
    newLink->value = val;
	/*temporary return value..you may need to change it*/
	//return(0);
    return (newLink);
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	/* FIXME: you must write this */
    assert(q != 0);
    assert(lnk != 0);
    struct DLink* newLink = _createLink(v);
    newLink->next = lnk->next;
    newLink->prev = lnk;
    lnk->next->prev = newLink;
    lnk->next = newLink;
    q->size = q->size+1;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val)
{
	/* FIXME: you must write this */
	assert(q != 0);
    struct DLink* newLink = _createLink(val);
    q->Sentinel->prev->next = newLink;
    newLink->prev = q->Sentinel->prev;
    q->Sentinel->prev = newLink;
    newLink->next = q->Sentinel;
    q->size = q->size+1;
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	/* FIXME: you must write this */
	assert(q != 0);
    struct DLink* newLink = _createLink(val);
    q->Sentinel->next->prev = newLink;
    newLink->next = q->Sentinel->next;
    q->Sentinel->next = newLink;
    newLink->prev = q->Sentinel;
    q->size = q->size+1;
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	assert(q != 0);
	assert(q->size >= 1);
	/*temporary return value..you may need to change it*/
	//return(1);
    return (q->Sentinel->next->value);
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	assert(q != 0);
	assert(q->size >= 1);
	/*temporary return value..you may need to change it*/
	//return(1);
	return (q->Sentinel->prev->value);
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	/* FIXME: you must write this */
    assert(q != 0);
    assert(q->size >= 1);
    lnk->prev->next = lnk->next;
    lnk->next->prev = lnk->prev;
    free(lnk);
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	/* FIXME: you must write this */
    assert(q != 0);
    assert(q->size >= 1);
    _removeLink(q,q->Sentinel->next);
    q->size = q->size-1;
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
  	/* FIXME: you must write this */
    assert(q != 0);
    assert(q->size >= 1);
    _removeLink(q,q->Sentinel->prev);
    q->size = q->size-1;
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
    struct DLink* link = q->Sentinel;
    for (int index = 0; index<=q->size; index++)
    {
        free(link);
        link = link->next;
    }
    q->size = 0;
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
  	/* FIXME: you must write this */
  	assert(q != 0);
	/*temporary return value..you may need to change it*/
	if (q->size == 0)
    {
        return 1;
    }
    return 0;
	//return(1);
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
    assert(q != 0);
    assert(q->size != 0);
    int index = 0;
    struct DLink* link = q->Sentinel->next;
    while (link != q->Sentinel)
    {
        printf("The value at %d is %f \n",index,link->value);
        link = link->next;
        index++;
    }
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
    struct DLink* linkFront = q->Sentinel->next;
    struct DLink* linkBack = q->Sentinel->prev;
    for (int index = 0; index < (q->size/2); index++)
    {
        TYPE temp;
        temp = linkFront->value;
        linkFront->value = linkBack->value;
        linkBack->value = temp;
        linkFront = linkFront->next;
        linkBack = linkBack->prev;
    }
}
