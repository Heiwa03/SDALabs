#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#define QUIT 7

#include "LinkedList.h"
#include "stdio.h"
#include "stdlib.h"

unsigned int open_option_menu(LinkedList *list);
void print_menu_options();
void print_search_menu_options();
void print_sort_menu_options();
void print_search_menu_options();
unsigned int open_sort_option_menu(LinkedList *list);
unsigned int open_search_option_menu(LinkedList *list);

#endif // OPTIONMENU_H