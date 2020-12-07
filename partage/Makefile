CC = gcc
CCFLAGS = -w -Wall -g

OBJ = tunalloc.o

all : test_tunalloc

test_tunalloc: test_tunalloc.c tunalloc.o
	$(CC) $(CCFLAGS) test_tunalloc.c -o test_tunalloc tunalloc.o

tunalloc.o : tunalloc.c
	$(CC) $(CCFLAGS) -c tunalloc.c

clean:
	- rm *.o
	- rm test_tunalloc