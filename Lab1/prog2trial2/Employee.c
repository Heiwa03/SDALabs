#include "Employee.h"

void get_employee_data (char * first_name, char * last_name, unsigned int * age, char * role) {
    printf("First name: ");
    scanf("%s", first_name);
    printf("Last name: ");
    scanf("%s", last_name);
    printf("Age: ");
    scanf("%u", age);
    printf("Role in the company: ");
    scanf("%s", role);
}
Employee* create_employee (char * first_name, char * last_name, unsigned int age, char * role) {
    Employee * employee = (Employee *) malloc(sizeof(Employee));
    if (employee == NULL) {
        printf("ERROR: create_employee failed to allocate temp employee memory\n");
        return NULL;
    }
    employee->first_name = (char *) malloc(strlen(first_name) + 1);
    employee->last_name = (char *) malloc(strlen(last_name) + 1);
    employee->role = (char *) malloc(strlen(role) + 1);
    strcpy(employee->first_name, first_name);
    strcpy(employee->last_name, last_name);
    employee->age = age;
    strcpy(employee->role, role);
    return employee;
}

EmployeeList* create_employee_list (int size_of_list) {
    EmployeeList * tmp_employee_list = (EmployeeList *) malloc(sizeof(EmployeeList));
    if (tmp_employee_list == NULL) {
        printf("ERROR: create_employee_list failed to allocate tmp_employee_list memory\n");
        return NULL;
    }
    tmp_employee_list->list = (Employee *) malloc(size_of_list * sizeof(Employee));
    tmp_employee_list->size_of_list = size_of_list;
    return tmp_employee_list;
}

void free_employee (Employee * employee) {
    free(employee->first_name);
    free(employee->last_name);
    free(employee->role);
    free(employee);
}

void free_employee_list (EmployeeList * employee_list) {
    free(employee_list->list);
    free(employee_list);
}

void print_employee (Employee * employee) {
    printf("First name: %s\n", employee->first_name);
    printf("Last name: %s\n", employee->last_name);
    printf("Age: %u\n", employee->age);
    printf("Role: %s\n", employee->role);
}

void print_employee_list (EmployeeList * employee_list) {
    printf("\nDisplaying active_list:\n");
    for (int index = 0; index < employee_list->size_of_list; index++) {
        printf("Employee nr.%d\n", index+1);
        printf("First name: %s\n", employee_list->list[index].first_name);
        printf("Last name: %s\n", employee_list->list[index].last_name);
        printf("Age: %u\n", employee_list->list[index].age);
        printf("Role: %s\n", employee_list->list[index].role);
    }
}

unsigned int populate_employee_list (EmployeeList * employee_list) {
    for (int index = 0; index < employee_list->size_of_list; index++) {
        char first_name[200];
        char last_name[200];
        unsigned int age;
        char role[200];
        get_employee_data(first_name, last_name, &age, role);
        employee_list->list[index] = *create_employee(first_name, last_name, age, role);
    }
    return 0;
}

unsigned int append_new_employee (EmployeeList * employee_list) {
    char first_name[200];
    char last_name[200];
    unsigned int age;
    char role[200];
    get_employee_data(first_name, last_name, &age, role);
    Employee * employee = create_employee(first_name, last_name, age, role);
    if (employee == NULL) {
        printf("ERROR: add_new_employee failed to allocate temp employee memory\n");
        return 1;
    }
    employee_list->size_of_list++;
    Employee * tmp_list = (Employee *) realloc(employee_list->list, employee_list->size_of_list * sizeof(Employee));
    // In case realloc fails, the list will not be altered and the size will be decremented.
    if (tmp_list == NULL) {
        employee_list->size_of_list--;
        printf("ERROR: add_new_employee failed to reallocate employee_list memory\n");
        printf("NOTICE: List will not be altered\n");
        return 1;
    } else {
        employee_list->list = tmp_list;
        tmp_list = NULL;
        employee_list->list[employee_list->size_of_list-1] = *employee;
    }
}

unsigned int prepend_new_employee (EmployeeList * employee_list) {
    char first_name[200];
    char last_name[200];
    unsigned int age;
    char role[200];
    get_employee_data(first_name, last_name, &age, role);
    Employee * employee = create_employee(first_name, last_name, age, role);
    if (employee == NULL) {
        printf("ERROR: add_new_employee failed to allocate temp employee memory\n");
        return 1;
    }
    employee_list->size_of_list++;
    Employee * tmp_list = (Employee *) realloc(employee_list->list, employee_list->size_of_list * sizeof(Employee));
    // In case realloc fails, the list will not be altered and the size will be decremented.
    if (tmp_list == NULL) {
        employee_list->size_of_list--;
        printf("ERROR: add_new_employee failed to reallocate employee_list memory\n");
        printf("NOTICE: List will not be altered\n");
        return 1;
    } else {
        employee_list->list = tmp_list;
        tmp_list = NULL;
        /* // Not very efficient but does the job too
        for (int index = employee_list->size_of_list-1; index > 0; index--) {
            employee_list->list[index] = employee_list->list[index-1];
        }
        */
        memmove(employee_list->list + 1, employee_list->list, (employee_list->size_of_list - 1) * sizeof(Employee));
        employee_list->list[0] = *employee;
    }
}
unsigned int insert_at_pos_new_employee (EmployeeList * employee_list, int position) {
    if (position < 1 || position > employee_list->size_of_list) {
        printf("ERROR: insert_at_pos_new_employee failed to insert at position %d\n", position);
        printf("NOTICE: Position is out of bounds\n");
        return 1;
    } else {
        position--;
    }
    char first_name[200];
    char last_name[200];
    unsigned int age;
    char role[200];
    get_employee_data(first_name, last_name, &age, role);
    Employee * employee = create_employee(first_name, last_name, age, role);
    if (employee == NULL) {
        printf("ERROR: add_new_employee failed to allocate temp employee memory\n");
        return 1;
    }
    employee_list->size_of_list++;
    Employee * tmp_list = (Employee *) realloc(employee_list->list, employee_list->size_of_list * sizeof(Employee));
    // In case realloc fails, the list will not be altered and the size will be decremented.
    if (tmp_list == NULL) {
        employee_list->size_of_list--;
        printf("ERROR: add_new_employee failed to reallocate employee_list memory\n");
        printf("NOTICE: List will not be altered\n");
        return 1;
    } else {
        employee_list->list = tmp_list;
        tmp_list = NULL;
        memmove(employee_list->list + position + 1, employee_list->list + position, (employee_list->size_of_list - position - 1) * sizeof(Employee));
        employee_list->list[position] = *employee;
    }
}