#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//text

char** make_key(const char* keyword1) {
    char* keyword = calloc(strlen(keyword1)+1, sizeof *keyword1);
    for(int i = 0, fill = 0, k = strlen(keyword1); i < k; i++){//replaces all W/w with V
        if(keyword1[i] == 'W' || keyword1[i] == 'w'){
            keyword[fill++] = 'V';
            continue;
        }
        if(keyword1[i] != ' ')
            keyword[fill++] = toupper(keyword1[i]);
    }
    keyword[strlen(keyword1)] = '\0';


    char buffer[26] = "";
    

    char** KEY = calloc(5, sizeof(char *));
    for(int i = 0; i < 5; i++){ //creates 2d allocated array for KEY
        KEY[i] = calloc(5, sizeof(char));
    }

    /*buffer[0] = (toupper(keyword[0]) != 'W') ? toupper(keyword[0]) : 'V';
//    printf("%c ", toupper(keyword[0]));

    for (int i = 1, fill = 1, k = strlen(keyword); i < k; i++) {
        bool flag = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (toupper(keyword[i]) == buffer[j]){
                flag = 1;
                break;
            }
        }

        if (!flag) {
            //printf("%c ", toupper(keyword[i]));

            buffer[fill] = keyword[i];
  //          printf("%c ", buffer[fill]);
            fill++;
        }
    }*/
    buffer[0] = keyword[0];
    bool flag;
    for(int i = 1, fill = 1; keyword[i] != '\0'; i++){
        flag = false;
        if(strchr(buffer, keyword[i]) == NULL){
            flag = true;
        }

        if(flag){
            buffer[fill++] = keyword[i];
        }
    }
    buffer[25] = '\0';


//    printf("%s\n", buffer);

    char letter = 'A';
    int k = strlen(buffer);
    for (int i = k, fill = k; i < 26 + k; i++, letter++) {
        bool flag = 0;
        for (int j = 0; j < k; j++) {
            if (letter == buffer[j] || letter == 'W'){
                flag = 1;
                break;
            }
        }

        if (!flag) {
//            printf("%c ",letter);
            buffer[fill] = letter;
            fill++;
        }
    }
//    printf("\n\n");


//    printf("%d\n", strlen(buffer));


//    for(int i = 0, flag = 0; i < 5; i++){
//        for(int j = 0; j < 5; j++){
//            KEY[i][j] = buffer[flag];
//            printf("%c ",KEY[i][j]);
//            flag++;
//        }
//        printf("\n");
//    }


    for (int i = 0, flag = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            KEY[i][j] = buffer[flag++];

        }
    }


//    free(buffer);
    free(keyword);
    return KEY;
}


char* operate_text(const char* text){
    short spaces = 0;
    for(int i = 0, k = strlen(text); i < k; i++){
        if(text[i] == ' ')
            spaces++;
    }
    char buffer[strlen(text)-spaces +1];
    buffer[strlen(text)-spaces] = '\0';
//    printf("%ld\n",(sizeof(buffer)));


    for (int i = 0, fill = 0, k = strlen(text); i < k; i++) {
        if(text[i] != ' ') {
            if(toupper(text[i]) == 'W'){
                buffer[fill++] = 'V';
                continue;
            }
            buffer[fill++] = toupper(text[i]);
        }
    }
//    printf("%s\n", buffer);


    char* buffer1 = calloc((2*strlen(buffer)+1), sizeof *buffer);
    short X = 0; //how many addition X's will be in encrypted word

    for (int i = 0, fill = 0, k = strlen(buffer); i < k;) {
        if(buffer[i] != buffer[i+1]) {
            buffer1[fill++] = buffer[i];
            buffer1[fill++] = buffer[i+1];
            i+=2;
            continue;
        }

        if(buffer[i] == buffer[i+1] && buffer[i+1] != '\0' && buffer[i] != 'X') {
            buffer1[fill++] = buffer[i];
            buffer1[fill++] = 'X';
            X++;
            i++;
            continue;
        }

        if(buffer[i] == 'X' && buffer[i] == buffer[i+1]){
            buffer1[fill++] = 'X';
            buffer1[fill++] = 'X';
            i+=2;
        }
    }

    if((strlen(buffer)+X) % 2 != 0){
        buffer1[strlen(buffer)+X] = 'X';
        buffer1[strlen(buffer)+X +1] = '\0';
    }
    else
        buffer1[strlen(buffer)+X] = '\0';


//    printf("%s\n", buffer);
//    printf("%s\n", buffer1);
//    printf("%d\n", strlen(buffer1));

    return buffer1;
}

