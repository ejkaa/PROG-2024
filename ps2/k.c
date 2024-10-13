#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "k.h"
#include "ui.h"


int pov(const char a){
    int b = 2;
    for(int i = 0, k = a-64; i < k; i++)
        b *= 2;

    return b;
}

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(game.board[i][j] == 'K'){
                return true;
            }
        }
    }
    return false;
}


bool is_move_possible(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == ' ')
                return true;
        }
    }

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE-1; j++){
            if(game.board[i][j] == game.board[i][j+1])
                return true;
        }
    }

    for(int i = 0; i < SIZE-1; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == game.board[i+1][j])
                return true;
        }
    }

    return false;
}

bool update(struct game *game, int dy, int dx){
    if(dy < -1 || dy > 1 || dx < -1 || dx > 1){
        return false;
    }
    
    if((dy != 0 && dx != 0) || (dy == 0 && dx == 0)){
        return false;
    }

    switch(dy){
        case 1:
            for (int j = 0; j < SIZE; j++){ //moves to right
                int move = 0;
                for (int i = SIZE-1; i >= 0;){

                    if(game->board[i][j] == ' '){
                        move++;
                        i--;
                        continue;
                    }

                    if(game->board[i][j] != ' ' && move != 0){

                        game->board[i+move][j] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        i = SIZE-1;
                        continue;
                    }
                    i--;
                }

                for (int i = SIZE-1; i >= 1; i-=1){
                    if(game->board[i][j] == game->board[i-1][j] && game->board[i][j] != ' '){
                        game->score += pov(game->board[i][j]);
                        game->board[i][j]++;
                        game->board[i-1][j] = ' ';
                    }
                }
                
                move = 0;
                for (int i = SIZE-1; i >= 0;){

                    if(game->board[i][j] == ' '){
                        move++;
                        i--;
                        continue;
                    }

                    if(game->board[i][j] != ' ' && move != 0){

                        game->board[i+move][j] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        i = SIZE-1;
                        continue;
                    }
                    i--;
                }
            }



            return true;

        case -1:
            for (int j = 0; j < SIZE; j++){ //moves to right
                int move = 0;
                for (int i = 0; i < SIZE;){

                    if(game->board[i][j] == ' '){
                        move++;
                        i++;
                        continue;
                    }

                    if(game->board[i][j] != ' ' && move != 0){

                        game->board[i-move][j] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        i = 0;
                        continue;
                    }
                    i++;
                }

                for (int i = 0; i < SIZE-1; i+=1){
                    if(game->board[i][j] == game->board[i+1][j] && game->board[i][j] != ' '){
                        game->score += pov(game->board[i][j]);
                        game->board[i][j]++;
                        game->board[i+1][j] = ' ';
                    }
                }
                
                move = 0;
                for (int i = 0; i < SIZE;){

                    if(game->board[i][j] == ' '){
                        move++;
                        i++;
                        continue;
                    }

                    if(game->board[i][j] != ' ' && move != 0){

                        game->board[i-move][j] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        i = 0;
                        continue;
                    }
                    i++;
                }
            }
            return true;
    }


    switch(dx){
        case 1:
            for (int i = 0; i < SIZE; i++){ //moves to right
                int move = 0;
                for (int j = SIZE-1; j >= 0;){

                    if(game->board[i][j] == ' '){
                        move++;
                        j--;
                        continue;
                    }

                    if(game->board[i][j] != ' ' && move != 0){

                        game->board[i][j+move] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        j = SIZE-1;
                        continue;
                    }
                    j--;
                }

                for (int j = SIZE-1; j >= 1; j-=1){
                    if(game->board[i][j] == game->board[i][j-1] && game->board[i][j] != ' '){
                        game->score += pov(game->board[i][j]);
                        game->board[i][j]++;
                        game->board[i][j-1] = ' ';
                    }
                }
                
                move = 0;
                for (int j = SIZE-1; j >= 0;){
                    if(game->board[i][j] == ' '){
                        move++;
                        j--;
                        continue;
                    }
                    if(game->board[i][j] != ' ' && move != 0){

                        game->board[i][j+move] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        j = SIZE-1;
                        continue;
                    }
                    j--;
                }
            }
            return true;


        case -1:
            for (int i = 0; i < SIZE; i++){ //moves to right
                int move = 0;
                for (int j = 0; j < SIZE;){

                    if(game->board[i][j] == ' '){
                        move++;
                        j++;
                        continue;
                    }

                    if(game->board[i][j] != ' ' && move != 0){

                        game->board[i][j-move] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        j = 0;
                        continue;
                    }
                    j++;
                }

                for (int j = 0; j < SIZE-1; j+=1){
                    if(game->board[i][j] == game->board[i][j+1] && game->board[i][j] != ' '){
                        game->score += pov(game->board[i][j]);
                        game->board[i][j]++;
                        game->board[i][j+1] = ' ';
                    }
                }

                move = 0;
                for (int j = 0; j < SIZE;){

                    if(game->board[i][j] == ' '){
                        move++;
                        j++;
                        continue;
                    }

                    if(game->board[i][j] != ' ' && move != 0){
                        game->board[i][j-move] = game->board[i][j];
                        game->board[i][j] = ' ';

                        move = 0;
                        j = 0;
                        continue;
                    }
                    j++;
                }
                
            }
    }
    return true;
}