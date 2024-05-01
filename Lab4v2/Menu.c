#include "Menu.h"

void print_menu() {
    printf("\nMenu:\n");
    printf("0. Clear tree\n");
    printf("1. Insert value\n");
    printf("2. Delete value\n");
    printf("3. Search value\n");
    printf("4. Print tree\n");
    printf("5. Show height of tree\n");
    printf("6. Perform BFS\n");
    printf("7. Perform DFS\n");
    printf("10. Exit\n");
}

void show_menu_for_tree_print() {
    printf("1. In-order\n");
    printf("2. Pre-order\n");
    printf("3. Post-order\n");
}

int get_user_input() {
    int user_input;
    printf("Enter your choice: ");
    scanf("%d", &user_input);
    getchar();
    return user_input;
}

void open_menu (BinaryTree * tree) {
    int user_input;
    unsigned int key;
    Node *node;
    unsigned int get_height, get_depth, get_nr_of_children;
    char brand[50];
    char model[50];
    char processor[50];
    char ram[50];
    char price[50];
    LinkedList *bfs_list = NULL;
    LinkedList *dfs_list = NULL;

    do {
        print_menu();
        user_input = get_user_input();
        switch (user_input) {
            case 0:
                clear_tree(tree);
                printf("Tree cleared\n");
                break;
            case 1:
                printf("Enter the key to insert: ");
                scanf("%u", &key);
                getchar();
                get_laptop_data(brand, model, processor, ram, price);
                insert_value(tree, key, create_laptop(brand, model, processor, ram, price));
                break;
            case 2:
                printf("Enter the key to delete: ");
                scanf("%u", &key);
                getchar();
                delete_value(tree, key);
                break;
            case 3:
                printf("Enter the key to search: ");
                scanf("%u", &key);
                getchar();
                node = search_value(tree, key);
                if (node != NULL) {
                    printf("Node found: %u\n", node->key);
                } else {
                    printf("Node not found\n");
                }
                break;
            case 4:
                show_menu_for_tree_print();
                user_input = get_user_input();
                if (user_input < 1 || user_input > 3) {
                    printf("Invalid choice\n");
                    break;
                }
                printf("\nShowing tree:\n");
                print_tree(tree, user_input);
                printf("\n");
                break;
            case 5:
                printf("\nHeight of tree: %u\n\n", 1 + get_tree_height(tree));
                break;
            case 6:
                printf("Result of BFS:\n");
                LinkedList *bfs_list = perform_bfs(tree);
                print_dfs_bfs_result(bfs_list);
                break;
            case 7:
                printf("Result of DFS:\n");
                LinkedList *dfs_list = perform_dfs(tree);
                print_dfs_bfs_result(dfs_list);
                break;
            case 10:
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (user_input != QUIT);

    return;
}