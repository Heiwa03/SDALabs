
#include "OptionMenu.h"

void print_menu_options() {
    printf("1. Add a laptop to the list\n");
    printf("2. Remove a laptop from the list\n");
    printf("3. Print the list\n");
    printf("4. Invert the list\n");
    printf("5. Search the list\n");
    printf("6. Sort the list\n");
    printf("7. Insert at position\n");
    printf("8. Exit\n");
}

void print_sort_menu_options() {
    printf("1. Sort by brand\n");
    printf("2. Sort by model\n");
    printf("3. Sort by processor\n");
    printf("4. Sort by ram\n");
    printf("5. Sort by price\n");
}

void printf_search_menu_options() {
    printf("1. Search by brand\n");
    printf("2. Search by model\n");
    printf("3. Search by processor\n");
    printf("4. Search by ram\n");
    printf("5. Search by price\n");
}
unsigned int open_search_option_menu(LinkedList * list) {
    char field[50];
    char value[50];
    unsigned int option;
    printf_search_menu_options();
    printf("Choose an option: ");
    scanf("%u", &option);
    getchar();
    printf("Enter the value to search: ");
    fgets(value, 50, stdin);
    value[strlen(value) - 1] = '\0';
    switch (option) {
        case 1:
            strcpy(field, "brand");
            break;
        case 2:
            strcpy(field, "model");
            break;
        case 3:
            strcpy(field, "processor");
            break;
        case 4:
            strcpy(field, "ram");
            break;
        case 5:
            strcpy(field, "price");
            break;
        default:
            printf("Invalid option\n");
            return open_search_option_menu(list);
    }
    int index = search_list(list, field, value);
    if (index == -1) {
        printf("Laptop not found\n");
    } else {
        printf("Laptop found at index %d\n", index);
    }
    return QUIT;
}

unsigned int open_sort_option_menu(LinkedList * list) {
    unsigned int option;
    print_sort_menu_options();
    printf("Choose an option: ");
    scanf("%u", &option);
    getchar();
    switch (option) {
        case 1:
            sort_list(list, "brand");
            break;
        case 2:
            sort_list(list, "model");
            break;
        case 3:
            sort_list(list, "processor");
            break;
        case 4:
            sort_list(list, "ram");
            break;
        case 5:
            sort_list(list, "price");
            break;
        default:
            printf("Invalid option\n");
            return open_sort_option_menu(list);
    }
    printf("List sorted\n");
    return QUIT;
}

unsigned int open_option_menu(LinkedList * list) {
    char brand[50];
    char model[50];
    char processor[50];
    char ram[50];
    char price[50];
    unsigned int option;
    while (option != QUIT) {
        print_menu_options();
        printf("Choose an option: ");
        scanf("%u", &option);
        getchar();
        switch (option) {
            case 1:
                printf("Enter new laptop data:\n");
                get_laptop_data(brand, model, processor, ram, price);
                push_back(list, create_laptop(brand, model, processor, ram, price));
                break;
            case 2:
                printf("Enter the index of the laptop to remove: ");
                scanf("%u", &option);
                pop_index(list, option);
                break;
            case 3:
                print_list(list);
                break;
            case 4:
                invert_list(list);
                printf("List inverted\n");
                break;
            case 5:
                if (open_search_option_menu(list) == QUIT)
                    break;
            case 6:
                if (open_sort_option_menu(list) == QUIT)
                    break;
            case 7:
                int index_for_insert;
                printf("Enter the position you want to insert at: ");
                if (!(scanf("%d", &index_for_insert))) {
                    printf("Invalid index\n");
                    break;
                    getchar();// Get the newline that wants to ruin my life
                }
                getchar();
                if (!(_check_not_out_of_bounds_index(list, index_for_insert))) {
                    printf("Invalid index\n");
                    break;
                }
                printf("Enter new laptop data:\n");
                get_laptop_data(brand, model, processor, ram, price);
                insert(list, create_laptop(brand, model, processor, ram, price), index_for_insert);
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    }
    return QUIT;
}