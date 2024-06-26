#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "Laptop.h"
#include "Queue.h"
#include "LinkedList.h"

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
    bool is_mirrored;
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
unsigned int get_tree_height(BinaryTree *tree);
Node* get_parent_of_node(BinaryTree *tree, unsigned int key);
unsigned int get_tree_mirror_status(BinaryTree *tree);

LinkedList* perform_bfs(BinaryTree *tree);
LinkedList* perform_dfs(BinaryTree *tree);
void print_dfs_bfs_result(LinkedList* list);
bool mirror_tree(BinaryTree *tree);
bool get_mirror_status(BinaryTree* tree);

#endif // BINARYTREE_H