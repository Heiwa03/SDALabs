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
void return_request () {
    int buffer = -1;
    printf("Return to menu? (1 = yes, 0 = no)\n");
    scanf("%d", &buffer);
    switch (buffer)
    {
    case 0:
        exit(0);
        break;

    default:
        break;
    }
}
void init_static_db (int n, struct Employee db []) {
    printf("Input the employee data:\n");
    for (int i = 1; i <= n; i++) {
        printf("Employee nr.%d\n", i);
        printf("First name: ");
        scanf("%s", &(db+(i-1))->first_name);
        printf("Last name: ");
        scanf("%s", &(db+(i-1))->last_name);
        printf("Age: ");
        scanf("%u", &(db+(i-1))->age);
        printf("Role in the company: ");
        scanf("%s", &(db+(i-1))->role);
        printf("Has server access?: ");
        scanf("%u", &(db+(i-1))->has_server_access);
    }
}
void print_static_db (int size, struct Employee db []) {
    printf("\nDisplaying database:\n");
    for (int i = 0; i < size; i++) {
        printf("Employee nr.%d\n", i+1);
        printf("First name: %s\n", db[i].first_name);
        printf("Last name: %s\n", db[i].last_name);
        printf("Age: %u\n", db[i].age);
        printf("Role: %s\n", db[i].role);
        printf("Server access: %u\n\n", db[i].has_server_access);
    }
}
unsigned int find_element_by_first_name (int size, struct Employee db []) {
    int found = 0;
    char search_query [200];
    printf("Enter the first name you want to search for: ");
    scanf("%s", &search_query);
    for (int i = 0; i < size; i++) {
        if (0 != strcmp(db[i].first_name, search_query)) {
            printf("Found at position %d in the database\n", i);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Couldn't find element\n");
    }
}
void operations_menu (int size, struct Employee db []) {
    int input_buffer = -1;
    do {
        printf("Choose a search type:\n");
        printf("1.Find by First name\n2.Find by Last name\n3.Find by Age\n4.Find by Role\n5.Find by Server Access\n\n0.Quit\n");
        scanf("%u", &input_buffer);
        switch (input_buffer)
        {
        case 0:
            printf("Exit requested\n");
            break;
        case 1:
            find_element_by_first_name(size, db);
            return_request();
            break;
        
        default:
            printf("Invalid input\n");
            break;
        }
    } while (input_buffer != 0);
}

int main () {
    int size = 0;
    printf("Size of array? = ");
    scanf("%d", &size);

    struct Employee database [size];
    init_static_db (size, database);
    print_static_db (size, database);

    operations_menu(size, database);

    return 0;
}