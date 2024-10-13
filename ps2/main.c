#include <stdio.h>
#include <stdlib.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main(int argc, char const *argv[]){
    struct game game = {
/*    .board = {
        {'B', ' ', 'B', 'A'},
        {' ', 'F', 'F', 'F'},
        {'C', ' ', ' ', 'C'},
        {'A', 'A', 'A', 'A'}
    },
*/
/*    .board = {
        {'B', ' ', 'B', 'A'},
        {' ', 'A', 'A', 'C'},
        {'C', ' ', ' ', 'C'},
        {'C', 'A', 'A', 'A'}
    },
    .score = 0
    };
*/
      .board = {
        {'A', ' ', ' ', ' '},
        {'B', ' ', ' ', 'B'},
        {'C', 'C', 'C', ' '},
        {'D', 'D', 'D', 'D'}
    },
    .score = 0
    };

    struct player player = {.name="John", .score=261};
    // int size=5;
    // struct player list[10] = {
    //     {.score= 1769, .name="Sue"},
    //     {.score= 1618, .name="Jack"},
    //     {.score= 1140, .name="Bill"},
    //     {.score=  870, .name="Bill"},
    //     {.score=  426, .name="Bill"}
    // };
    is_move_possible(game);
    // printf("is move possible: %d\n", is_move_possible(game));
    update(&game, 0, 1);
    render(game);
    add_random_tile(&game);
    is_game_won(game);
    struct player list[10];
    int size = load(list);
    add_player(list, &size, player);
    // printf("%d\n\n", add_player(list, &size, player));

    // for (int i = 0; i < size; ++i){
    //     printf("%s %d\n", list[i].name, list[i].score);
    // }

    save(list, size);
    
    // save(hof, size);
    // print(list, size);
    return 0;
}