#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "transformations.h"

struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }

    struct bmp_image* flip_done = calloc(1, sizeof(struct bmp_image));
    flip_done->header = calloc(1, sizeof(struct bmp_header));
    memcpy(flip_done->header, image->header, sizeof(struct bmp_header));

    flip_done->data = calloc(image->header->height * image->header->width, 3);

    
    int width = image->header->width;
    int height = image->header->height;


    // int all_pixels = width*height;
    // for (int i = 0; i < all_pixels; i+=width){
    //     for (int j = i, counter = 0; j < width+i; j++){
    //         printf("%d\n",counter);
    //         memcpy(&flip_done->data[j], &image->data[width+i -1 -counter++], 3);
    //     }
    // }

    int flag = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            memcpy(&flip_done->data[flag++], &image->data[(i+1)*width -j -1], 3);
        }
    }

    return flip_done;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }

    struct bmp_image* flip_done = calloc(1, sizeof(struct bmp_image));
    flip_done->header = calloc(1, sizeof(struct bmp_header));
    memcpy(flip_done->header, image->header, sizeof(struct bmp_header));

    flip_done->data = calloc((image->header->size-54)/3, 3);


    int width = image->header->width;
    int height = image->header->height;
    int all_pixels = width*height;
    int flag = 0;
    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){
            memcpy(&flip_done->data[flag++], &image->data[all_pixels - (i+1)*(width) +j], 3);
        }
    }
    return flip_done;
}

struct bmp_image* rotate_left(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }

    struct bmp_image* flip_done = calloc(1, sizeof(struct bmp_image));
    flip_done->header = calloc(1, sizeof(struct bmp_header));
    memcpy(flip_done->header, image->header, sizeof(struct bmp_header));

    flip_done->data = calloc(image->header->width * image->header->height, 3);

    flip_done->header->width = image->header->height;
    flip_done->header->height = image->header->width;

    int width = flip_done->header->width;
    int height = flip_done->header->height;
    int all_pixels = width*height;

	int padding = (((width*3)%4) != 0) ? (4-(width*3)%4) : 0;


    flip_done->header->size = 54 + width*height*3 + height * (padding);
    flip_done->header->image_size = width*height*3 + height * (padding);

    // printf("%d %d %d\n", flip_done->header->width, flip_done->header->height, flip_done->header->image_size);

    int counter = 0;
    for(int i = 0; i < height; i++){
        for (int j = 1; j < width+1; j++){
            memcpy(&flip_done->data[counter++], &image->data[all_pixels - (j*height) +i] , 3);
        }
    }

    return flip_done;

}

struct bmp_image* rotate_right(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }

    struct bmp_image* flip_done = calloc(1, sizeof(struct bmp_image));
    flip_done->header = calloc(1, sizeof(struct bmp_header));
    memcpy(flip_done->header, image->header, sizeof(struct bmp_header));

    flip_done->data = calloc(image->header->width * image->header->height, 3);
    
    flip_done->header->width = image->header->height;
    flip_done->header->height = image->header->width;

    int width = flip_done->header->width;
    int height = flip_done->header->height;

	int padding = (((width*3)%4) != 0) ? (4-(width*3)%4) : 0;


    flip_done->header->size = 54 + width*height*3 + height * (padding);
    flip_done->header->image_size = width*height*3 + height * (padding);

    // printf("%d %d %d\n", flip_done->header->width, flip_done->header->height, flip_done->header->image_size);


    width = image->header->width;
    height = image->header->height;
    int counter = 0;
    for(int i = width-1; i >= 0; i--){
        for (int j = 0; j < height; j++){
            memcpy(&flip_done->data[counter++], &image->data[(j*width) + i ], 3);
        }
    }

    return flip_done;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
    if(image == NULL){
        return NULL;
    }

    if(start_x < 0 || start_y < 0 ||  start_x > image->header->width || start_y > image->header->height){
        return NULL;
    }
    if(width < 1 || height < 1 || width > image->header->width || height > image->header->height){
        return NULL;
    }
    if(start_x + (width-1) > image->header->width || start_y + (height-1) > image->header->height){
        return NULL;
    }

    struct bmp_image* crop_done = calloc(1, sizeof(struct bmp_image));
    crop_done->header = calloc(1, sizeof(struct bmp_header));
    memcpy(crop_done->header, image->header, sizeof(struct bmp_header));

    
    

     crop_done->header->width = width;
     crop_done->header->height = height;

   	int padding = (((width*3)%4) != 0) ? (4-(width*3)%4) : 0;

     crop_done->data = calloc(width * height, 3);

    crop_done->header->size = sizeof(struct bmp_header) + width*height*3 + height * (padding);
    crop_done->header->image_size = width*height*3 + height * (padding);

    // printf("%d %d %d\n", crop_done->header->width, crop_done->header->height, crop_done->header->image_size);
    
    int flag = 0;
    // int index;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // index = (image->header->height - (start_y+height) + i) * image->header->width + (start_x + j);
            memcpy(&crop_done->data[flag++], &image->data[(i + (-(start_y+height)+image->header->height))*image->header->width + start_x+j], 3);
        }
    }
    return crop_done;
}


struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if(image == NULL || colors_to_keep == NULL || !strlen(colors_to_keep)){
        return NULL;
    }

    struct bmp_image* extracted = calloc(1, sizeof(struct bmp_image));
    extracted->header = calloc(1, sizeof(struct bmp_header));
    extracted->data = calloc(image->header->width * image->header->height, 3);

    memcpy(extracted->header, image->header, sizeof(struct bmp_header));
    memcpy(extracted->data, image->data, 3);

    int r=0, g=0, b=0;
    for(int i = 0; i < strlen(colors_to_keep); i++){
        if(colors_to_keep[i] == 'r')
            r++;
        else if(colors_to_keep[i] == 'g')
            g++;
        else if(colors_to_keep[i] == 'b')
            b++;
        else
            return NULL;
    }


    for(int i = 0; i < image->header->width * image->header->height; i++){
        memcpy(&extracted->data[i], &image->data[i], 3);
    }

    for(int i = 0, all_pixels = image->header->width * image->header->height; i < all_pixels; i++){
        extracted->data[i].red = (!r) ? 0 : extracted->data[i].red;
        extracted->data[i].green = (!g) ? 0 : extracted->data[i].green;
        extracted->data[i].blue = (!b) ? 0 : extracted->data[i].blue;
    }

    return extracted;
}


struct bmp_image* scale(const struct bmp_image* image, float factor){
    if(image == NULL || factor < 0){
        return NULL;
    }

    struct bmp_image* scaled = calloc(1, sizeof(struct bmp_image));
    scaled->header = calloc(1, sizeof(struct bmp_header));

    if(factor == 1){//if scale == 1 return the same image
        scaled->data = calloc(1, image->header->image_size);
        memcpy(scaled->header, image->header, sizeof(struct bmp_header));
        memcpy(scaled->data, image->data, sizeof(image->header->image_size));
    
        return scaled;
    }

    memcpy(scaled->header, image->header, sizeof(struct bmp_header));

    scaled->header->width = (uint32_t)round((double)factor * (double)image->header->width);
    scaled->header->height = (uint32_t)round((double)factor * (double)image->header->height);
    printf("w: %d h: %d\n", scaled->header->width, scaled->header->height);

    scaled->data = calloc(scaled->header->width * scaled->header->height, 3);

  	int padding = (((scaled->header->width*3)%4) != 0) ? (4-(scaled->header->width*3)%4) : 0;

    printf("image_size1: %d size1: %d\n", image->header->image_size, image->header->size);


    scaled->header->image_size = scaled->header->width * scaled->header->height * 3 + scaled->header->height * padding;
    scaled->header->size = scaled->header->image_size + sizeof(struct bmp_header);
    printf("image_size: %d size: %d\n", scaled->header->image_size, scaled->header->size);

    for(int i = 0, flag = 0; i < scaled->header->height; i++){
       for(int j = 0; j < scaled->header->width; j++){

            int image_x = (double)j / (double)(scaled->header->width) * (double)image->header->width;
            int image_y = (double)i / (double)(scaled->header->height) * (double)image->header->height;

            memcpy(&scaled->data[flag++], &image->data[image_y * image->header->width + image_x], 3);
       }
   }

    return scaled;
}
