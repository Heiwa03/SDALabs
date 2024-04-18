#include "BinaryTree.h"

Laptop *create_node(unsigned int key, char *brand, char *model, char *processor, char *ram, char *price) {
    Laptop *newLaptop = (Laptop *)malloc(sizeof(Laptop));
    if (newLaptop == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newLaptop->key = key;
    newLaptop->left = NULL;
    newLaptop->right = NULL;
    newLaptop->height = 0;
    newLaptop->depth = 0;
    newLaptop->brand = brand;
    newLaptop->model = model;
    newLaptop->processor = processor;
    newLaptop->ram = ram;
    newLaptop->price = price;

    return newLaptop;
}

void free_node(Laptop *node) {
    if (node == NULL) {
        return;
    }

    free_node(node->left);
    free_node(node->right);

    free(node);
}

void free_tree(BinaryTree *tree) {
    if (tree == NULL) {
        return;
    }

    free_node(tree->root);
    free(tree);
}

void clear_tree(BinaryTree *tree) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    free_node(tree->root);
    tree->root = NULL;
    tree->nr_of_nodes = 0;
}

BinaryTree *create_binary_tree() {
    BinaryTree *newTree = (BinaryTree *)malloc(sizeof(BinaryTree));
    if (newTree == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newTree->root = NULL;
    newTree->nr_of_nodes = 0;

    return newTree;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Laptop *_insert_node(Laptop *node, unsigned int key, int depth) {
    if (node == NULL) {
        Laptop *newLaptop = create_node(key);
        newLaptop->depth = depth;
        return newLaptop;
    }

    if (key < node->key) {
        node->left = _insert_node(node->left, key, depth + 1);
    } else if (key > node->key) {
        node->right = _insert_node(node->right, key, depth + 1);
    }

    node->height = 1 + max((node->left ? node->left->height : -1), 
                           (node->right ? node->right->height : -1));

    return node;
}

void insert_value(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    tree->root = _insert_node(tree->root, key, 0);
    tree->nr_of_nodes++;
}

Laptop *_min_value_node(Laptop *node) {
    Laptop *current_node = node;

    while (current_node && current_node->left != NULL)
        current_node = current_node->left;

    return current_node;
}

Laptop *_delete_node(Laptop *root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = _delete_node(root->left, key);
    else if (key > root->key)
        root->right = _delete_node(root->right, key);
    else {
        if (root->left == NULL) {
            Laptop *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Laptop *temp = root->left;
            free(root);
            return temp;
        }

        Laptop *temp = _min_value_node(root->right);

        root->key = temp->key;

        root->right = _delete_node(root->right, temp->key);
    }
    return root;
}

void delete_value(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    tree->root = _delete_node(tree->root, key);
    tree->nr_of_nodes--;
}

void _print_inorder(Laptop *node) {
    if (node == NULL) {
        return;
    }

    _print_inorder(node->left);
    printf("%u ", node->key);
    _print_inorder(node->right);
}

void _print_preorder(Laptop *node) {
    if (node == NULL) {
        return;
    }

    printf("%u ", node->key);
    _print_preorder(node->left);
    _print_preorder(node->right);
}

void _print_postorder(Laptop *node) {
    if (node == NULL) {
        return;
    }

    _print_postorder(node->left);
    _print_postorder(node->right);
    printf("%u ", node->key);
}

void print_tree(BinaryTree *tree, unsigned int print_type) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }
    switch (print_type) {
        case IN_ORDER:
            _print_inorder(tree->root);
            break;
        case PRE_ORDER:
            _print_preorder(tree->root);
            break;
        case POST_ORDER:
            _print_postorder(tree->root);
            break;
        default:
            break;
    }
    printf("\n");
}

unsigned int get_node_height(Laptop *node) {
    if (node == NULL) {
        printf("Laptop is not initialized\n");
        return UINT_MAX;
    }

    return node->height;
}

unsigned int get_node_depth(Laptop *node) {
    if (node == NULL) {
        printf("Laptop is not initialized\n");
        return UINT_MAX;
    }

    return node->depth;
}

unsigned int get_node_nr_of_children(Laptop *node) {
    if (node == NULL) {
        printf("Laptop is not initialized\n");
        return UINT_MAX;
    }

    unsigned int nr_of_children = 0;
    if (node->left != NULL) {
        nr_of_children++;
    }
    if (node->right != NULL) {
        nr_of_children++;
    }

    return nr_of_children;
}

unsigned int get_tree_height(BinaryTree *tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Tree is not initialized or empty\n");
        return UINT_MAX;
    }

    return tree->root->height;
}

Laptop* _find_parent_of_node(Laptop* node, Laptop* parent, unsigned int key) {
    if (node == NULL) {
        return NULL;
    }

    if (node->key == key) {
        return parent;
    }

    Laptop* left_search = _find_parent_of_node(node->left, node, key);
    Laptop* right_search = _find_parent_of_node(node->right, node, key);

    return left_search != NULL ? left_search : right_search;
}

Laptop* get_parent_of_node(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return NULL;
    }

    if (tree->root->key == key) {
        return NULL; // root node has no parent
    }

    return _find_parent_of_node(tree->root, NULL, key);
}


Laptop *_search_node(Laptop *node, unsigned int key) {
    if (node == NULL || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return _search_node(node->left, key);
    } else {
        return _search_node(node->right, key);
    }
}

Laptop *search_value(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return NULL;
    }

    return _search_node(tree->root, key);
}

unsigned int get_height_of_node_by_key(BinaryTree *tree, unsigned int key) {
    Laptop *node = search_value(tree, key);
    if (node == NULL) {
        printf("Laptop with key %u not found\n", key);
        return UINT_MAX;
    }
    return get_node_height(node);
}

unsigned int get_depth_of_node_by_key(BinaryTree *tree, unsigned int key) {
    Laptop *node = search_value(tree, key);
    if (node == NULL) {
        printf("Laptop with key %u not found\n", key);
        return UINT_MAX;
    }
    return get_node_depth(node);
}