#include "Queue.h"

Qnode* create_new_node(void* data) {
    Qnode* node = (Qnode*)malloc(sizeof(Qnode));
    node->data = data;
    node->next = NULL;
    return node;
}

Queue* create_new_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, void* data) {
    Qnode* node = create_new_node(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = node;
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
}

void* dequeue(Queue* queue) {
    if (queue->front == NULL)
        return NULL;

    Qnode* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    void* data = temp->data;
    free(temp);

    return data;
}

void free_queue(Queue* queue) {
    while (queue->front != NULL) {
        Qnode* temp = queue->front;
        queue->front = queue->front->next;
        free_q_node(temp);
    }
    free(queue);
}

void free_q_node(Qnode* node) {
    free(node);
}

bool get_is_empty(Queue* queue) {
    return queue->front == NULL;
}