#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "playfair.h" 

int main(){
//	char** KEY = make_key("please");
//	char* encrypted = operate_text("Hhelloo");
//
//	
//	for (int i = 0; i < 5; i++) {
//        for (int j = 0; j < 5; j++) {
//            printf("%c ", KEY[i][j]);
//        }
//        printf("\n");
//    }	
//
//	printf("\n%s\n", encrypted);
//
//
//
//	for(int i = 0; i < 5; i++){
//        free(KEY[i]);
//    }
//    free(KEY);
//	free(encrypted);
//
//
	char* encrypted1 = playfair_encrypt("Nebolo mu treba viacej pocut hned si pomyslel ze jeho brat tam dakde musel zle pochodit", "Ale vies ty co");
	/*printf("%s\n", encrypted1);*/
	free(encrypted1);

	char* decrypted1 = playfair_decrypt("Ked ho mladenec obliekal zazrel i on tu smutnu ozltnutu horu a opytal sa", "IO CR EF NC NL TR LI LB IL OK DN AZ EA MZ KF YZ ZB SJ EC NC LP SI GB SY EC HX TL PB LI RL HU KH CN CJ");
	/*printf("%s\n", decrypted1);*/
	free(decrypted1);

	char* reversed = reverse("Hello worlxxxxxd!");
//	printf("%s\n", reversed);
	// "!DLROW OLLEH"
	free(reversed);

	char* encrypted2 = vigenere_encrypt("CoMPuTeR", "Hello world!");
//	printf("%s\n", encrypted2);
	free(encrypted2);

    char* decrypted2 = vigenere_decrypt("CoMPuTeR", "JSXAI PSINR!");
//	printf("%s\n", decrypted2);
    free(decrypted2);

	unsigned char* encrypted3 = bit_encrypt("Hello world!");


	char* decrypted3 = bit_decrypt(encrypted3);

	free(decrypted3);
    free(encrypted3);

    unsigned char* encrypted4 = bmp_encrypt("please", "Hello world!");
//	for(int i=0; i < 12;i++) {
//    	printf("%x ", encrypted[i]);
//    	//80 9c 95 95 96 11 bc 96 b9 95 9d 10
//	}
	char* decrypted4 = bmp_decrypt("please", encrypted4);
//	printf("%s\n", decrypted4);

	free(encrypted4);
	free(decrypted4);



	return 0;
}
