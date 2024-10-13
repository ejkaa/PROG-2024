#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mm(int num){
	int sum = 0;
	while(num >= 10){
		sum += num%10;
		num /= 10;
	}
	sum+=num%10;

	return sum;
}

int main(){
    unsigned long long num = 0;
    char buf;

    while((buf = fgetc(stdin)) != '\n'){
        num += buf-48;
    }

	int sum = mm(num);
	while(sum >=10)
		sum = mm(sum);

	printf("%d\n", sum);
	
	return 0;
}
