#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "backpack.h"


struct backpack* create_backpack(const int capacity){
    if(capacity <= 0) return NULL;

    struct backpack* new_backpack = calloc(1, sizeof(struct backpack));

    new_backpack->capacity = capacity;

    return new_backpack;
}


struct backpack* destroy_backpack(struct backpack* backpack){
    if(backpack == NULL) return NULL;

    if(backpack->items != NULL) destroy_containers(backpack->items);

    free(backpack);
    
    return NULL;
}


bool add_item_to_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL)       return false;
    if(backpack->size +1 > backpack->capacity) return false;
    if(!(item->properties & MOVABLE))          return false;

    if(backpack->items == NULL){
        backpack->items = create_container(NULL, ITEM, item);
        backpack->size++;
        return true;
    }

    else{
        create_container(backpack->items, ITEM, item);
        backpack->size++;
        return true;
    }
}


struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
    if(backpack == NULL || name == NULL) return NULL;
    if(strlen(name) == 0) return NULL;

    return get_from_container_by_name(backpack->items, name);
}


void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL) return;

    backpack->items = remove_container(backpack->items, item);
    backpack->size--;
    
    return;
}