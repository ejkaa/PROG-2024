#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "command.h"


struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    if(name == NULL || description == NULL) return NULL;
    // printf("%ld %ld\n", strlen(name), strlen(description));
    if(strlen(name) == 0 || strlen(description) == 0) return NULL;

    struct command* new = calloc(1, sizeof(struct command));

    new->name = calloc(strlen(name)+1, 1);
    strcpy(new->name, name);

    new->description = calloc(strlen(description)+1, 1);
    strcpy(new->description, description);


    if(pattern != NULL) regcomp(&new->preg, pattern, 0);

    new->nmatch = nmatch;

    return new;
}


struct command* destroy_command(struct command* command){
    if(command == NULL) return NULL;
    
    if(command->name != NULL)        free(command->name);
    if(command->description != NULL) free(command->description);
    if(command->groups != NULL)      free(command->groups);
    regfree(&command->preg);
    
    free(command);
    return NULL;
}