char* playfair_encrypt(const char* key, const char* text){
    if(key == NULL || text == NULL){
        return NULL;
    }

    for(int i = 0, k = strlen(text); i < k; i++){
        if (text[i] != ' ')
            break;
        if(i == k-1)
            return NULL;
    }

    for(int i = 0; text[i] != '\0'; i++){
        if( (toupper(text[i]) < 'A' && text[i] != ' ') || toupper(text[i]) > 'Z')
            return NULL;
    }

    for(int i = 0, k = strlen(key); i < k; i++){
        if(key[i] != ' ')
            break;
        if(i == k-1)
            return NULL;
    }

    for(int i = 0; key[i] != '\0'; i++){
        if ((toupper(key[i]) < 'A' && key[i] != ' ') || toupper(key[i]) > 'Z')
            return NULL;
    }

    char** KEY = make_key(key);
//    printf("\n");
//    printf("\n");

 //   for (int i = 0; i < 5; i++) {
 //       for (int j = 0; j < 5; j++) {
 //           printf("%c ", KEY[i][j]);
 //       }
 //       printf("\n");
 //   }


    char* operated = operate_text(text);
    char* buffer = calloc(2*strlen(operated), sizeof *operated);


//    printf("\n%s\n", operated);


    short y11 = 0, x11 = 0, y22 = 0, x22  = 0;
    short* y1 = &y11;
    short* x1 = &x11;
    short* y2 = &y22;
    short* x2 = &x22;
    for(int a = 0, fill = 0, k = strlen(operated); a < k; a+=2){

        for(short i = 0; i < 5; i++){ //looks for matching letters between KEY and operated
            for(short j = 0; j < 5; j++) {
                if (KEY[i][j] == operated[a]) {
                    *y1 = i;
                    *x1 = j;
                    i = 5;
                    break;
                }
            }
        }

        for(short i = 0; i < 5; i++){//looks for matching letters between KEY and operated
            for(short j = 0; j < 5; j++) {
                if (KEY[i][j] == operated[a + 1]) {
                    *y2 = i;
                    *x2 = j;
                    i = 5;
                    break;
                }
            }
        }

        if(*x1 == *x2){
            buffer[fill++] = KEY[(*y1+1)%5][*x1];
            buffer[fill++] = KEY[(*y2+1)%5][*x2];
            buffer[fill++] = ' ';
            continue;
        }

        if(*y1 == *y2){
            buffer[fill++] = KEY[*y1][(*x1+1)%5];
            buffer[fill++] = KEY[*y2][(*x2+1)%5];
            buffer[fill++] = ' ';
            continue;
        }

        else{
            buffer[fill++] = KEY[*y1][*x2];
            buffer[fill++] = KEY[*y2][*x1];
            buffer[fill++] = ' ';
        }
    }
    size_t len = strlen(operated) + strlen(operated)/2-1;
    buffer[len] = '\0';


    free(operated);
    for(int i = 0; i < 5; i++){
        free(KEY[i]);
    }
    free(KEY);


    return buffer;
}


char* playfair_decrypt(const char* key, const char* text1){
    if(key == NULL || text1 == NULL){
        return NULL;
    }

    for(int i = 0, k = strlen(text1); i < k; i++){
        if (text1[i] != ' ')
            break;
        if(i == k-1)
            return NULL;
    }

    for(int i = 0/*, k = strlen(text1)*/; /*i < k*/ text1[i] != '\0'; i++){
        if( (text1[i] < 'A' && text1[i] != ' ') || text1[i] > 'Z' || text1[i] =='W')
            return NULL;
    }

    for(int i = 0, k = strlen(key); i < k; i++){
        if(key[i] != ' ')
            break;
        if(i == k-1)
            return NULL;
    }

    for(int i = 0; key[i] != '\0'; i++){
        if( (toupper(key[i]) < 'A' && key[i] != ' ') || toupper(key[i]) > 'Z')
            return NULL;
    }

    char* text = calloc(strlen(text1)+1, sizeof *text);
    for(int i = 0, fill = 0, k = strlen(text1); i < k; i++){
        if(text1[i] != ' '){
            text[fill++] = text1[i];
        }
    }

    char** KEY = make_key(key);
    char* buffer = calloc(strlen(text)+1, sizeof *text);

    short y11 = 0, x11 = 0, y22 = 0, x22  = 0;
    short* y1 = &y11;
    short* x1 = &x11;
    short* y2 = &y22;
    short* x2 = &x22;
    for(int a = 0, fill = 0, k = strlen(text); a < k; a+=2){

        for(short i = 0; i < 5; i++){ //looks for matching letters between KEY and operated
            for(short j = 0; j < 5; j++) {
                if (KEY[i][j] == text[a]) {
                    *y1 = i;
                    *x1 = j;
                    i = 5;
                    break;

                }
            }
        }

        for(short i = 0; i < 5; i++){//looks for matching letters between KEY and operated
            for(short j = 0; j < 5; j++) {
                if (KEY[i][j] == text[a + 1]) {
                    *y2 = i;
                    *x2 = j;
                    i = 5;
                    break;

                }
            }
        }

        if(*x1 == *x2){
            buffer[fill++] = KEY[(*y1+4)%5][*x1];
            buffer[fill++] = KEY[(*y2+4)%5][*x2];
            continue;
        }

        if(*y1 == *y2){
            buffer[fill++] = KEY[*y1][(*x1+4)%5];
            buffer[fill++] = KEY[*y2][(*x2+4)%5];
            continue;
        }

        else{
            buffer[fill++] = KEY[*y1][*x2];
            buffer[fill++] = KEY[*y2][*x1];
        }
    }

    free(text);
    for(int i = 0; i < 5; i++){
        free(KEY[i]);
    }
    free(KEY);

    return buffer;
}