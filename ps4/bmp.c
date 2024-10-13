#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

struct bmp_header* read_bmp_header(FILE* stream){
	if(stream == NULL){
		return NULL;
	}
	
	struct bmp_header* header = calloc(1, sizeof(struct bmp_header)/*+3*/);

	fseek(stream, 0, SEEK_SET);

	fread(header, sizeof(struct bmp_header), 1, stream);
	// printf("%d %d\n", header->height, header->width);
	// printf("%d\n", header->size);

    if (header->type != 0x4d42){
		free(header);
		return NULL;
    }

	return header;
}


struct pixel* read_data(FILE* stream, const struct bmp_header* header){
	if(stream == NULL || header == NULL){
		return NULL;
	}
	fseek(stream, 54, SEEK_SET);

	struct pixel* data = calloc((header->size - 54)/3/*+3*/, 3);

	int padding = (((header->width*3)%4) != 0) ? (4-(header->width*3)%4) : 0;
	// int padding = 0;
	// if(((header->width * 3) % 4) != 0)
	// 	padding = 4 - ((header->width*3)%4);

	for(int y = 0, flag = 0, vyska = header->height; y < vyska; y++){
        for(int x = 0, dlzka = header->width; x < dlzka; x++){
            if(fread(&data[flag++], 3, 1, stream) == 0){
            	free(data);
            	return NULL;
            }
        }
        if(y+1 < vyska){
            if(fseek(stream, padding, SEEK_CUR) != 0){
                free(data);
                return NULL;
            }
        }
    }
    return(data);
}


struct bmp_image* read_bmp(FILE* stream){
	if(stream == NULL){
		return NULL;
	}

	struct bmp_image* BMP = calloc(1, sizeof(struct bmp_image)/*+3*/);

	BMP->header = read_bmp_header(stream);
	if(BMP->header == NULL){
		fprintf(stderr, "Error: This is not a BMP file.\n");
		free(BMP);
		return NULL;
	}

	BMP->data = read_data(stream, BMP->header);
	if(BMP->data == NULL){
		fprintf(stderr, "Error: Corrupted BMP file.\n");
		free(BMP);
		return NULL;
	}

	return BMP;
}


bool write_bmp(FILE* stream, const struct bmp_image* image){
	if(stream == NULL || image == NULL){
		return NULL;
	}

	if(!fwrite(image->header, sizeof(struct bmp_header), 1, stream)){
		return false;
	}

	int padding = (((image->header->width*3)%4) != 0) ? (4-(image->header->width*3)%4) : 0;
	// int padding = 0;
	// if(((image->header->width * 3) % 4) != 0)
	// 	padding = 4 - ((image->header->width*3)%4);


	for(int y = 0, flag = 0, vyska = image->header->height; y < vyska; y++){
        for(int x = 0, dlzka = image->header->width; x < dlzka; x++){
            if(fwrite(&image->data[flag++], 3, 1, stream) == 0){
                return false;
            }
        }

        if(fwrite(PADDING_CHAR, 1, padding, stream) < padding){
            return false;
        }
    }
    return true;
}


void free_bmp_image(struct bmp_image* image){
	if(image == NULL)
		return;

	if(image->header == NULL){
		if(image->data == NULL){
			free(image);
			return;	
		}
		free(image->data);
		free(image);
		return;
	}

	if(image->data == NULL){
		if(image->header == NULL){
			free(image);
			return;	
		}
		free(image->header);
		free(image);
		return;
	}
	
	free(image->header);
	free(image->data);
	free(image);
}
