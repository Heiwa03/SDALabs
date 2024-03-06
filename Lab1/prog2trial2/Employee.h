#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

void get_employee_data (char * first_name, char * last_name, unsigned int * age, char * role);
Employee* create_employee (char * first_name, char * last_name, unsigned int age, char * role);
void free_employee (Employee * employee);
void print_employee (Employee * employee);

EmployeeList* create_employee_list (int size_of_list);
void free_employee_list (EmployeeList * employee_list);
void print_employee_list (EmployeeList * employee_list);
unsigned int populate_employee_list (EmployeeList * employee_list);

unsigned int append_new_employee (EmployeeList * employee_list); 
unsigned int prepend_new_employee (EmployeeList * employee_list); 
unsigned int insert_at_pos_new_employee (EmployeeList * employee_list, int position);
unsigned int delete_at_pos_employee (EmployeeList * employee_list, int position);

int search_employee(EmployeeList* employee_list, SearchCompareFunc compare, const char* value);
void sort_employee_list(EmployeeList* employee_list, SortCompareFunc compare);

#endif // EMPLOYEE_H