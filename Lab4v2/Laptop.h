#ifndef LAPTOP_H
#define LAPTOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTree.h"

typedef struct Laptop {
    char * brand;
    char * model;
    char * processor;
    char * ram;
    char * price;
} Laptop;

void get_laptop_data(char * brand, char * model, char * processor, char * ram, char * price);
Laptop * create_laptop(char * brand, char * model, char * processor, char * ram, char * price);
void print_laptop(Laptop *laptop);
void free_laptop(Laptop * laptop);

#endif // lAPTOP_H