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

struct EmployeeArray
{
    Employee * 
    size_t 
    
}

// menu functions
void return_to_menu ();
void operations_menu (int size, struct Employee* db);

// init and print functions
void init_dynamic_db (int n, struct Employee* db);
void print_dynamic_db (int size, struct Employee* db);

// search functions
unsigned int find_element_by_role (int size, struct Employee* db);
unsigned int find_element_by_first_name (int size, struct Employee* db);
unsigned int find_element_by_last_name (int size, struct Employee* db);

// sorting functions
void sort_by_age(struct Employee* db, int size);
void sort_by_first_name(struct Employee* db, int size);
void sort_by_last_name(struct Employee* db, int size);
void sort_by_role(struct Employee* db, int size);

// direct database manipulation functions
struct Employee* append_element(struct Employee* db, int* size);
struct Employee* prepend_element(struct Employee* db, int* size);
struct Employee* insert_element(struct Employee* db, int* size);
struct Employee* remove_element(struct Employee* db, int* size);

int main () {
    int size = 0;
    printf("Size of array? = ");
    scanf("%d", &size);

    struct Employee* database = malloc(size * sizeof(struct Employee));
    if (NULL == database) {
        printf("ERROR: Failed to allocate memory\n");
        return 1;
    }

    init_dynamic_db (size, database);
    print_dynamic_db (size, database);

    operations_menu(size, database);

    free(database);

    return 0;
}

void init_dynamic_db (int n, struct Employee* db) {
    printf("Input the employee data:\n");
    for (int i = 1; i <= n; i++) {
        printf("Employee nr.%d\n", i);
        printf("First name: ");
        scanf("%s", (db+(i-1))->first_name);
        printf("Last name: ");
        scanf("%s", (db+(i-1))->last_name);
        printf("Age: ");
        scanf("%u", &(db+(i-1))->age);
        printf("Role in the company: ");
        scanf("%s", (db+(i-1))->role);
        printf("Has server access?: ");
        scanf("%u", &(db+(i-1))->has_server_access);
    }
}

void print_dynamic_db (int size, struct Employee* db) {
    printf("\nDisplaying database:\n");
    for (int i = 0; i < size; i++) {
        printf("Employee nr.%d\n", i+1);
        printf("First name: %s\n", (db+i)->first_name);
        printf("Last name: %s\n", (db+i)->last_name);
        printf("Age: %u\n", (db+i)->age);
        printf("Role: %s\n", (db+i)->role);
        printf("Server access: %u\n\n", (db+i)->has_server_access);
    }
}

