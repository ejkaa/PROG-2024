#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


char* reverse(const char* text){
	if(text == NULL)
		return NULL;

	char* buffer = calloc(strlen(text)+1, sizeof *text);

	for(int i = 0, k = strlen(text); i < k; i++){
		buffer[i] = toupper(text[k-i-1]);
	}
	return buffer;
}


char* make_keyv(const char* key, const char* text){
    char* buffer = calloc(strlen(text)+1, sizeof *key);

    for(int i = 0, fill = 0, k = 0; text[i] != '\0'; i++){
        if(key[k] == '\0')
            k = 0;

        if(toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
            buffer[fill++] = toupper(key[k++]);
    }
    return buffer;
}

char* vigenere_encrypt(const char* key, const char* text){
	if(key == NULL || text == NULL)
		return NULL;
 
    for(int i = 0; key[i] != '\0'; i++){
    	if (key[i] == ' '){
    		return NULL;
		}
	}
			
	for(int i = 0; key[i] != '\0'; i++)
        if(key[i] != ' ' && (toupper(key[i]) < 65  || toupper(key[i]) > 90))
            return NULL;
	
	int mod = 26;
    int letters = 130;
    char*  buffer = calloc(strlen(text)+1, sizeof *text);
    char* KEY = make_keyv(key, text);

    for(int i = 0, fill = 0; text[i] != '\0'; i++){
        if(toupper(text[i]) >= 65 && toupper(text[i]) <= 90){
            buffer[i] = 65 + (((toupper(text[i]) + KEY[fill++]) % letters)%mod);
        }

        else{
            buffer[i] = text[i];
        }
    }
	free(KEY);
    return buffer;
}


char* vigenere_decrypt(const char* key, const char* text){
    if(key == NULL || text == NULL)
        return NULL;

    for(int i = 0; key[i] != '\0'; i++)
        if (key[i] == ' ')
            return NULL;

    for(int i = 0; key[i] != '\0'; i++)
        if (key[i] != ' ' && (toupper(key[i]) < 65 || toupper(key[i]) > 90))
            return NULL;

    int mod = 26;
    char*  buffer = calloc(strlen(text)+1, sizeof *text);
    char* KEY = make_keyv(key, text);

    for(int i = 0, fill = 0; text[i] != '\0'; i++){
        if(text[i] >= 65 && text[i] <= 90){
            buffer[i] = 65 + ((text[i] - KEY[fill++] + mod)%mod);
        }

        else{
            buffer[i] = text[i];
        }
    }
    free(KEY);
    return buffer;
}

unsigned char* bit_encrypt(const char* text){
    if(text == NULL){
		return NULL;
	}
    size_t len = strlen(text);

    bool buf[len][8];
    bool buf1[len][8];
    unsigned char* ret = calloc(len+1, sizeof(unsigned char));

    for(int j = 0; text[j] != '\0'; j++){
        for (int i = 7; i >= 0; i--) {
            if (text[j] >> i & 1) {
                buf[j][7 - i] = 1;
            }
            else {
                buf[j][7 - i] = 0;
            }
        }
    }

    for(int i = 0; i < len; i++){
        buf1[i][0] = buf[i][1];
        buf1[i][1] = buf[i][0];
        buf1[i][2] = buf[i][3];
        buf1[i][3] = buf[i][2];
        
        buf1[i][4] = buf[i][4] ^ buf1[i][0];
        buf1[i][5] = buf[i][5] ^ buf1[i][1];
        buf1[i][6] = buf[i][6] ^ buf1[i][2];
        buf1[i][7] = buf[i][7] ^ buf1[i][3];

    }
//    for(int i = 0; i < len; i++) {
//        for (int j = 0; j < 8; j++)
//            printf("%d ", buf1[i][j]);
//        printf("\n");
//    }


    for(int i = 0; i < len; i++) {
        ret[i] += buf1[i][0] * 128 + buf1[i][1] * 64 + buf1[i][2] * 32 + buf1[i][3] * 16 + buf1[i][4] * 8 + buf1[i][5] * 4 + buf1[i][6] * 2 + buf1[i][7] * 1;
    }

    return ret;
}

char* bit_decrypt(const char* text){
    if(text == NULL){
		return NULL;
	}

	int len = strlen(text);

    bool buf[len][8];
    bool buf1[len][8];
    char* ret = calloc(len+1, sizeof(char));

    for(int j = 0; text[j] != '\0'; j++){
        for (int i = 7; i >= 0; i--) {
            if (text[j] >> i & 1) {
                buf[j][7 - i] = 1;
            }
            else {
                buf[j][7 - i] = 0;
            }
        }
    }

    for(int i = 0; i < len; i++){
        buf1[i][4] = buf[i][4] ^ buf[i][0];
        buf1[i][5] = buf[i][5] ^ buf[i][1];
        buf1[i][6] = buf[i][6] ^ buf[i][2];
        buf1[i][7] = buf[i][7] ^ buf[i][3];

        buf1[i][0] = buf[i][1];
        buf1[i][1] = buf[i][0];
        buf1[i][2] = buf[i][3];
        buf1[i][3] = buf[i][2];
    }

//    for(int i = 0; i < len; i++) {
//        for (int j = 0; j < 8; j++)
//            printf("%d ", buf1[i][j]);
//        printf("\n");
//    }


    for(int i = 0; i < len; i++) {
        ret[i] += buf1[i][0] * 128 + buf1[i][1] * 64 + buf1[i][2] * 32 + buf1[i][3] * 16 + buf1[i][4] * 8 + buf1[i][5] * 4 + buf1[i][6] * 2 + buf1[i][7] * 1;
    }

    return ret;
}

unsigned char* bmp_encrypt(const char* key, const char* text){
	if(key == NULL || text == NULL){
		return NULL;
	}

	char* reversed = reverse(text);

	char* vigovigo = vigenere_encrypt(key, reversed);

	unsigned char* b1t = bit_encrypt(vigovigo);

	free(reversed);
	free(vigovigo);
	return b1t;
}


char* bmp_decrypt(const char* key, const char* text){
	if(key == NULL || text == NULL){
		return NULL;
	}

	char* b1t = bit_decrypt(text);
	
	char* vigovigo = vigenere_decrypt(key, b1t);
	
	char* reversed = reverse(vigovigo);
	
	free(b1t);
	free(vigovigo);
	return reversed;
}
