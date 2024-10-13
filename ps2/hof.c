#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hof.h"


int cmp_score(const void* p1, const void* p2){
	int player1 = ((struct player*)p1)->score;
	int player2 = ((struct player*)p2)->score;

	return -(player1 - player2);
}


int load(struct player list[]){
	FILE* fr = fopen(HOF_FILE, "r");
	if(fr == NULL){
		return -1;
	}



	char flag;

	fseek(fr, 0, SEEK_SET);
	size_t size = 0;
	while( (flag = (char)(fgetc(fr)) ) != EOF){
		if(flag == '\n')
			size++;
	}
	size = (size > 10) ? 10 : size;

	fseek(fr, 0, SEEK_SET);
	for (int i = 0; i < size; i++){
		fscanf(fr, "%s %d", list[i].name, &list[i].score);
	}
	fclose(fr);

	qsort(list, size, sizeof list[0], cmp_score);
	
	return (int)size;
}

bool save(const struct player list[], const int size){
	if(list == NULL)
		return false;

	FILE* fw = fopen(HOF_FILE, "w+");

	for (int i = 0; i < size; ++i){
		fprintf(fw, "%s %d\n", list[i].name, list[i].score);
	}
	fclose(fw);

	return true;
}


int cmp_score(const void* p1, const void* p2){
	int player1 = ((struct player*)p1)->score;
	int player2 = ((struct player*)p2)->score;

	return -(player1 - player2);
}


bool add_player(struct player list[], int* size, const struct player player){
	int size1 = *size+1;


	struct player list1[size1];
	list1[0] = player;
	for (int i = 1; i < size1; i++){
		list1[i] = list[i-1];
	}

	
	qsort(list1, (size_t)size1, sizeof list1[0], cmp_score);

	if(size1 > 10)
		size1 = 10;

	for (int i = 0; i < size1; i++){
		list[i] = list1[i];
	}

	for (int i = 0; i < size1; i++){
		if(i == 10)
			break;
		if( (!strcmp(player.name, list[i].name)) && (player.score == list[i].score) ){
			*size = size1;
			return true;
		}
	}

	return false;
}