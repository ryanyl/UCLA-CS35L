#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int x = atoi(argv[1]);
    char c;
    char sp = ' ';
    for (int i = 0; i < x; i++) {
        c = rand()% (127 - 32) + 32;
        write(1, &c, 1);
        c = rand()% (127 - 32) + 32;
        write(1, &c, 1);
        c = rand()% (127 - 32) + 32;
        write(1, &c, 1);
        c = rand()% (127 - 32) + 32;
        write(1, &c, 1);
        write(1, &sp, 1);

    }
}