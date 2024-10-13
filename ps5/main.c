#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "container.h"
#include "room.h"
#include "item.h"
#include "command.h"
#include "game.h"
#include "parser.h"
#include "backpack.h"
#include "world.h"

//
int main(){
    struct item* item1 = create_item("chun", "gus", 1);
    struct container* cont_ITEM = create_container(NULL, ITEM, item1);

    struct command* command1 = create_command("VERZIA", "Zobraz verziu hry.", NULL, 0);
    struct container* cont_COMMAND = create_container(NULL, COMMAND, command1);
    destroy_containers(cont_COMMAND);


    struct room* room1 = create_room("small", "bebra");
    struct room* room2 = create_room("big", "nebebra");
    
    get_item_from_room(NULL, "chun");
    add_item_to_room(NULL, NULL);
    delete_item_from_room(NULL, NULL);


    create_backpack(0);
    get_item_from_backpack(NULL, NULL);
    add_item_to_backpack(NULL, NULL);
    delete_item_from_backpack(NULL, NULL);
    destroy_backpack(NULL);


    struct game* game = create_game();
    destroy_game(game);
    execute_command(NULL, NULL);




    struct parser* parser = create_parser();
    parse_input(NULL, NULL);    
    destroy_parser(parser);



    struct container* world = create_world();
    destroy_world(world);
    add_room_to_world(NULL, NULL);
    get_room(NULL, NULL);



    struct container* cont1 = create_container(NULL, ROOM, room1);
    set_exits_from_room(room1, room2, NULL, NULL, NULL);
    



    destroy_room(room2);

    destroy_containers(cont1);

    destroy_containers(cont_ITEM);





    // struct command* command1 = create_command("VEZMI", "", NULL, 0);
    // if(command1 == NULL) printf("NULL\n");
    // destroy_command(command1);

    // struct container* first1 = create_container(NULL, TEXT, "mama"); // creates list of containers with texts
    // printf("text: %s\n", first1->text);
    // struct container* entry = create_container(first1, TEXT, "JUH");
    // printf("text2: %s\n", entry->text);

    // char* result_text = get_from_container_by_name(first1, "JUH");
    // if(result_text == NULL) printf("result_text == NULL\n");
    // else printf("result text: %s\n", result_text);
    // destroy_containers(first1);





    // struct item* entry1 = create_item("TRUHLICA", "Do tejto bedne sa daju vlozit veci.", USABLE | EXAMINABLE);
    // struct container* first = create_container(NULL, ITEM, entry1);
    // struct item* result_item = get_from_container_by_name(first, "TRUHLICA");
    // printf("%s\n", result_item->name);
    // destroy_containers(first);




    // struct item* entry1 = create_item("TRUHLICA", "Do tejto bedne sa daju vlozit veci.", USABLE | EXAMINABLE);
    // struct room* room2 = create_room("big", "nebebra");
    
    // add_item_to_room(room2, entry1);
    // get_item_from_room(NULL, "chun");
    // delete_item_from_room(room2, entry1);

    // destroy_room(room2);





    // char* text = "NAHRAJ"; // returns allocated string
    // struct container* first = create_container(NULL, TEXT, text);
    // if(remove_container(first, text) == NULL) printf("cont NULL\n");




    // struct room* room = create_room("West X Street", "West X Street is the rich section of town. So rich, they paved the streets with gold. This probably was not a good idea. The thief guild opened up the next day.");
    // struct room* north = create_room("Wizard Tower", "Zanny magical antics are afoot in the world-famous Wizard Tower. Cauldrons bubble, rats talk, and books float midair in this center of magical discovery.");
    // struct room* south = create_room("West X Street", "West X Street is the rich section of town. So rich, they paved the streets with gold. This probably was not a good idea. The thief guild opened up the next day.");
    // struct room* east = create_room("", "");
    // struct room* west = create_room("Town Square", "The town square is a large open space with a fountain in the center. Streets lead in all directions.");
    // set_exits_from_room(room, west, east, south, north);
    // set_exits_from_room(room, north, south, east, west);

    return 0;
}
