#include "OptionMenu.h"

void print_menu() {
    printf("\n\n");
    printf("1. Append new employee\n");
    printf("2. Prepend new employee\n");
    printf("3. Insert new employee at position\n");
    printf("4. Delete employee at position\n");
    printf("5. Search for employee by role\n");
    printf("6. Search for employee by first name\n");
    printf("7. Search for employee by last name\n");
    printf("8. Sort employee list by role\n");
    printf("9. Sort employee list by first name\n");
    printf("10. Sort employee list by last name\n");
    printf("11. Print employee list\n");
    printf("12. Exit\n");
    printf("Enter your choice: ");
}

int option_menu(EmployeeList ** active_list) {
    int user_choice;
    int position = 0;
    do {
        print_menu();
        scanf("%d", &user_choice);
        switch(user_choice){
            case 1:
                append_new_employee(*active_list);
                break;
            case 2:
                prepend_new_employee(*active_list);
                break;
            case 3:
                printf("Choose insertion position: ");
                scanf("%d", &position);
                insert_at_pos_new_employee(*active_list, position);
                break;
            case 4:
                printf("Choose deletion position: ");
                scanf("%d", &position);
                delete_at_pos_employee(*active_list, position);
                break;
            case 5:
                char role[200];
                printf("Input role to search by: ");
                scanf("%s", role);
                search_employee(*active_list, _search_compare_role, role);
                break;
            case 6:
                char first_name[200];
                printf("Input first name to search by: ");
                scanf("%s", first_name);
                search_employee(*active_list, _search_compare_first_name, first_name);
                break;
            case 7:
                char last_name[200];
                printf("Input last name to search by: ");
                scanf("%s", last_name);
                search_employee(*active_list, _search_compare_last_name, last_name);
                break;
            case 8:
                sort_employee_list(*active_list, _sort_compare_role);
                break;
            case 9:
                sort_employee_list(*active_list, _sort_compare_first_name);
                break;
            case 10:
                sort_employee_list(*active_list, _sort_compare_last_name);
                break;
            case 11:
                print_employee_list(*active_list);
                break;
            case 12:
                break;
            default:
                printf("Invalid input\n");
        }
    } while (user_choice != 12);
}


