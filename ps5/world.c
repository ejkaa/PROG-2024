#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "world.h"


struct container* create_world(){

    struct room *one        = create_room("First room",     "idk let it be bebra");
    struct room *two        = create_room("Second room",    "idk let it be bebra");
    struct room *three      = create_room("Third room",     "idk let it be bebra");
    struct room *four       = create_room("Fourth room",    "idk let it be bebra");
    struct room *five       = create_room("Fifth room",     "idk let it be bebra");
    struct room *six        = create_room("Sixth room",     "idk let it be bebra");
    struct room *seven      = create_room("Seventh room",   "idk let it be bebra");
    struct room *eight      = create_room("Eighth room",    "idk let it be bebra");
    struct room *nine       = create_room("Ninth room",     "idk let it be bebra");
    struct room *ten        = create_room("Tenth room",     "idk let it be bebra");
    struct room *eleven     = create_room("Eleventh room",  "idk let it be bebra");
    struct room *twelve     = create_room("Twelfth room",   "idk let it be bebra");
    struct room *thirteen   = create_room("Thirteenth room","idk let it be bebra");
    struct room *fourteen   = create_room("Fourteenth room","idk let it be bebra");
    struct room *fifteen    = create_room("Fifteenth room", "idk let it be bebra");



    struct item *item_one   = create_item("just item", "idk let it be baraberebere", MOVABLE | USABLE | EXAMINABLE | OPENABLE);
    struct item *item_two   = create_item("just item", "idk let it be baraberebere", MOVABLE | USABLE | EXAMINABLE | OPENABLE);
    struct item *item_three = create_item("just item", "idk let it be baraberebere", MOVABLE | USABLE | EXAMINABLE | OPENABLE);
    struct item *item_four  = create_item("just item", "idk let it be baraberebere", MOVABLE | USABLE | EXAMINABLE | OPENABLE);
    struct item *item_five  = create_item("just item", "idk let it be baraberebere", MOVABLE | USABLE | EXAMINABLE | OPENABLE);



    struct container *all_rooms;
    all_rooms = create_container(NULL, ROOM, one);
    create_container(all_rooms, ROOM, two);
    create_container(all_rooms, ROOM, three);
    create_container(all_rooms, ROOM, four);
    create_container(all_rooms, ROOM, five);
    create_container(all_rooms, ROOM, six);
    create_container(all_rooms, ROOM, seven);
    create_container(all_rooms, ROOM, eight);
    create_container(all_rooms, ROOM, nine);
    create_container(all_rooms, ROOM, ten);
    create_container(all_rooms, ROOM, eleven);
    create_container(all_rooms, ROOM, twelve);
    create_container(all_rooms, ROOM, thirteen);
    create_container(all_rooms, ROOM, fourteen);
    create_container(all_rooms, ROOM, fifteen);



    add_item_to_room(one,   item_one);
    add_item_to_room(two,   item_two);
    add_item_to_room(three, item_three);
    add_item_to_room(four,  item_four);
    add_item_to_room(five,  item_five);


    return all_rooms;
}


struct container* destroy_world(struct container* world){
    if(world == NULL) return NULL;

    destroy_containers(world);

    return NULL;
}


struct container* add_room_to_world(struct container* world, struct room* room){
    if(room == NULL) return NULL;

    ///if room is already in world
    if(get_from_container_by_name(world, room->name) != NULL) return NULL;

    return create_container(world, ROOM, room);
}


struct room* get_room(struct container* world, char* name){
    if(world == NULL || name == NULL) return NULL;

    return get_from_container_by_name(world, name);
}