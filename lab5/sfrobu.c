#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

//function declarations
int frobcmp ( const char *a, const char *b );
int frobcmp_wrap( const void* a, const void* b);
void memErr( void* p );

// global variables
int case_s = 0;
char* buf = NULL;

int main(int argc, char *argv[]) {
	char* temp_buf;
	if(argc > 2){
		fprintf(stderr, "too many arguments\n");
		exit(1);
	}
	if(argc == 2){
		if(strcmp(argv[1], "-f") == 0){
			case_s = 1;
		}
		else{
			fprintf(stderr, "invalid arguments\n");
		}
	}

	struct stat finfo;
	if( fstat(0, &finfo) != 0){
		fprintf(stderr, "unable to read input info\n");
		exit(1);
	}

	int arr_size = finfo.st_size;
	int* words = NULL;
	int* tempw = NULL;
	int wordcount = 0;
	int new = 1;	

	if(S_ISREG(finfo.st_mode) && arr_size > 0){
		buf = (char*)malloc(sizeof(char)*arr_size);
		memErr(buf);
		read(0, buf, arr_size);
		for(int i = 0; i < arr_size; i++){
			if(new == 1){
				tempw = (int*)realloc(words, (wordcount+1)*sizeof(int));
				memErr(tempw);
				if(tempw == NULL)
					free(words);
				words = tempw;
				words[wordcount] = i;
				wordcount++;
				new = 0;
				if(buf[i] == ' ')
					new = 1;
			}
			else {
				if(buf[i] == ' ')
					new = 1;
			}
		}
	}

	// if more bytes are left from growing file
	lseek(0, 0, SEEK_CUR);
	char c;
	while(read(STDIN_FILENO, &c, 1) > 0){
		if(ferror(stdin)){
			fprintf(stderr, "read error\n");
			free(buf);
			free(words);
			exit(1);
		}
		temp_buf = (char*)realloc(buf, arr_size+1);
		memErr(temp_buf);
		buf = temp_buf;
		buf[arr_size] = c;

		if(new == 1){
			tempw = (int*)realloc(words, (wordcount+1)*sizeof(int));
			memErr(tempw);
			words = tempw;
			words[wordcount] = arr_size;
			wordcount++;
			new = 0;
			if(c == ' ')
				new = 1;
		}
		else{
			if(c == ' ')
				new = 1;
		}
		arr_size++;
	}

	if(new == 0){
		temp_buf = realloc(buf, arr_size+1);
		memErr(temp_buf);
		buf = temp_buf;
		buf[arr_size] = ' ';
		arr_size++;
	}
	
	qsort(words, wordcount, sizeof(int), frobcmp_wrap);

	for(int k = 0; k < wordcount; k++){
		for(int j = 0 ;; j++){
			write(1, &(buf[words[k]+j]), 1);
			if(buf[words[k]+j] == ' ')
				break;
		}
	}

	free(buf);
	free(words);
	exit(0);
}

// function definitions

int frobcmp ( const char *a, const char *b ) {
	while( *a != ' ' && *b != ' ' ){
		unsigned char a_t = (unsigned char) (*a^42);
		unsigned char b_t = (unsigned char)(*b^42);
		if(case_s == 1){
			a_t = toupper(a_t);
			b_t = toupper(b_t);
		}
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


int frobcmp_wrap( const void* a, const void* b) {
	int a_i = *(int const*) a;
	int b_i = *(int const*) b;
    return frobcmp(&(buf[a_i]), &(buf[b_i]));
}

void memErr(void *p){
	if( p == NULL ){
		fprintf(stderr, "memory allocation error\n");
		free(buf);
		exit(1);
	}
}
