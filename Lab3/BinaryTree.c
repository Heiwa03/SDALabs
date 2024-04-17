#include "BinaryTree.h"

BinaryTree* create_binary_tree() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (tree == NULL) {
        printf("ERROR:[create_binary_tree]:Failed to allocate memory for binary tree\n");
        return NULL;
    }
    tree->root = NULL;
    tree->nr_of_nodes = 0;
    tree->total_nr_of_containers = 0;
    return tree;
}

Node* create_node(Container *container) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("ERROR:[create_node]:Failed to allocate memory for node\n");
        return NULL;
    }
    new_node->head = container;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->nr_of_containers = 1;
    new_node->nr_of_children = 0;
    return new_node;
}

Container* create_container(char *key, int data) {
    Container* new_container = (Container*)malloc(sizeof(Container));
    if (new_container == NULL) {
        printf("ERROR:[create_container]:Failed to allocate memory for container\n");
        return NULL;
    }
    new_container->key = key;
    new_container->data = data;
    new_container->next = NULL;
    return new_container;
}

bool insert(BinaryTree *tree, char *key, int data) {
    // Create a new container
    Container* container = create_container(key, data);
    if (container == NULL) {
        printf("ERROR:[insert]:Failed to create container\n");
        return false;
    }

    // If the tree is empty, create new root node 
    if (tree->root == NULL) {
        tree->root = create_node(container);
        if (tree->root == NULL) {
            printf("ERROR:[insert]:Failed to create root node\n");
            free(container);
            return false;
        }
        tree->nr_of_nodes = 1;
        tree->total_nr_of_containers = 1;
        return true;
    }

    // Otherwise, find the correct place to insert the new node or container
    Node* current = tree->root;
    while (true) {
        if (data < current->head->data) {
            // Go to the left child
            if (current->left == NULL) {
                current->left = create_node(container);
                if (current->left == NULL) {
                    free(container);
                    return false;
                }
                current->nr_of_children++;
                tree->nr_of_nodes++;
                tree->total_nr_of_containers++;
                return true;
            }
            current = current->left;
        } else if (data > current->head->data) {
            // Go to the right child
            if (current->right == NULL) {
                current->right = create_node(container);
                if (current->right == NULL) {
                    free(container);
                    return false;
                }
                current->nr_of_children++;
                tree->nr_of_nodes++;
                tree->total_nr_of_containers++;
                return true;
            }
            current = current->right;
        } else {
            // The key already exists, add a new container to the current node
            container->next = current->head;
            current->head = container;
            current->nr_of_containers++;
            tree->total_nr_of_containers++;
            return true;
        }
    }
}

