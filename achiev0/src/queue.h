#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "tile.h"

typedef struct Element Element;

struct Element{
    const struct tile *tile;
    struct Element *next;
};

typedef struct Queue Queue;
struct Queue{
    struct Element *firstElement;
};

//function that initializes the queue
Queue *initQueue();

//function that adds elements to the queue
void push(Queue *queue,const struct tile *t);

//function that returns a pointer towards an element in the head of the queue
Element *top(Queue *queue);

//function that deletes elements to the queue
void pop(Queue *queue);

//function that deletes the queue
void popAll(Queue *queue);

Queue * rand_q(Queue *queue);


#endif