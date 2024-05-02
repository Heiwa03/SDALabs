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
    new_tree->is_mirrored = NOT_MIRRORED;
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

Node *_insert_node(Node *node, unsigned int key, Laptop *new_laptop, int depth, bool is_mirrored) {
    if (node == NULL) {
        Node *new_node = create_node(key, new_laptop);
        new_node->depth = depth;
        return new_node;
    }
    int balance = 0;
    switch (is_mirrored) {
        case MIRRORED:
            if (key < node->key) {
                node->right = _insert_node(node->right, key, new_laptop, depth + 1, is_mirrored);
            } else if (key > node->key) {
                node->left = _insert_node(node->left, key, new_laptop, depth + 1, is_mirrored);
            } else {
                printf("ERROR:Key already exists\n");
                return node;
            }

            node->height = 1 + _find_max_value((node->left ? node->left->height : -1), 
                                (node->right ? node->right->height : -1));

            balance = _get_balance(node);

            // If this node becomes unbalanced, then there are 4 cases

            // Everthing on left Case
            if (balance > 1 && key > node->left->key)
                return _left_rotate(node);

            // Everything on right Case
            if (balance < -1 && key < node->right->key)
                return _right_rotate(node);

            // Left Right Case
            if (balance > 1 && key < node->left->key) {
                node->left =  _right_rotate(node->left);
                return _left_rotate(node);
            }

            // Right Left Case
            if (balance < -1 && key > node->right->key) {
                node->right = _left_rotate(node->right);
                return _right_rotate(node);
            }

            return node;
            break;
        case NOT_MIRRORED:
            if (key < node->key) {
                node->left = _insert_node(node->left, key,new_laptop, depth + 1, is_mirrored);
            } else if (key > node->key) {
                node->right = _insert_node(node->right, key, new_laptop, depth + 1, is_mirrored);
            } else {
                printf("ERROR:Key already exists\n");
                return node;
            }

            node->height = 1 + _find_max_value((node->left ? node->left->height : -1), 
                                (node->right ? node->right->height : -1));

            balance = _get_balance(node);

            // Balancing nodes

            // Everything on left Case
            if (balance > 1 && key < node->left->key)
                return _right_rotate(node);

            // Everything on right Case
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
            break;
        default:
            printf("ERROR:Mirror status is invalid. Tree may be corrupted.");
            return NULL;
            break;
    }
}

void insert_value(BinaryTree *tree, unsigned int key, Laptop *new_laptop) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }
    bool is_mirrored = get_mirror_status(tree);
    tree->root = _insert_node(tree->root, key, new_laptop, 0, is_mirrored);
    tree->nr_of_nodes++;
}

Node *_find_min_value_node(Node *node) {
    Node *current_node = node;

    while (current_node && current_node->left != NULL)
        current_node = current_node->left;

    return current_node;
}

Node *_find_max_value_node(Node *node) {
    Node *current_node = node;

    while (current_node && current_node->right != NULL)
        current_node = current_node->right;

    return current_node;
}

Node *_delete_node(Node *root, int key, bool is_mirrored) {
    if (root == NULL) return root;
    switch (is_mirrored)
    {
    case MIRRORED:
        if (key < root->key)
            root->right = _delete_node(root->right, key, is_mirrored);
        else if (key > root->key)
            root->left = _delete_node(root->left, key, is_mirrored);
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

            Node *temp = _find_max_value_node(root->left);

            root->key = temp->key;

            root->left = _delete_node(root->left, temp->key, is_mirrored);
        }
        return root;
        break;
    default:
        if (key < root->key)
            root->left = _delete_node(root->left, key, is_mirrored);
        else if (key > root->key)
            root->right = _delete_node(root->right, key, is_mirrored);
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

            root->right = _delete_node(root->right, temp->key, is_mirrored);
        }
        return root;
        break;
    }
}

void delete_value(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return;
    }
    bool is_mirrored = get_mirror_status(tree);
    tree->root = _delete_node(tree->root, key, is_mirrored);
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

Node *_search_node(Node *node, unsigned int key, bool is_mirrored) {
    if (node == NULL || node->key == key) {
        return node;
    }
    switch (is_mirrored)
    {
    case MIRRORED:
        if (key < node->key) {
            return _search_node(node->right, key, is_mirrored);
        } else {
            return _search_node(node->left, key, is_mirrored);
        }
        break;
    default:
        if (key < node->key) {
            return _search_node(node->left, key, is_mirrored);
        } else {
            return _search_node(node->right, key, is_mirrored);
        }
        break;
    }
}

Node *search_value(BinaryTree *tree, unsigned int key) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return NULL;
    }
    bool is_mirrored = get_mirror_status(tree);
    return _search_node(tree->root, key, is_mirrored);
}

unsigned int get_tree_mirror_status(BinaryTree *tree) {
    if (tree == NULL) {
        printf("Tree is not initialized\n");
        return UNINITIALIZED;
    }

    return tree->is_mirrored;
}

LinkedList* perform_bfs(BinaryTree *tree) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    Queue* queue = create_new_queue();
    LinkedList* bfs_result = create_new_linkedlist();
    enqueue(queue, tree->root);

    while (!get_is_empty(queue)) {
        Node* node = (Node*)dequeue(queue);
        add_to_linkedlist(bfs_result, node);

        // Enqueue left child
        if (node->left != NULL) {
            enqueue(queue, node->left);
        }

        // Enqueue right child
        if (node->right != NULL) {
            enqueue(queue, node->right);
        }
    }
    free_queue(queue);
    return bfs_result;
}

LinkedList* _perform_dfs_helper(Node* node, LinkedList* list) {
    if (node == NULL) {
        return list;
    }

    // Create a new node for the linked list
    LLNode* new_llnode = (LLNode*)malloc(sizeof(LLNode));
    new_llnode->data = node;
    new_llnode->next = NULL;

    // Add the new node to the end of the linked list
    if (list->head == NULL) {
        list->head = new_llnode;
    } else {
        LLNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_llnode;
    }

    // Recur for the left subtree
    _perform_dfs_helper(node->left, list);

    // Recur for the right subtree
    _perform_dfs_helper(node->right, list);

    return list;
}

LinkedList* perform_dfs(BinaryTree *tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("ERROR:Tree is not initialized or empty\n");
        return NULL;
    }

    // Create a new linked list
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;

    // Perform DFS and return the linked list
    return _perform_dfs_helper(tree->root, list);
}

void print_dfs_bfs_result(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        printf("ERROR:List is not initialized or empty\n");
        return;
    }

    LLNode* current = list->head;
    while (current != NULL) {
        Node* node = (Node*)current->data;
        printf("Key: %u\n", node->key);
        print_laptop(node->laptop);
        current = current->next;
    }
}
bool get_mirror_status(BinaryTree* tree) {
    if (tree == NULL) {
        printf("ERROR:Tree is not initialized\n");
        return UNINITIALIZED;
    }

    return tree->is_mirrored;
}

void _mirror_tree(Node* node) {
    if (node == NULL) {
        return;
    }

    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;

    _mirror_tree(node->left);
    _mirror_tree(node->right);
}

bool mirror_tree(BinaryTree* tree) {
    if (tree == NULL) {
        printf("ERROR:Tree is not initialized\n");
        return NOT_MIRRORED;
    }
    // Check if the tree is mirrored and change the status accordingly
    bool is_mirrored = get_mirror_status(tree);
    if (is_mirrored == MIRRORED) {
        tree->is_mirrored = NOT_MIRRORED;
    } else {
        tree->is_mirrored = MIRRORED;
    }

    _mirror_tree(tree->root);
    return tree->is_mirrored;
}