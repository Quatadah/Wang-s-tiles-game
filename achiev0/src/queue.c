#include <stdio.h>
#include <stdlib.h>

#include "tile.h"
#include "queue.h"


Queue *initQueue()
{
    Queue *queue;
    queue = malloc(sizeof(*queue));
    //printf("malloc queue\n");
    if ( queue == NULL)
    {
        printf("Error in dynamic allocation.\n");
        exit(EXIT_FAILURE);
    }
    queue->firstElement = NULL;

    return queue;
}

void push(Queue *queue,const struct tile *t)
{
    Element *newElement;
    newElement = malloc(sizeof(*newElement));
    //printf("malloc push\n");
    if (newElement == NULL || queue == NULL)
    {
        printf("Error in dynamic allocation.\n");
        exit(EXIT_FAILURE);
    }
    newElement->tile = t;
    newElement->next = NULL;
    if (queue->firstElement != NULL)
    {
        Element *currentElement = queue->firstElement;
        while(currentElement->next != NULL)
        {
            currentElement = currentElement->next;
        }
        currentElement->next = newElement ;
    }
    
    else
    {
        queue->firstElement = newElement;
    }
    
};


Element *top(Queue *queue)
{
    return queue->firstElement;
}


void pop(Queue *queue)
{
    if (queue == NULL )
    {
        printf("Error in dynamic allocation.\n");
        exit(EXIT_FAILURE);
    }

    if (queue->firstElement == NULL)
    {
        printf("Nothing to pop, the queue is empty.\n");
        exit(EXIT_SUCCESS);
    }

    else{
        Element *toBeDeleted = queue->firstElement;
        queue->firstElement = queue->firstElement->next;
        free(toBeDeleted);
    }
}

void popAll(Queue *queue)
{
    if (queue == NULL)
    {
        printf("Error in dynamic allocation.\n");
        exit(EXIT_FAILURE);
    }

    Element *currentElement = queue->firstElement;
    
    while(currentElement != NULL)
    {
        currentElement = currentElement->next;
        pop(queue);
    }
}

Queue * rand_q(Queue *queue)
{
    Queue *ret = initQueue();
    int length = 0;
    int n;
    const struct tile* tiles[MAX_DECK_SIZE];
    while (queue->firstElement != NULL)
    {
        tiles[length] = top(queue)->tile;
        length++;
        pop(queue);
    }
    popAll(queue);
    free(queue);
    for (int i=0; i<length; i++)
    {
        n = rand()%length;
        while (tiles[n] == NULL)
        {
            n = (n+1)%length;
        }
        push(ret, tiles[n]);
        tiles[n] = NULL;
    }
    return ret;
}