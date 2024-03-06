#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"

int main () {
    EmployeeList * current_employee_list = create_employee_list(2);
    if (current_employee_list == NULL) {
        printf("ERROR: main failed to create current_employee_list\n");
        return 1;
    }
    populate_employee_list(current_employee_list);
    print_employee_list(current_employee_list);
    append_new_employee(current_employee_list);
    print_employee_list(current_employee_list);
    prepend_new_employee(current_employee_list);
    print_employee_list(current_employee_list);
    free_employee_list(current_employee_list);


    return 0;
}