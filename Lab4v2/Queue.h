#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Qnode {
    void* data;
    struct Qnode* next;
} Qnode;

typedef struct Queue {
    Qnode *front, *rear;
} Queue;

Qnode* create_new_node(void* data);
Queue* create_new_queue();
void enqueue(Queue* queue, void* data);
void* dequeue(Queue* queue);
void free_queue(Queue* queue);
void free_q_node(Qnode* node);
bool get_is_empty(Queue* queue);


#endif // QUEUE_H