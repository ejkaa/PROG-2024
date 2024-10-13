#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "room.h"


struct room* create_room(char *name, char *description){
    if(name == NULL || description == NULL)  return NULL;
    if(strlen(name) == 0 || strlen(description) == 0) return NULL;


    struct room* new = calloc(1, sizeof(struct room));

    new->name = calloc(strlen(name)+1, 1);
    strcpy(new->name, name);

    new->description = calloc(strlen(description)+1, 1);
    strcpy(new->description, description);

    return new; 
}


void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
    if(room == NULL) return;

    /*if(north != NULL)*/ room->north = north;
    /*if(south != NULL)*/ room->south = south;
    /*if(east != NULL)*/  room->east = east;
    /*if(west != NULL)*/  room->west = west;
}


// void show_room(const struct room* room){
//     if(room == NULL) return;

//     printf("%s\n\n", room->name);
//     printf("%s\n\n", room->description);

//     printf("Mozne vychody z miesnosti:\n");

//     if(room->north != NULL) printf("\tnorth\n");
//     if(room->south != NULL) printf("\tsouth\n");
//     if(room->east  != NULL) printf("\teast\n");
//     if(room->west  != NULL) printf("\twest\n");

//     // if(room->items != NULL){
//     //     for (int i = 0, number_of_items = sizeof(room->items) / sizeof(struct item); i < number_of_items; i++){
//     //         printf("\t%s\n", room->items[i].item.name);
//     //     }
//     // }
// }


struct room* destroy_room(struct room* room){
    if(room == NULL) return NULL;
    
    if(room->description != NULL) free(room->description);
    if(room->name != NULL)        free(room->name);
    if(room->items != NULL)       destroy_containers(room->items);

    free(room);

    return NULL;
}


void add_item_to_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL) return;
    
    if(room->items == NULL) {room->items = create_container(NULL, ITEM, item); return;}

    create_container(room->items, ITEM, item);

    // return;
}


void delete_item_from_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL) return;

    room->items = remove_container(room->items, item);
    
    // return;
}

struct item* get_item_from_room(const struct room* room, const char* name){
    if(room == NULL || name == NULL) return NULL;

    return get_from_container_by_name(room->items, name);
}
