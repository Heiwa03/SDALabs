#include "LinkedList.h"

LLNode* create_new_llnode(void* data) {
    LLNode* node = (LLNode*)malloc(sizeof(LLNode));
    node->data = data;
    node->next = NULL;
    return node;
}

LinkedList* create_new_linkedlist() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void add_to_linkedlist(LinkedList* list, void* data) {
    LLNode* node = create_new_llnode(data);
    node->next = list->head;
    list->head = node;
    list->size++;
}

void free_linkedlist(LinkedList* list) {
    while (list->head != NULL) {
        LLNode* temp = list->head;
        list->head = list->head->next;
        free_llnode(temp);
    }
    free(list);
}

void free_llnode(LLNode* node) {
    free(node);
}

