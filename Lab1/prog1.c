#define NOT_FOUND -1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    char first_name [100];
    char last_name [100];
    unsigned int age;
    char role [150];
    unsigned int has_server_access;
};

void return_to_menu ();
void init_static_list (int size_of_list, struct Employee list []);
void print_static_list (int size_of_list, struct Employee list []);
int find_element_by_first_name (char * first_name, int size_of_list, struct Employee list []);
int find_element_by_last_name (char * last_name, int size_of_list, struct Employee list []);
int find_element_by_role (char * role, int size_of_list, struct Employee list []);
void start_menu (int size_of_list, struct Employee list []); 

int main () {
    int size_of_list = 0;
    printf("Size of list? = ");
    scanf("%d", &size_of_list);

    struct Employee active_list [size_of_list];
    init_static_list (size_of_list, active_list);
    print_static_list (size_of_list, active_list);

    start_menu(size_of_list, active_list);

    return 0;
}

void start_menu (int size_of_list, struct Employee list []) {
    int input_option = -1;
    do {
        printf("Choose a search type:\n");
        printf("1.Find by First name\n2.Find by Last name\n3.Find by Role\n4.Print active_list\n\n0.Quit\n");
        scanf("%u", &input_option);
        int position = -1;
        char search_string [200];
        switch (input_option)
        {
        case 0:
            printf("Exit requested\n");
            break;
        case 1:
            printf("Enter the first name you want to search for: ");
            scanf("%s", &search_string);
            position = find_element_by_first_name(search_string, size_of_list, list);
            if (NOT_FOUND == position) {
                printf("Couldn't find element\n");
                return_to_menu();
                break;
            } else {
                printf("Found at position %d in the active_list\n", position);
                return_to_menu();
                break;
            }
            break;
        case 2:
            printf("Enter the last name you want to search for: ");
            scanf("%s", &search_string);
            position = find_element_by_last_name(search_string, size_of_list, list);
            if (NOT_FOUND == position) {
                printf("Couldn't find element\n");
                return_to_menu();
                break;
            } else {
                printf("Found at position %d in the active_list\n", position);
                return_to_menu();
                break;
            }
        case 3:
            printf("Enter the role you want to search for: ");
            scanf("%s", &search_string);
            position = find_element_by_role(search_string, size_of_list, list);
            if (NOT_FOUND == position) {
                printf("Couldn't find element\n");
                return_to_menu();
                break;
            } else {
                printf("Found at position %d in the active_list\n", position);
                return_to_menu();
                break;
            }
        case 4:
            print_static_list(size_of_list, list);
            return_to_menu();
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (input_option != 0);
}
/*
unsigned int find_element_by_last_name (int size_of_list, struct Employee list []) {
    int found = 0;
    char search_string [200];
    printf("Enter the last name you want to search for: ");
    scanf("%s", &search_string);
    for (int i = 0; i < size_of_list; i++) {
        if (0 == strcmp(list[i].last_name, search_string)) {
            printf("Found at position %d in the active_list\n", i);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Couldn't find element\n");
    }
}
*/

int find_element_by_last_name (char * last_name, int size_of_list, struct Employee list []) {
    for (int index = 0; index < size_of_list; index++) {
        if (!(strcmp(list[index].last_name, last_name))) {
            return index;
        }
    }
    return NOT_FOUND;
}

int find_element_by_first_name (char * first_name, int size_of_list, struct Employee list []) {
    for (int index = 0; index < size_of_list; index++) {
        if (!(strcmp(list[index].first_name, first_name))) {
            return index;
        }
    }
    return NOT_FOUND;
}

int find_element_by_role (char * role, int size_of_list, struct Employee list []) {
    for (int index = 0; index < size_of_list; index++) {
        if (!(strcmp(list[index].role, role))) {
            return index;
        }
    }
    return NOT_FOUND;
}

void print_static_list (int size_of_list, struct Employee list []) {
    printf("\nDisplaying active_list:\n");
    for (int index = 0; index < size_of_list; index++) {
        printf("Employee nr.%d\n", index+1);
        printf("First name: %s\n", list[index].first_name);
        printf("Last name: %s\n", list[index].last_name);
        printf("Age: %u\n", list[index].age);
        printf("Role: %s\n", list[index].role);
        printf("Server access: %u\n\n", list[index].has_server_access);
    }
}

void init_static_list (int size_of_list, struct Employee list []) {
    printf("Input the employee data:\n");
    for (int index = 1; index <= size_of_list; index++) {
        printf("Employee nr.%d\n", index);
        printf("First name: ");
        scanf("%s", &(list+(index-1))->first_name);
        printf("Last name: ");
        scanf("%s", &(list+(index-1))->last_name);
        printf("Age: ");
        scanf("%u", &(list+(index-1))->age);
        printf("Role in the company: ");
        scanf("%s", &(list+(index-1))->role);
        printf("Has server access?: ");
        scanf("%u", &(list+(index-1))->has_server_access);
    }
}

void return_to_menu () {
    int option = -1;
    printf("Return to menu? (1 = yes, 0 = no)\n");
    scanf("%d", &option);
    switch (option)
    {
    case 0:
        exit(0);
        break;
    default:
        break;
    }
}
