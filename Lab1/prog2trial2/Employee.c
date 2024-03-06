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
    EmployeeList * employee_list = (EmployeeList *) malloc(sizeof(EmployeeList));
    employee_list->list = (Employee *) malloc(size_of_list * sizeof(Employee));
    employee_list->size_of_list = size_of_list;
    return employee_list;
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

void add_new_employee (EmployeeList * employee_list) {
    char first_name[200];
    char last_name[200];
    unsigned int age;
    char role[200];
    get_employee_data(first_name, last_name, &age, role);
    Employee * employee = create_employee(first_name, last_name, age, role);
    employee_list->size_of_list++;
    employee_list->list = (Employee *) realloc(employee_list->list, employee_list->size_of_list * sizeof(Employee));
    employee_list->list[employee_list->size_of_list-1] = *employee;
}