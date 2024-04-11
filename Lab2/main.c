#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "OptionMenu.h"

int main () {
    LinkedList * list = create_linked_list();
    if (list == NULL) {
        printf("Error creating the list\n");
        return 1;
    }
    if (open_option_menu(list) == QUIT) {
        printf("Exiting...\n");
        return 0;
    }
    return 1;
}