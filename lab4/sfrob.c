#include <stdio.h>
#include <stdlib.h>

int frobcmp ( const char *a, const char *b ) {
	while( *a != ' ' && *b != ' ' ){
		char a_t = *a^42;
		char b_t = *b^42;
		if ( a_t > b_t )
			return 1;
		else if ( a_t < b_t )
			return -1;
		a++;
		b++;
	}
	if ( *a == ' ' && *b == ' ' )
		return 0;
	else if ( *a != ' ' )
		return 1;
	else
		return -1;
}

int frobcmp_void( const void* a, const void* b) {
  return frobcmp(*(char**)a, *(char**)b);
}

int main(void){
	char** words = NULL;
	char** tempw = NULL;
	int size = 0;
	int new = 1;
	char *ptr;
	char *temp;
	int i = 0;
	int c = getchar();
	while( !feof(stdin) ){
		if(ferror(stdin)){
			fprintf(stderr, "Error reading char\n");
			for(int j = 0; j < size; j++){
				free(words[j]);
			}
			free(words);
			exit(1);
		}
		if(new == 1){
			temp = (char*)malloc(sizeof(char));
			if(temp == NULL){
				fprintf(stderr, "Error allocating memory\n" );
				for(int j = 0; j < size; j++){
					free(words[j]);
				}
				free(words);
				exit(1);
			}
			ptr = temp;
			ptr[i] = c;
			i++;
			new = 0;
			if( c == ' ')
				new = 1;
		}
		else{
			temp = (char*)realloc(ptr, (i+1) * sizeof(char));
			if(temp == NULL){
				fprintf(stderr, "Error allocating memory\n" );
				for(int j = 0; j < size; j++){
					free(words[j]);
				}
				free(words);
				exit(1);
			}
			ptr = temp;		
			ptr[i] = c;
			i++;
			if( c == ' '){
				tempw = (char**)realloc(words, (size+1) * sizeof(char*));
				if(tempw == NULL){
					fprintf(stderr, "Error allocating memory\n" );
					for(int j = 0; j < size; j++){
						free(words[j]);
					}
					free(words);
					exit(1);
				}
				words = tempw;
				words[size] = ptr;
				size++;
				new = 1;
				i = 0;

			}
		}
		c = getchar();
	}
	if( new == 0 ){
		temp = (char*)realloc(ptr, (i+1) * sizeof(char));
		if(temp == NULL){
			fprintf(stderr, "Error allocating memory\n" );
			for(int j = 0; j < size; j++){
				free(words[j]);
			}
			free(words);
			exit(1);
		}
		ptr = temp;
		ptr[i] = ' ';
		tempw = realloc(words, (size+1) * sizeof(char*));
		if (tempw == NULL){
			fprintf(stderr, "Error allocating memory\n" );
			for(int j = 0; j < size; j++){
				free(words[j]);
			}
			free(words);
			exit(1);			
		}
		words = tempw;
		words[size] = ptr;
		size++;
	}

	qsort(words, size, sizeof(char*), frobcmp_void);
	
	// output lines
	for(int x = 0; x < size; x++){
		for(int y = 0 ;; y++){
			if( putchar(words[x][y]) == EOF ){
				fprintf(stderr, "Error writing to STDOUT");
				for(int j = 0; j < size; j++){
					free(words[j]);
				}
				free(words);
				exit(1);
			}
			if(words[x][y] == ' ')
				break;
		}
	}

	for(int j = 0; j < size; j++){
		free(words[j]);
	}
	free(words);
	exit(0);

}