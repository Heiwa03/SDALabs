#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LLNode {
    void* data;
    struct LLNode *next;
} LLNode;

typedef struct LinkedList {
    LLNode *head;
    unsigned int size;
} LinkedList;

LLNode* create_new_llnode(void* data);
LinkedList* create_new_linkedlist();
void add_to_linkedlist(LinkedList* list, void* data);
void free_linkedlist(LinkedList* list);
void free_llnode(LLNode* node);

#endif // LINKEDLIST_H