#include "Laptop.h"

void get_laptop_data (char * brand, char * model, char * processor, char * ram, char * price) {
    printf("Enter the brand: ");
    fgets(brand, 50, stdin);
    brand[strlen(brand) - 1] = '\0';
    printf("Enter the model: ");
    fgets(model, 50, stdin);
    model[strlen(model) - 1] = '\0';
    printf("Enter the processor: ");
    fgets(processor, 50, stdin);
    processor[strlen(processor) - 1] = '\0';
    printf("Enter the RAM: ");
    fgets(ram, 50, stdin);
    ram[strlen(ram) - 1] = '\0';
    printf("Enter the price: ");
    fgets(price, 50, stdin);
    price[strlen(price) - 1] = '\0';
}

Laptop * create_laptop(char * brand, char * model, char * processor, char * ram, char * price) {
    Laptop * laptop = (Laptop *) malloc(sizeof(Laptop));
    laptop->brand = (char *) malloc(strlen(brand) + 1);
    laptop->model = (char *) malloc(strlen(model) + 1);
    laptop->processor = (char *) malloc(strlen(processor) + 1);
    laptop->ram = (char *) malloc(strlen(ram) + 1);
    laptop->price = (char *) malloc(strlen(price) + 1);
    strcpy(laptop->brand, brand);
    strcpy(laptop->model, model);
    strcpy(laptop->processor, processor);
    strcpy(laptop->ram, ram);
    strcpy(laptop->price, price);
    return laptop;
}

void print_laptop(Laptop *laptop) {
    printf("Brand: %s\n", laptop->brand);
    printf("Model: %s\n", laptop->model);
    printf("Processor: %s\n", laptop->processor);
    printf("RAM: %s\n", laptop->ram);
    printf("Price: %s\n", laptop->price);
    printf("\n");
}

void free_laptop(Laptop * laptop) {
    free(laptop->brand);
    free(laptop->model);
    free(laptop->processor);
    free(laptop->ram);
    free(laptop->price);
    free(laptop);
}