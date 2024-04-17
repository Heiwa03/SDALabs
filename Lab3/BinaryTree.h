#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Container {
    char * key;
    int data;
    struct Container *next;
} Container;

typedef struct Node {
    Container * head;
    struct Node *left;
    struct Node *right;
    unsigned int nr_of_containers;
    unsigned int nr_of_children;
} Node;

typedef struct BinaryTree {
    Node *root;
    int nr_of_nodes;
    int total_nr_of_containers;
} BinaryTree;

BinaryTree *create_binary_tree();
Container* create_container(char *key, int data);
Node *create_node(Container *container);
bool insert(BinaryTree *tree, char *key, int data);

#endif // BINARYTREE_H