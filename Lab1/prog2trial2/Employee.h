#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Employee* create_employee (char * first_name, char * last_name, unsigned int age, char * role);
EmployeeList* create_employee_list (int size_of_list);
void free_employee (Employee * employee);
void free_employee_list (EmployeeList * employee_list);
void print_employee (Employee * employee);
void print_employee_list (EmployeeList * employee_list);

#endif // EMPLOYEE_H