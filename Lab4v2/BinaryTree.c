#include "BinaryTree.h"

Node *create_node(unsigned int key, Laptop *new_laptop) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;
    new_node->depth = 0;
    new_node->laptop = new_laptop;

    return new_node;
}

void free_node(Node *node) {
    if (node == NULL) {
        return;
    }
    free_laptop(node->laptop);
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
    BinaryTree *new_tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    if (new_tree == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    new_tree->root = NULL;
    new_tree->nr_of_nodes = 0;

    return new_tree;
}

int _find_max_value(int a, int b) {
    return (a > b) ? a : b;
}

int _get_balance(Node *current_node) {
    if (current_node == NULL)
        return 0;
    return get_node_height(current_node->left) - get_node_height(current_node->right);
}

Node *_right_rotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = _find_max_value(get_node_height(y->left), get_node_height(y->right))+1;
    x->height = _find_max_value(get_node_height(x->left), get_node_height(x->right))+1;
    return x;
}

Node *_left_rotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = _find_max_value(get_node_height(x->left), get_node_height(x->right))+1;
    y->height = _find_max_value(get_node_height(y->left), get_node_height(y->right))+1;
    return y;
}

Node *_insert_node(Node *node, unsigned int key, Laptop *new_laptop, int depth) {
    if (node == NULL) {
        Node *new_node = create_node(key, new_laptop);
        new_node->depth = depth;
        return new_node;
    }

    if (key < node->key) {
        node->left = _insert_node(node->left, key,new_laptop, depth + 1);
    } else if (key > node->key) {
        node->right = _insert_node(node->right, key, new_laptop, depth + 1);
    } else {
        printf("ERROR:Key already exists\n");
        return node;
    }

    node->height = 1 + _find_max_value((node->left ? node->left->height : -1), 
                           (node->right ? node->right->height : -1));

    int balance = _get_balance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return _right_rotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return _left_rotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left =  _left_rotate(node->left);
        return _right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = _right_rotate(node->right);
        return _left_rotate(node);
    }

    return node;
}

void insert_value(BinaryTree *tree, unsigned int key, Laptop *new_laptop) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    tree->root = _insert_node(tree->root, key, new_laptop, 0);
    tree->nr_of_nodes++;
}

Node *_find_min_value_node(Node *node) {
    Node *current_node = node;

    while (current_node && current_node->left != NULL)
        current_node = current_node->left;

    return current_node;
}

Node *_delete_node(Node *root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = _delete_node(root->left, key);
    else if (key > root->key)
        root->right = _delete_node(root->right, key);
    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = _find_min_value_node(root->right);

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

void _print_inorder(Node *node) {
    if (node == NULL) {
        return;
    }

    _print_inorder(node->left);
    printf("%u\n", node->key);
    print_laptop(node->laptop);
    _print_inorder(node->right);
}

void _print_preorder(Node *node) {
    if (node == NULL) {
        return;
    }

    printf("%u ", node->key);
    print_laptop(node->laptop);
    _print_preorder(node->left);
    _print_preorder(node->right);
}

void _print_postorder(Node *node) {
    if (node == NULL) {
        return;
    }

    _print_postorder(node->left);
    _print_postorder(node->right);
    printf("%u ", node->key);
    print_laptop(node->laptop);
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

unsigned int get_node_height(Node *node) {
    if (node == NULL) {
        printf("Node is not initialized\n");
        return UINT_MAX;
    }

    return node->height;
}

unsigned int get_node_depth(Node *node) {
    if (node == NULL) {
        printf("Node is not initialized\n");
        return UINT_MAX;
    }

    return node->depth;
}

unsigned int get_node_nr_of_children(Node *node) {
    if (node == NULL) {
        printf("Node is not initialized\n");
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

Node* _find_parent_of_node(Node* node, Node* parent, unsigned int key) {
    if (node == NULL) {
        return NULL;
    }

    if (node->key == key) {
        return parent;
    }

    Node* left_search = _find_parent_of_node(node->left, node, key);
    Node* right_search = _find_parent_of_node(node->right, node, key);

    return left_search != NULL ? left_search : right_search;
}

Node* get_parent_of_node(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return NULL;
    }

    if (tree->root->key == key) {
        return NULL; // root node has no parent
    }

    return _find_parent_of_node(tree->root, NULL, key);
}

void _get_leaves(Node *node) {
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        printf("%u ", node->key);
        print_laptop(node->laptop);
    } else {
        _get_leaves(node->left);
        _get_leaves(node->right);
    }
}

void show_all_leaves_of_tree(BinaryTree *tree) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    _get_leaves(tree->root);
    printf("\n");
}

Node *_search_node(Node *node, unsigned int key) {
    if (node == NULL || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return _search_node(node->left, key);
    } else {
        return _search_node(node->right, key);
    }
}

Node *search_value(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return NULL;
    }

    return _search_node(tree->root, key);
}

void _print_depth_inorder(Node *node) {
    if (node == NULL) {
        return;
    }

    _print_depth_inorder(node->left);
    printf("Key: %u, Depth: %u\n", node->key, node->depth);
    _print_depth_inorder(node->right);
}

void print_depth_of_each_node(BinaryTree *tree) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    _print_depth_inorder(tree->root);
}

void _print_height_inorder(Node *node) {
    if (node == NULL) {
        return;
    }

    _print_height_inorder(node->left);
    printf("Key: %u, Height: %u\n", node->key, node->height);
    _print_height_inorder(node->right);
}

void print_height_of_each_node(BinaryTree *tree) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    _print_height_inorder(tree->root);
}

void _print_node_properties(Node *node, unsigned int get_height, unsigned int get_depth, unsigned int get_nr_of_children) {
    if (node == NULL) {
        return;
    }

    _print_node_properties(node->left, get_height, get_depth, get_nr_of_children);

    printf("Key: %u", node->key);
    if (get_height) {
        printf(", Height: %u", node->height);
    }
    if (get_depth) {
        printf(", Depth: %u", node->depth);
    }
    if (get_nr_of_children) {
        printf(", Nr of children: %u", get_node_nr_of_children(node));
    }
    print_laptop(node->laptop);
    printf("\n");

    _print_node_properties(node->right, get_height, get_depth, get_nr_of_children);
}

void print_properties_of_each_node(BinaryTree *tree, unsigned int get_height, unsigned int get_depth, unsigned int get_nr_of_children) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }

    _print_node_properties(tree->root, get_height, get_depth, get_nr_of_children);
}

unsigned int get_height_of_node_by_key(BinaryTree *tree, unsigned int key) {
    Node *node = search_value(tree, key);
    if (node == NULL) {
        printf("Node with key %u not found\n", key);
        return UINT_MAX;
    }
    return get_node_height(node);
}

unsigned int get_depth_of_node_by_key(BinaryTree *tree, unsigned int key) {
    Node *node = search_value(tree, key);
    if (node == NULL) {
        printf("Node with key %u not found\n", key);
        return UINT_MAX;
    }
    return get_node_depth(node);
}

unsigned int get_tree_mirror_status(BinaryTree *tree) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return UNINITIALIZED;
    }

    return tree->is_mirrored;
}