#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "game.h"
#include "world.h"


struct game* create_game(){
    struct game* new = calloc(1, sizeof(struct game));

    new->parser = create_parser();
    
    new->backpack = create_backpack(5);
    
    new->state = PLAYING;
    
    new->world = create_world();
    new->current_room = new->world->room;
    
    return new;
}


struct game* destroy_game(struct game* game){
    if(game == NULL) return NULL;

    destroy_parser(game->parser);
    destroy_world(game->world);
    destroy_backpack(game->backpack);

    free(game);

    return NULL;
}


void execute_command(struct game* game, struct command* command){
    if(game == NULL || command == NULL) return;

    if(!strcmp(command->name, "KONIEC"))    game->state = GAMEOVER;
    if(!strcmp(command->name, "RESTART"))   game->state = RESTART;


    if(!strcmp(command->name, "SEVER"))     game->current_room = game->current_room->north;
    if(!strcmp(command->name, "JUH"))       game->current_room = game->current_room->south;
    if(!strcmp(command->name, "VYCHOD"))    game->current_room = game->current_room->east;
    if(!strcmp(command->name, "ZAPAD"))     game->current_room = game->current_room->west;
}