#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "BinaryTree.h"

#define QUIT 10

void print_menu();
int get_user_input();
void open_menu(BinaryTree *tree);

#endif // MENU_H