#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "OptionMenu.h"

int main () {
    printf("Welcome to the Employee Management System\n");
    printf("The List requires an initial size to be created\n");
    printf("Please enter the size of the list: ");
    int size_of_list;
    scanf("%d", &size_of_list);
    EmployeeList * employee_list = create_employee_list(size_of_list);
    printf("The list has been created\n");
    printf("The list has been initialized with %d employees\n", populate_employee_list(employee_list));
    option_menu(&employee_list);
    
    free_employee_list(employee_list);
    return 0;
}