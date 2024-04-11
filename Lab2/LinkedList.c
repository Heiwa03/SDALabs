#include "LinkedList.h"

LinkedList * create_linked_list() {
    LinkedList * list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}
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

Node * create_node(Laptop * laptop) {
    Node * node = (Node *) malloc(sizeof(Node));
    node->laptop = laptop;
    node->next = NULL;
    return node;
}

void push_front(LinkedList * list, Laptop * laptop) {
    Node * node = create_node(laptop);
    node->next = list->head;
    list->head = node;
    list->size++;
}

void push_back(LinkedList * list, Laptop * laptop) {
    Node * node = create_node(laptop);
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node * current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
    list->size++;
}

void insert(LinkedList * list, Laptop * laptop, int index) {
    if (index < 0 || index > list->size) {
        printf("Index out of bounds\n");
        return;
    }
    if (index == 0) {
        push_front(list, laptop);
    } else if (index == list->size) {
        push_back(list, laptop);
    } else {
        Node * node = create_node(laptop);
        Node * current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
        list->size++;
    }
}

void pop_front(LinkedList * list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node * temp = list->head;
    list->head = list->head->next;
    free_node(temp);
    list->size--;
}

void pop_back(LinkedList * list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (list->head->next == NULL) {
        free_node(list->head);
        list->head = NULL;
    } else {
        Node * current = list->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free_node(current->next);
        current->next = NULL;
    }
    list->size--;
}

void pop_index(LinkedList * list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of bounds\n");
        return;
    }
    if (index == 0) {
        pop_front(list);
    } else if (index == list->size - 1) {
        pop_back(list);
    } else {
        Node * current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node * temp = current->next;
        current->next = current->next->next;
        free_node(temp);
        list->size--;
    }
}

void print_list(LinkedList * list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node * current = list->head;
    while (current != NULL) {
        printf("Brand: %s\n", current->laptop->brand);
        printf("Model: %s\n", current->laptop->model);
        printf("Processor: %s\n", current->laptop->processor);
        printf("RAM: %s\n", current->laptop->ram);
        printf("Price: %s\n", current->laptop->price);
        printf("\n");
        current = current->next;
    }
}

void free_list(LinkedList * list) {
    while (list->head != NULL) {
        pop_front(list);
    }
    free(list);
}

void free_node(Node * node) {
    free_laptop(node->laptop);
    free(node);
}

void free_laptop(Laptop * laptop) {
    free(laptop->brand);
    free(laptop->model);
    free(laptop->processor);
    free(laptop->ram);
    free(laptop->price);
    free(laptop);
}

void invert_list(LinkedList * list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node * prev = NULL;
    Node * current = list->head;
    Node * next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

int search_list(LinkedList* list, char* field, char* value) {
    Node* current = list->head;
    int index = 0;

    while (current != NULL) {
        if (strcmp(field, "brand") == 0 && strcmp(current->laptop->brand, value) == 0) {
            return index;
        } else if (strcmp(field, "model") == 0 && strcmp(current->laptop->model, value) == 0) {
            return index;
        } else if (strcmp(field, "processor") == 0 && strcmp(current->laptop->processor, value) == 0) {
            return index;
        } else if (strcmp(field, "ram") == 0 && strcmp(current->laptop->ram, value) == 0) {
            return index;
        } else if (strcmp(field, "price") == 0 && strcmp(current->laptop->price, value) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1; // return -1 if no matching node is found
}

void sort_list(LinkedList* list, char* field) {
    if (list->size < 2) {
        return; // list is already sorted if it has less than 2 elements
    }

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) {
            int comparison;
            if (!(strcmp(field, "brand"))) {
                comparison = strcmp(ptr1->laptop->brand, ptr1->next->laptop->brand);
            } else if (!(strcmp(field, "model"))) {
                comparison = strcmp(ptr1->laptop->model, ptr1->next->laptop->model);
            } else if (!(strcmp(field, "processor"))) {
                comparison = strcmp(ptr1->laptop->processor, ptr1->next->laptop->processor);
            } else if (!(strcmp(field, "ram"))) {
                comparison = strcmp(ptr1->laptop->ram, ptr1->next->laptop->ram);
            } else if (!(strcmp(field, "price"))) {
                comparison = strcmp(ptr1->laptop->price, ptr1->next->laptop->price);
            } else {
                return; // invalid field
            }

            if (comparison > 0) {
                Laptop* temp = ptr1->laptop;
                ptr1->laptop = ptr1->next->laptop;
                ptr1->next->laptop = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

int _check_not_out_of_bounds_index (LinkedList *list, int index) {
    if (index > list->size || index < 0) {
        return 0;
    }
    return 1;
}
