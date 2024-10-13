#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "item.h"

struct item* create_item(char* name, char* description, unsigned int properties){
    if(name == NULL || description == NULL) return NULL;
    if(strlen(name) == 0 || strlen(description) == 0) return NULL;


    struct item* new = calloc(1, sizeof(struct item));

    new->name = calloc(strlen(name)+1, 1);
    strcpy(new->name, name);
    
    new->description = calloc(strlen(description)+1, 1);
    strcpy(new->description, description);
    
    new->properties = properties;

    return new;
}



struct item* destroy_item(struct item* item){
    if(item == NULL) return NULL;

    if(item->name != NULL)        free(item->name);
    if(item->description != NULL) free(item->description);
    free(item);

    return NULL;
}