unsigned int find_element_by_last_name (int size, struct Employee* db) {
    int found = 0;
    char search_query [200];
    printf("Enter the last name you want to search for: ");
    scanf("%s", search_query);
    for (int i = 0; i < size; i++) {
        if (0 == strcmp((db+i)->last_name, search_query)) {
            printf("Found at position %d in the database\n", i);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Couldn't find element\n");
    }
}

unsigned int find_element_by_first_name (int size, struct Employee* db) {
    int found = 0;
    char search_query [200];
    printf("Enter the first name you want to search for: ");
    scanf("%s", search_query);
    for (int i = 0; i < size; i++) {
        if (0 == strcmp((db+i)->first_name, search_query)) {
            printf("Found at position %d in the database\n", i);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Couldn't find element\n");
    }
}

unsigned int find_element_by_role (int size, struct Employee* db) {
    int found = 0;
    char search_query [200];
    printf("Enter the role you want to search for: ");
    scanf("%s", search_query);
    for (int i = 0; i < size; i++) {
        if (0 == strcmp((db+i)->role, search_query)) {
            printf("Found at position %d in the database\n", i);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Couldn't find element\n");
    }
}

/* // Old version of operations_menu with int input_buffer
void operations_menu (int size, struct Employee* db) {
    int input_buffer = -1;
    do {
        printf("Choose a search type:\n");
        printf("1.Find by First name\n2.Find by Last name\n3.Find by Role\n\n4.Print database\n\n5.Sort by age\n6.Sort by first name\n7.Sort by last name\n8.Sort by role\n\na.Append element\n\n0.Quit\n");
        scanf("%u", &input_buffer);
        switch (input_buffer)
        {
        case 0:
            printf("Exit requested\n");
            break;
        case 1:
            find_element_by_first_name(size, db);
            return_to_menu();
            break;
        case 2:
            find_element_by_last_name(size, db);
            return_to_menu();
            break;
        case 3:
            find_element_by_role(size, db);
            return_to_menu();
            break;
        case 4:
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 5:
            sort_by_age(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 6:
            sort_by_first_name(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 7:
            sort_by_last_name(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 8:
            sort_by_role(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (input_buffer != 0);
}
*/

void operations_menu (int size, struct Employee* db) {
    char input_buffer;
    do {
        printf("Choose a search type:\n");
        printf("a.Find by First name\nb.Find by Last name\nc.Find by Role\nd.Print database\ne.Sort by age\nf.Sort by first name\ng.Sort by last name\nh.Sort by role\ni.Append element\nj.Prepend element\nk.Insert element\nl.Remove element\n\nq.Quit\n");
        scanf(" %c", &input_buffer);
        switch (input_buffer)
        {
        case 'q':
            printf("Exit requested\n");
            break;
        case 'a':
            find_element_by_first_name(size, db);
            return_to_menu();
            break;
        case 'b':
            find_element_by_last_name(size, db);
            return_to_menu();
            break;
        case 'c':
            find_element_by_role(size, db);
            return_to_menu();
            break;
        case 'd':
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'e':
            sort_by_age(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'f':
            sort_by_first_name(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'g':
            sort_by_last_name(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'h':
            sort_by_role(db, size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'i':
            db = append_element(db, &size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'j':
            db = prepend_element(db, &size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'k':
            db = insert_element(db, &size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        case 'l':
            db = remove_element(db, &size);
            print_dynamic_db(size, db);
            return_to_menu();
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (input_buffer != 'j');
}

int compare_by_age(const void* a, const void* b) {
    struct Employee* employeeA = (struct Employee*) a;
    struct Employee* employeeB = (struct Employee*) b;
    return (employeeA->age - employeeB->age);
}
void sort_by_age(struct Employee* db, int size) {
    qsort(db, size, sizeof(struct Employee), compare_by_age);
}

int compare_by_first_name(const void* a, const void* b) {
    struct Employee* employeeA = (struct Employee*) a;
    struct Employee* employeeB = (struct Employee*) b;
    return strcmp(employeeA->first_name, employeeB->first_name);
}

void sort_by_first_name(struct Employee* db, int size) {
    qsort(db, size, sizeof(struct Employee), compare_by_first_name);
}

int compare_by_last_name(const void* a, const void* b) {
    struct Employee* employeeA = (struct Employee*) a;
    struct Employee* employeeB = (struct Employee*) b;
    return strcmp(employeeA->last_name, employeeB->last_name);
}

void sort_by_last_name(struct Employee* db, int size) {
    qsort(db, size, sizeof(struct Employee), compare_by_last_name);
}

int compare_by_role(const void* a, const void* b) {
    struct Employee* employeeA = (struct Employee*) a;
    struct Employee* employeeB = (struct Employee*) b;
    return strcmp(employeeA->role, employeeB->role);
}

void sort_by_role(struct Employee* db, int size) {
    qsort(db, size, sizeof(struct Employee), compare_by_role);
}

struct Employee* append_element(struct Employee* db, int* size) {
    struct Employee new_employee;

    printf("Enter first name: ");
    scanf("%s", new_employee.first_name);
    printf("Enter last name: ");
    scanf("%s", new_employee.last_name);
    printf("Enter age: ");
    scanf("%u", &new_employee.age);
    printf("Enter role: ");
    scanf("%s", new_employee.role);
    printf("Enter server access (1 for yes, 0 for no): ");
    scanf("%u", &new_employee.has_server_access);

    struct Employee* new_db = realloc(db, (*size + 1) * sizeof(struct Employee));
    if (new_db == NULL) {
        printf("Memory allocation failed\n");
        return db;  // if the kernel is a bitch, return old database
    }
    new_db[*size] = new_employee;
    (*size)++;
    return new_db;
}

struct Employee* prepend_element(struct Employee* db, int* size) {
    struct Employee new_employee;

    printf("Enter first name: ");
    scanf("%s", new_employee.first_name);
    printf("Enter last name: ");
    scanf("%s", new_employee.last_name);
    printf("Enter age: ");
    scanf("%u", &new_employee.age);
    printf("Enter role: ");
    scanf("%s", new_employee.role);
    printf("Enter server access (1 for yes, 0 for no): ");
    scanf("%u", &new_employee.has_server_access);

    struct Employee* new_db = realloc(db, (*size + 1) * sizeof(struct Employee));
    if (new_db == NULL) {
        printf("Memory allocation failed\n");
        return db;  // if the kernel is a bitch, return old database
    }

    // Pray to God almighty memmove doesn't fail making space at the beginning
    memmove(&new_db[1], &new_db[0], *size * sizeof(struct Employee));

    new_db[0] = new_employee;
    (*size)++;
    return new_db;
}

struct Employee* insert_element(struct Employee* db, int* size) {
    struct Employee new_employee;
    int position;

    printf("Enter the position where the new employee will be inserted: ");
    scanf("%d", &position);

    if (position < 0 || position > *size) {
        printf("ERROR:Invalid position!\nWARNING:Database is unchanged\n");
        return db;
    }

    printf("Enter first name: ");
    scanf("%s", new_employee.first_name);
    printf("Enter last name: ");
    scanf("%s", new_employee.last_name);
    printf("Enter age: ");
    scanf("%u", &new_employee.age);
    printf("Enter role: ");
    scanf("%s", new_employee.role);
    printf("Enter server access (1 for yes, 0 for no): ");
    scanf("%u", &new_employee.has_server_access);

    struct Employee* new_db = realloc(db, (*size + 1) * sizeof(struct Employee));
    if (new_db == NULL) {
        printf("Memory allocation failed\n");
        return db;  // if the kernel is a bitch, return old database
    }

    // Pray to God almighty memmove doesn't fail making space at the beginning
    memmove(&new_db[position + 1], &new_db[position], (*size - position) * sizeof(struct Employee));

    new_db[position] = new_employee;  // add new employee
    (*size)++;
    return new_db;
}

struct Employee* remove_element(struct Employee* db, int* size) {
    int position;

    printf("Enter the position of the employee to be removed: ");
    scanf("%d", &position);

    if (position < 0 || position >= *size) {
        printf("Invalid position\n");
        return db;
    }

    // Pray to God almighty memmove doesn't fail making space at the beginning
    memmove(&db[position], &db[position + 1], (*size - position - 1) * sizeof(struct Employee));

    (*size)--;  // decrement the size

    struct Employee* new_db = realloc(db, *size * sizeof(struct Employee));
    // WARN: For some ODD FUCKING REASON, this piece of code sometimes fails on Windows...
    //       But it does work completely fine on Linux sooooooooo........... Linux win!!!
    if (new_db == NULL && *size > 0) {  // if realloc fails and size > 0
        printf("Memory allocation failed\n");
        return db;  // return the old database
    }
    return new_db;  // return the new database
}

void return_to_menu () {
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