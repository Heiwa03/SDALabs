#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Laptop {
    char * brand;
    char * model;
    char * processor;
    char * ram;
    char * price;
} Laptop;

typedef struct Node {
    Laptop * laptop;
    struct Node * next;
} Node;

typedef struct LinkedList {
    Node * head;
    int size;
} LinkedList;

LinkedList * createLinkedList();
Laptop * createLaptop(char * brand, char * model, char * processor, char * ram, char * price);
Node * createNode(Laptop * laptop);
void push_front(LinkedList * list, Laptop * laptop);
void push_back(LinkedList * list, Laptop * laptop);
void insert(LinkedList * list, Laptop * laptop, int index);
void pop_front(LinkedList * list);
void pop_back(LinkedList * list);
void pop_index(LinkedList * list, int index);
void printList(LinkedList * list);
void freeList(LinkedList * list);
void freeNode(Node * node);
void freeLaptop(Laptop * laptop);
void invertList(LinkedList * list);
int searchList(LinkedList* list, char* field, char* value);
void sortList(LinkedList* list, char* field);





#endif // LINKEDLIST_H