#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "BinaryTree.h"
#include "Menu.h"

int main () {
    BinaryTree *tree = create_binary_tree();
    
    open_menu(tree);

    free_tree(tree);
}