#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// struct definitions
typedef struct Employee {
    char * first_name;
    char * last_name;
    unsigned int age;
    char * role;
} Employee;

typedef struct EmployeeList {
    Employee * list;
    int size_of_list;
} EmployeeList;

// helper compare function definitions
typedef bool (*SearchCompareFunc)(Employee*, const char*);
typedef int (*SortCompareFunc)(const void*, const void*);

// Employee function prototypes
void get_employee_data (char * first_name, char * last_name, unsigned int * age, char * role);
Employee* create_employee (char * first_name, char * last_name, unsigned int age, char * role);
void free_employee (Employee * employee);
void print_employee (Employee * employee);

// EmployeeList function prototypes
EmployeeList* create_employee_list (int size_of_list);
void free_employee_list (EmployeeList * employee_list);
void print_employee_list (EmployeeList * employee_list);
unsigned int populate_employee_list (EmployeeList * employee_list);

// EmployeeList manipulation function prototypes
unsigned int append_new_employee (EmployeeList * employee_list); 
unsigned int prepend_new_employee (EmployeeList * employee_list); 
unsigned int insert_at_pos_new_employee (EmployeeList * employee_list, int position);
unsigned int delete_at_pos_employee (EmployeeList * employee_list, int position);

// search and sort function prototypes
int search_employee(EmployeeList* employee_list, SearchCompareFunc compare, const char* value);
void sort_employee_list(EmployeeList* employee_list, SortCompareFunc compare);

// helper functions
bool _search_compare_role(Employee* employee, const char* role);
bool _search_compare_first_name(Employee* employee, const char* first_name);
bool _search_compare_last_name(Employee* employee, const char* last_name);

int _sort_compare_role(const void* a, const void* b);
int _sort_compare_first_name(const void* a, const void* b);
int _sort_compare_last_name(const void* a, const void* b);


#endif // EMPLOYEE_H