#include <stdio.h>

int main() {
	int A[8];
	short i;
	for(i = 0; i < 8; i++)
		printf("Byte %d : ", i),scanf("%x", &A[i]);
	for(i = 0; i < 64; i++) {
		if(i % 8 == 0 && i != 0)
			printf("\n");
		if((A[i / 8] & (1 << (i % 8))) > 0)
			printf("#");
		else
			printf(".");
	} 
	return 0; 
}