#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "container.h"


struct container* create_container(struct container* first, enum container_type type, void* entry){
    if(entry == NULL)  return NULL;
    if(first != NULL && first->type != type) return NULL;

    struct container* new = calloc(1, sizeof(struct container));
    new->type = type;
    new->next = NULL;

    if(type == ROOM)         new->room = entry;
    else if(type == ITEM)    new->item = entry;
    else if(type == COMMAND) new->command = entry;
    else if(type == TEXT)    new->text = entry;

    if(first == NULL) first = new;
    else {
        struct container *temporary = first;
        while (temporary->next != NULL) {
            // printf("1\n");
            temporary = temporary->next;
        }
        temporary->next = new;
    }
    
    return new;
}


struct container* destroy_containers(struct container* first){
    struct container* temporary = first;

    // int i = 0;
    while(temporary != NULL){
        struct container* erase = temporary;
        temporary = temporary->next;

        if(erase->type == ROOM)         destroy_room(erase->room);
        else if(erase->type == ITEM)    destroy_item(erase->item);
        else if(erase->type == COMMAND) destroy_command(erase->command);
        else if(erase->type == TEXT)    free(erase->text);
        
        free(erase);
        // printf("i :%d\n", i++);

    }

    return NULL;
}


void* get_from_container_by_name(struct container *first, const char *name){
    if(first == NULL || name == NULL) return NULL;
    if(strlen(name) == 0) return NULL;
    
    struct container* temporary = first;

    if(first->type == ROOM){
        while(temporary != NULL){
            if(!strcmp(temporary->room->name, name)) return temporary->room;
            temporary = temporary->next;
        }
    }

    else if(first->type == ITEM){
        while(temporary != NULL){
            if(!strcmp(temporary->item->name, name)) return temporary->item;
            temporary = temporary->next;
        }
    }

    else if(first->type == COMMAND){
        while(temporary != NULL){
            if(!strcmp(temporary->command->name, name)) return temporary->command;
            temporary = temporary->next;
        }
    }

    else if(first->type == TEXT){
        while(temporary != NULL){
            if(!strcmp(temporary->text, name)) return temporary->text;
            temporary = temporary->next;
        }
    }

    return NULL;
}


void free_first(struct container *first, struct container* to_remove){
    to_remove = first;
    first = to_remove->next;
    free(to_remove);
    return;
}
void free_after_first(struct container* before_remove, struct container* to_remove){
    to_remove = before_remove->next;
    before_remove->next = to_remove->next;
    free(to_remove);
    return;
}
struct container* remove_container(struct container *first, void *entry){
    if(first == NULL) return NULL;
    if(entry == NULL) return first;

    struct container* before_remove = first;
    struct container* to_remove = first;
    

///     { for case if "entry" is in 1st container
    if(first->next == NULL) {
        if (first->type == ROOM) {

            if (first->room == entry) {

                free_first(first, to_remove);
                return NULL;
            }
        }
        
        else if (first->type == ITEM) {

            if (first->item == entry) {

                free_first(first, to_remove);
                return NULL;
            }
        }
        
        else if (first->type == COMMAND) {

            if (first->command == entry) {

                free_first(first, to_remove);
                return NULL;
            }
        }
        
        else if (first->type == TEXT) {

            if (first->text == entry) {

                free_first(first, to_remove);
                return NULL;
            }
        }
    }
///     }
    

    while(before_remove->next != NULL){
        if(before_remove->next->type == ROOM){

            if(before_remove->next->room == entry){

                free_after_first(before_remove, to_remove);
                return first;
            }
        }

        else if(before_remove->next->type == ITEM){

            if(before_remove->next->room == entry){

                free_after_first(before_remove, to_remove);
                return first;
            }
        }

        else if(before_remove->next->type == COMMAND){

            if(before_remove->next->room == entry){

                free_after_first(before_remove, to_remove);
                return first;
            }
        }

        else if(before_remove->next->type == TEXT){

            if(before_remove->next->text == entry){

                free_after_first(before_remove, to_remove);
                return first;
            }
        }
        
        
        // before_remove = to_remove;
        // to_remove = to_remove->next;
        
        // if(to_remove == NULL) return NULL;
    }

    // before_remove->next = to_remove->next;
    // free(to_remove);
    
    return first;
}