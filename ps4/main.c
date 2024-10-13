#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include "transformations.h"


int main(){
	// FILE* read = fopen("assets/kliatba.noci.bmp", "rb");
	// FILE* flip = fopen("write_test.bmp", "wb");
	
	// struct bmp_image* image = read_bmp(read);

	// struct bmp_image* memory1 = rotate_right(flip_vertically(image));
	// free_bmp_image(memory1);

	// struct bmp_image* memory2 = rotate_left(flip_horizontally(image));
	// free_bmp_image(memory2);

	// struct bmp_image* memory3 = extract(image, "br");
	// free_bmp_image(memory3);

	// struct bmp_image* memory4 = scale(image, 2);
	// free_bmp_image(memory4);

	// write_bmp(flip, extract(crop(image, 0, 0, 192, 256), "br"));
	
	// free_bmp_image(image);

    // fclose(read);
    // fclose(flip);


	// FILE* fpbmp = fopen("file.bmp", "rb");
	// struct bmp_header* header = read_bmp_header(fpbmp);
	// printf("%d %d\n", header->width, header->height);

	// struct pixel* data = read_data(fpbmp, header);
	// if(data != NULL)
	// 	printf("1\n");

	// fclose(fpbmp);
	// free(header);
	// free(data);



	// FILE* BMP = fopen("write_test.bmp", "wb");
    // FILE* read = fopen("assets/mushroom.bmp", "rb");
    // write_bmp(BMP, rotate_right(read_bmp(read)));

    // fclose(read);
    // fclose(BMP);

	// FILE* read = fopen("cj.bmp", "rb");
	// FILE* output = fopen("write_test.bmp", "wb");

	// struct bmp_image* image = read_bmp(read);
	// if(read_bmp(read) != NULL)
	// 	printf("\n");

    // write_bmp(output, image);
	// free(image);
    // fclose(read);
    // fclose(output);


	// FILE* read = fopen("cj.bmp", "rb");
	// FILE* flip = fopen("write_test.bmp", "wb");

	// struct bmp_image* image = read_bmp(read);

    // write_bmp(flip, rotate_right(image));
	// free_bmp_image(image);
    // fclose(read);
    // fclose(flip);

	// FILE* read = fopen("assets/square.4x4.bmp", "rb");
	// FILE* crop1 = fopen("write_test.bmp", "wb");

	// struct bmp_image* image = read_bmp(read);

    // write_bmp(crop1, crop(image, 0, 0, 1, 1));
	// free_bmp_image(image);
    // fclose(read);
    // fclose(crop1);


	FILE* read = fopen("file.bmp", "rb");
	FILE* scale1 = fopen("write_test.bmp", "wb");

	struct bmp_image* image = read_bmp(read);

    write_bmp(scale1, scale(image, 3.237997));
	free_bmp_image(image);
    fclose(read);
    fclose(scale1);
	
	return 0;
}
