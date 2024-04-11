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

LinkedList * create_linked_list();
void get_laptop_data(char * brand, char * model, char * processor, char * ram, char * price);
Laptop * create_laptop(char * brand, char * model, char * processor, char * ram, char * price);
Node * create_node(Laptop * laptop);
void push_front(LinkedList * list, Laptop * laptop);
void push_back(LinkedList * list, Laptop * laptop);
void insert(LinkedList * list, Laptop * laptop, int index);
void pop_front(LinkedList * list);
void pop_back(LinkedList * list);
void pop_index(LinkedList * list, int index);
void print_list(LinkedList * list);
void free_list(LinkedList * list);
void free_node(Node * node);
void free_laptop(Laptop * laptop);
void invert_list(LinkedList * list);
int search_list(LinkedList* list, char* field, char* value);
void sort_list(LinkedList* list, char* field);

#endif // LINKEDLIST_H