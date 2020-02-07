#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	if( argc != 3 ){
		write(2, "incorrect number of arguments\n", 30);
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
		write(2, "from and to are empty\n", 22);
		exit(1);
	}
	if( from_l != to_l ){
		write(2, "to and from needs to have identical lengths\n", 44);
		exit(1);
	}
	for(int i = 0; from[i] != '\0'; i++){
		for(int j = 0; j < i; j++){
			if(from[i] == from[j]){
				write(2, "duplicate in from argument\n", 27);
				exit(1);
			}
		}
	}
	char c;
	char t;
	while(read(0, &c, 1) != 0){
		if(ferror(stdin)){
			write(2, "error reading from stdin\n", 25);
			exit(1);
		}

		t = c;
		for(int i = 0; i < from_l; i++){
			if(c == from[i]){
				t = to[i];
			}
		}
		write(1, &t, 1);
	}
}