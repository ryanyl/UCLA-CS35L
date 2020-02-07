CC = gcc
CFLAGS = -O2 -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

randlibsw.so:
	$(CC) $(CFLAGS) -fPIC -c -o randlibsw.o randlibsw.c
	$(CC) $(CFLAGS) -shared -o randlibsw.so randlibsw.o
randlibhw.so:
	$(CC) $(CFLAGS) -fPIC -c -o randlibhw.o randlibhw.c
	$(CC) $(CFLAGS) -shared -o randlibhw.so randlibhw.o
randmain:
	$(CC) $(CFLAGS) -c -o randcpuid.o randcpuid.c
	$(CC) $(CFLAGS) -c -o randmain.o randmain.c
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) -o randmain randmain.o randcpuid.o
