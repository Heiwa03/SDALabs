#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "Laptop.h"

#define UNINITIALIZED -1
#define IN_ORDER 1
#define PRE_ORDER 2
#define POST_ORDER 3
#define GET_DEPTH 1
#define GET_HEIGHT 1
#define GET_NR_OF_CHILDREN 1
#define NO_DEPTH 0
#define NO_HEIGHT 0
#define NO_NR_OF_CHILDREN 0
#define MIRRORED 1
#define NOT_MIRRORED 0

typedef struct Node {
    unsigned int key;
    struct Node *left;
    struct Node *right;
    unsigned int nr_of_children;
    unsigned int height;
    unsigned int depth;
    struct Laptop *laptop;
} Node;

typedef struct BinaryTree {
    Node *root;
    unsigned int nr_of_nodes;
    unsigned int is_mirrored;
} BinaryTree;


Node *create_node(unsigned int key, struct Laptop *new_laptop);
BinaryTree *create_binary_tree();
void insert_value(BinaryTree *tree, unsigned int key, struct Laptop *new_laptop);
void delete_value(BinaryTree *tree, unsigned int key);
Node *search_value(BinaryTree *tree, unsigned int key);

void clear_tree(BinaryTree *tree);
void free_tree(BinaryTree *tree);

// Recursive freeing of each node coming from the root including the root
void free_node(Node *node);

// Use IN_ORDER, PRE_ORDER, POST_ORDER to print the tree in the respective order
void print_tree(BinaryTree *tree, unsigned int print_type);

unsigned int get_node_height(Node *node);
unsigned int get_node_depth(Node *node);
unsigned int get_node_nr_of_children(Node *node);
unsigned int get_tree_height(BinaryTree *tree);
Node* get_parent_of_node(BinaryTree *tree, unsigned int key);
unsigned int get_tree_mirror_status(BinaryTree *tree);

unsigned int get_height_of_node_by_key(BinaryTree *tree, unsigned int key);
unsigned int get_depth_of_node_by_key(BinaryTree *tree, unsigned int key);

void show_all_leaves_of_tree(BinaryTree *tree);
void print_depth_of_each_node(BinaryTree *tree);
void print_height_of_each_node(BinaryTree *tree);

// Use GET_DEPTH, GET_HEIGHT, GET_NR_OF_CHILDREN to retrieve the respective property of each node
// Use NO_DEPTH, NO_HEIGHT, NO_NR_OF_CHILDREN to eliminate a property from being printed
// Properties are stacked in the order of the prototype function's arguments
void print_properties_of_each_node(BinaryTree *tree, unsigned int get_height, unsigned int get_depth, unsigned int get_nr_of_children);


#endif // BINARYTREE_H