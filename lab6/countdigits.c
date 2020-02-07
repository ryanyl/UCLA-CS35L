#include <stdio.h>

int main(void){
	int c = getchar();
	int count;
	while( !feof(stdin)){
		count++;
		c = getchar();
	}
	fprintf(stdout, "%d\n", count);
}