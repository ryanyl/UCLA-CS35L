#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if( argc != 3 ){
		fprintf(stderr, "incorrect number of arguments\n");
		exit(1);
	}
	char* from = argv[1];
	char* to = argv[2];
	int from_l = 0;
	int to_l = 0;
	while(from[from_l] != '\0') {
		from_l++;
	}
	while(to[to_l] != '\0'){
		to_l++;
	}
	if(from_l == 0 && to_l == 0){
		fprintf(stderr, "to and from are empty\n");
		exit(1);
	}
	if( from_l != to_l ){
		fprintf(stderr, "to and from needs to have identical lengths\n");
		exit(1);
	}
	for(int i = 0; from[i] != '\0'; i++){
		for(int j = 0; j < i; j++){
			if(from[i] == from[j]){
				fprintf(stderr, "duplicate in from");
				exit(1);
			}
		}
	}
	char c = getchar();
	char t;
	while(!feof(stdin)){
		if(ferror(stdin)){
			fprintf(stderr, "error reading from stdin");
			exit(1);
		}

		t = c;
		for(int i = 0; i < from_l; i++){
			if(c == from[i]){
				t = to[i];
			}
		}
		putchar(t);
		c = getchar();
	}
}